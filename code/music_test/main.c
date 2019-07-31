#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "pff.h"
#include "diskio.h"

#define PWM_RESOLUTION 0x00FF

// how many bytes are in each of the double buffers
#define BUFFER_SIZE 10

#define TRY_SD_OP(A) if( A != FR_OK ) { error_exit(); }

volatile uint8_t flags = 0x00;
#define MSK_FLAG_SD_READING       0x01
#define MSK_FLAG_BUFFER_SWAPPED   0x02
#define MSK_FLAG_END_OF_FILE      0x04

void set_mask( volatile uint8_t* reg, uint8_t mask ) {
  *reg |= mask;
  return;
}

void clr_mask( volatile uint8_t* reg, uint8_t mask ) {
  *reg &= ~mask;
  return;
}

void stop_PWM() {
  clr_mask(&TCCR1B, _BV(CS12) | _BV(CS11) | _BV(CS10));
}

void start_PWM() {
  set_mask(&TCCR1B, _BV(CS10));
}

void setup_timer1() {
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

void swap_buffers( volatile uint8_t** label_a, volatile uint8_t** label_b ) {
  volatile uint8_t* placeholder = *label_a;
  *label_a = *label_b;
  *label_b = placeholder;
  set_mask(&flags, MSK_FLAG_BUFFER_SWAPPED);
  return;
}

// there's gotta be a better way to do this than using so many globals
// the active buffer with audio data
volatile uint8_t* buf_read;
// the secondary buffer being loaded with data from the SD card
volatile uint8_t* buf_load;
// which sample is currently being read from that sample buffer
volatile uint16_t sample_index = 0;

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
    }
  }
}

void error_exit() {
  set_mask(&PORTD, _BV(PORTD0));
  exit(1);
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

int main(void) {

  // prepare timer1
  //setup_timer1();
  // make sure we're not running the audio output
  stop_PWM();

  // enable output for err light
  DDRD = 0xFF;

  // set up buffers
  buf_read = malloc(BUFFER_SIZE);
  buf_load = malloc(BUFFER_SIZE);
  if( buf_read == 0 || buf_load == 0 ) {
    error_exit();
  }
  set_mask(&PORTD, PORTD1);

  /*
  // pre-load buffer
  FATFS fs;
  TRY_SD_OP( pf_mount( &fs ) );
  set_mask(&PORTD, PORTD2);
  TRY_SD_OP( pf_open( "SOMEWHERE_IN_THE_BETWEEN.PCM" ) );
  set_mask(&PORTD, PORTD3);
  read_chunk( (uint8_t*)buf_load, BUFFER_SIZE );
  set_mask(&PORTD, PORTD4);

  // kick off audio
  swap_buffers(&buf_read, &buf_load);
  start_PWM();

  while(1) {
    // load new data every time the buffers swap
    if( flags & MSK_FLAG_BUFFER_SWAPPED ) {
      clr_mask(&flags, MSK_FLAG_BUFFER_SWAPPED);
      read_chunk( (uint8_t*)buf_load, BUFFER_SIZE );
      set_mask(&PORTD, PORTD5);
    }
    
    // if we hit the end of the file, reset the read pointer
    if( flags & MSK_FLAG_END_OF_FILE ) {
      // zero out the rest of the buffer if the noise is bad
      TRY_SD_OP( pf_lseek(0) );
      set_mask(&PORTD, PORTD6);
    }
  }
  */
}
