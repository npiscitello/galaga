#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include "pff.h"
#include "diskio.h"
#include "utils.h"
#include "sound_files.h"

// how many bits of resolution used by the DAC
#define PWM_RESOLUTION 0x00FF

// how many bytes are in each of the double buffers
#define BUFFER_SIZE 512

// definition for the LED bootup
// how many 33-millisecond ticks to wait before the LEDs change during an
// animation (12 is a little under 152 BPM, the tempo of the intro)
#define LED_BOOTUP_DELAY 3
// how many frames are in the bootup sequence (oneshot)
#define LED_BOOTUP_STEPS 4
// led frames - each byte gets masked and written to Port C.
// LSB is the far right blaster.
const uint8_t g_led_bootup_frames[] PROGMEM = {
  0x00, 0x0C, 0x2D, 0x3F
};

// definition for the LED animation
// how many 33-millisecond ticks to wait before the LEDs change during an
// animation (12 is a little under 152 BPM, the tempo of the intro)
#define LED_ANIMATION_DELAY 4
// how many frames are in the animation sequence (looping)
#define LED_ANIMATION_STEPS 6
// led frames - each byte gets masked and written to Port C.
// LSB is the far right blaster.
//const uint8_t g_led_animation_frames[] PROGMEM = {0x2A, 0x15};
const uint8_t g_led_animation_frames[] PROGMEM = {
  0x2C, 0x1C, 0x02, 0x0D, 0x0E, 0x10
};

// if an SD card op fails all we can do is try again
// <TODO> add logic in the final app to power off after 
// a certain number of failed ops in a row
#define TRY_SD_OP(A) while( A != FR_OK ) {}

volatile uint8_t flags = 0x00;
#define MSK_FLAG_SD_READING       0x01
#define MSK_FLAG_BUFFER_SWAPPED   0x02
#define MSK_FLAG_END_OF_FILE      0x04
#define MSK_FLAG_SD_READY         0x08



 /***********************\
|***** AUDIO AND DAC *****|
 \***********************/

// there's gotta be a better way to do this than using so many globals
// the active buffer with audio data
volatile uint8_t* g_buf_read;
// the secondary buffer being loaded with data from the SD card
volatile uint8_t* g_buf_load;
// which sample is currently being read from that sample buffer
volatile uint16_t g_sample_index = 0;



// this is the main DAC
void setup_dac(void) {
  // disable interrupts globally for setup
  cli();
  // set OC1A (PB1) to output
  set_mask(&DDRB, _BV(DDB1));
  // turn on timer 1
  clr_mask(&PRR, _BV(PRTIM1));

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
  OCR1AL = *(g_buf_read + g_sample_index);
  g_sample_index++;
  if( g_sample_index >= BUFFER_SIZE ) {
    if( flags & MSK_FLAG_SD_READING ) {
      g_sample_index--;
    } else {
      g_sample_index = 0;
      swap_buffers(&g_buf_read, &g_buf_load);
      set_mask(&flags, MSK_FLAG_BUFFER_SWAPPED);
    }
  }
}



void stop_PWM(void) {
  clr_mask(&TCCR1B, _BV(CS12) | _BV(CS11) | _BV(CS10));
}

void start_PWM(void) {
  // no prescaler for timer1 (DAC)
  set_mask(&TCCR1B, _BV(CS10));
}



 /**************************\
|***** LEDS AND FLASHING*****|
 \**************************/

// simulate a 16 bit timer (make sure an LED change triggers on first enable)
volatile uint8_t g_timer0_cycles = LED_ANIMATION_DELAY;
// which frame we're on
volatile uint8_t g_current_frame = 0;



void setup_leds( void ) {
  // LED pins are all output (even the one used for the ADC!)
  set_mask(&DDRC, _BV(DDC0) | _BV(DDC1) | _BV(DDC2) | 
      _BV(DDC3) | _BV(DDC4) | _BV(DDC5));

  // We're sourcing, so start all LED pins low
  clr_mask(&PORTC, _BV(PORTC0) | _BV(PORTC1) | _BV(PORTC2) |
      _BV(PORTC3) | _BV(PORTC4) | _BV(PORTC5));

  // see setup_dac function for details
  // prescaler set in the start_LED function
  cli();
  clr_mask(&PRR, _BV(PRTIM0));
  TIMSK0 = _BV(TOIE0);
  TIFR0 = 0xFF;
  sei();
  return;
}



ISR(TIMER0_OVF_vect) {
  if( !(flags & MSK_FLAG_SD_READY) ) {
    if( ++g_timer0_cycles > LED_BOOTUP_DELAY ) {
      g_timer0_cycles = 0;
      PORTC &= 0xC0;
      // avr compiler magic, YCM will complain
      PORTC |= pgm_read_byte(&(g_led_bootup_frames[g_current_frame])) & 0x3F;
      // we only want it to run once
      if( g_current_frame < LED_BOOTUP_STEPS - 1 ) {
        ++g_current_frame;
      }
    }
  } else {
    if( ++g_timer0_cycles > LED_ANIMATION_DELAY ) {
      g_timer0_cycles = 0;
      PORTC &= 0xC0;
      // avr compiler magic, YCM will complain
      PORTC |= pgm_read_byte(&(g_led_animation_frames[g_current_frame])) & 0x3F;
      if( ++g_current_frame >= LED_ANIMATION_STEPS ) {
        g_current_frame = 0;
      }
    }
  }
}



void stop_LED( void ) {
  clr_mask(&TCCR0B, _BV(CS02) | _BV(CS01) | _BV(CS00));
}

void start_LED( void ) {
  // make sure we trigger as soon as we enable
  TCNT0 = 0xFF;
  // 1024 prescaler for timer0 (LED flasher)
  set_mask(&TCCR0B, _BV(CS02) | _BV(CS00));
}



int main( void ) {

  // get the random filename before the LED output messes up the RNG
  char filename_buf[MAX_FILENAME_LEN];
  get_filename(filename_buf);

  setup_leds();
  start_LED();

  setup_dac();
  stop_PWM();

  // set up audio buffers
  g_buf_read = malloc(BUFFER_SIZE);
  g_buf_load = malloc(BUFFER_SIZE);
  if( (g_buf_read == 0) || (g_buf_load == 0) ) {
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

  // load the sound file we'll be playing
  TRY_SD_OP( pf_open(filename_buf) );
  read_chunk( (uint8_t*)g_buf_load, BUFFER_SIZE );

  // switch the LEDs from the bootup sequence to the animation sequence
  set_mask(&flags, MSK_FLAG_SD_READY);
  g_current_frame = 0;

  // kick off audio
  swap_buffers(&g_buf_read, &g_buf_load);
  start_PWM();

  // make super duper sure we don't miss the end of file flag
  while(!(flags & MSK_FLAG_END_OF_FILE)) {
    // load new data every time the buffers swap
    if( flags & MSK_FLAG_BUFFER_SWAPPED ) {
      read_chunk( (uint8_t*)g_buf_load, BUFFER_SIZE );
      clr_mask(&flags, MSK_FLAG_BUFFER_SWAPPED);
    }
  }

  // un-latch the SSR
  clr_mask(&PORTB, _BV(PORTB6));
  return 0;
}
