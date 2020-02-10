#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "pff.h"
#include "diskio.h"
#include "utils.h"
#include "sound_files.h"

// how many bits of resolution used by the DAC
#define PWM_RESOLUTION 0x00FF

// how many bytes are in each of the double buffers
#define BUFFER_SIZE 512

// if an SD card op fails all we can do is try again
// <TODO> add logic in the final app to power off after 
// a certain number of failed ops in a row
#define TRY_SD_OP(A) while( A != FR_OK ) {}


volatile uint8_t flags = 0x00;
#define MSK_FLAG_SD_READING       0x01
#define MSK_FLAG_BUFFER_SWAPPED   0x02
#define MSK_FLAG_END_OF_FILE      0x04
#define MSK_BUTTON_PRESSED        0x08

// there's gotta be a better way to do this than using so many globals
// the active buffer with audio data
volatile uint8_t* buf_read;
// the secondary buffer being loaded with data from the SD card
volatile uint8_t* buf_load;
// which sample is currently being read from that sample buffer
volatile uint16_t sample_index = 0;



// this is the main DAC
void setup_timer1(void) {
  // disable interrupts globally for setup
  cli();
  // set OC1A (PB1) to output
  set_mask(&DDRB, _BV(DDB1));
  // turn on timer 1
  PRR &= 0xFF & ~_BV(PRTIM1);

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
  return;
}



// read a bunch of bytes from the SD card
void read_chunk( uint8_t* read_buf, uint16_t num_bytes ) {
  UINT bytes_read = 0;
  set_mask(&flags, MSK_FLAG_SD_READING);
  TRY_SD_OP( pf_read(read_buf, num_bytes, &bytes_read) );
  clr_mask(&flags, MSK_FLAG_SD_READING);

  if( bytes_read < num_bytes ) {
    set_mask(&flags, MSK_FLAG_END_OF_FILE);
  }
  return;
}



// pump out a sample. If the SD card is still filling the other buffer, idle
// on the current sample until its done.
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



int main( void ) {

  // LED pins are all output (even the one used for the ADC!)
  set_mask(&DDRC, _BV(DDC0) & _BV(DDC1) & _BV(DDC2) & 
      _BV(DDC3) & _BV(DDC4) & _BV(DDC5));

  setup_timer1();
  stop_PWM();

  // set up audio buffers
  buf_read = malloc(BUFFER_SIZE);
  buf_load = malloc(BUFFER_SIZE);
  if( (buf_read == 0) || (buf_load == 0) ) {
    // I don't know how to recover from a malloc error
    // shut off and try again next time!
    clr_mask(&PORTB, _BV(PORTB6));
  }

  // set PB6 to output and set high to keep SSR latched
  // we don't do this in the beginning in case the chip browns-out and resets as
  // the board turns off - putting it a handful of instructions down means it's
  // still quick enough to be 'instantaneous' to humans but not fast enough to
  // accidentally trigger and re-latch the SSR as the board is turning off.
  set_mask(&DDRB, _BV(DDB6));
  set_mask(&PORTB, _BV(PORTB6));

  // mount SD card
  FATFS fs;
  TRY_SD_OP( pf_mount( &fs ) );

  // figure out what sound we'll be playing
  char filename_buf[MAX_FILENAME_LEN];
  get_filename(filename_buf);
  TRY_SD_OP( pf_open(filename_buf) );
  read_chunk( (uint8_t*)buf_load, BUFFER_SIZE );

  // kick off audio
  swap_buffers(&buf_read, &buf_load);
  start_PWM();

  // make super duper sure we don't miss the end of file flag
  while(!(flags & MSK_FLAG_END_OF_FILE)) {
    // load new data every time the buffers swap
    if( flags & MSK_FLAG_BUFFER_SWAPPED ) {
      read_chunk( (uint8_t*)buf_load, BUFFER_SIZE );
      clr_mask(&flags, MSK_FLAG_BUFFER_SWAPPED);
    }
  }

  // un-latch the SSR
  clr_mask(&PORTB, _BV(PORTB6));
  return 0;
}
