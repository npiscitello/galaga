#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "pff.h"
#include "diskio.h"
#include "utils.h"

#define PWM_RESOLUTION 0x00FF

// used to test the self-power-off function
#define PWR_CONTROL 1

// how many bytes are in each of the double buffers
#define BUFFER_SIZE 512

#define TRY_SD_OP(A) if( A != FR_OK ) { error_exit(); }

volatile uint8_t flags = 0x00;
#define MSK_FLAG_SD_READING       0x01
#define MSK_FLAG_BUFFER_SWAPPED   0x02
#define MSK_FLAG_END_OF_FILE      0x04

// there's gotta be a better way to do this than using so many globals
// the active buffer with audio data
volatile uint8_t* buf_read;
// the secondary buffer being loaded with data from the SD card
volatile uint8_t* buf_load;
// which sample is currently being read from that sample buffer
volatile uint16_t sample_index = 0;



void setup_timer1(void) {
  // disable interrupts globally for setup
  cli();
  // set OC1A (PB1) to output
  DDRB = 0x00 | _BV(DDB1);
  // turn on timer 1
  PRR = 0xFF & !_BV(PRTIM1);

  // PWM setup
  // set pin behavior (non-inverted) and part of waveform mode (fast PWM, TOP=ICR1)
  TCCR1A = 0x00 | _BV(COM1A1) | _BV(WGM11);
  // set part of waveform mode (fast PWM, TOP=ICR1). Clock will be enabled later.
  TCCR1B = 0x00 | _BV(WGM13) | _BV(WGM12);
  // set TOP
  ICR1H = 0xFF & (PWM_RESOLUTION >> 8);
  ICR1L = 0xFF & (PWM_RESOLUTION);

  // waveform setup (load new value to OCR1A every TOP interrupt)
  // enable timer1 TOP interrupts and clear pending interrupts
  TIMSK1 = 0x00 | _BV(TOIE1);
  TIFR1 = 0xFF;
  // clear OCR1AH b/c we're only dealing with 8 bit for now
  OCR1AH = 0x00;

  // enable global interrupts
  sei();
}



void read_chunk( uint8_t* read_buf, uint16_t num_bytes ) {
  UINT bytes_read = 0;
  set_mask(&flags, MSK_FLAG_SD_READING);
  TRY_SD_OP( pf_read(read_buf, num_bytes, &bytes_read) );
  clr_mask(&flags, MSK_FLAG_SD_READING);
  if( bytes_read < BUFFER_SIZE ) {
    set_mask(&flags, MSK_FLAG_END_OF_FILE);
  }
  return;
}



// pump out a sample. If the SD card is still filling the other buffer, idle on the current
// sample until its done.
ISR(TIMER1_OVF_vect) {
  OCR1AL = *(buf_read + sample_index);
  sample_index++;
  if( sample_index >= BUFFER_SIZE ) {
    if( flags & MSK_FLAG_SD_READING ) {
      sample_index--;
    } else {
      sample_index = 0;
      swap_buffers(&buf_read, &buf_load);
      set_mask(&flags, MSK_FLAG_BUFFER_SWAPPED);
    }
  }
}



int main(void) {

  // prepare timer1
  setup_timer1();
  // make sure we're not running the audio output
  stop_PWM();

  // enable output for debug lights
  DDRD = 0xFF;

#if PWR_CONTROL
  set_mask(&DDRB, _BV(DDB6));
  clr_mask(&PORTB, _BV(PORTB6));
#endif

  // set up buffers
  buf_read = malloc(BUFFER_SIZE);
  buf_load = malloc(BUFFER_SIZE);
  if( (buf_read == 0) || (buf_load == 0) ) {
    error_exit();
  }
  set_mask(&PORTD, _BV(PORTD1));

  // pre-load buffer
  FATFS fs;
  TRY_SD_OP( pf_mount( &fs ) );
  set_mask(&PORTD, _BV(PORTD2));
  TRY_SD_OP( pf_open( "SITB.PCM" ) );
  set_mask(&PORTD, _BV(PORTD3));
  read_chunk( (uint8_t*)buf_load, BUFFER_SIZE );
  set_mask(&PORTD, _BV(PORTD4));

  // kick off audio
  swap_buffers(&buf_read, &buf_load);
  start_PWM();

  while(1) {
    // load new data every time the buffers swap
    if( flags & MSK_FLAG_BUFFER_SWAPPED ) {
      read_chunk( (uint8_t*)buf_load, BUFFER_SIZE );
      clr_mask(&flags, MSK_FLAG_BUFFER_SWAPPED);
      set_mask(&PORTD, _BV(PORTD5));
    }
    
    // if we hit the end of the file, reset the read pointer
    if( flags & MSK_FLAG_END_OF_FILE ) {
      TRY_SD_OP( pf_lseek(0) );
      clr_mask(&flags, MSK_FLAG_END_OF_FILE);
      set_mask(&PORTD, _BV(PORTD6));

#if PWR_CONTROL
      // put PB6 high to turn off the power
      set_mask(&PORTB, _BV(PORTB6));
#endif
    }
  }
}
