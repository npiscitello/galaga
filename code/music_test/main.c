#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "pff.h"
#include "diskio.h"

#define PWM_RESOLUTION 0x00FF

// how many bytes are in each of the double buffers
#define BUFFER_SIZE 512

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
  return;
}

// there's gotta be a better way to do this than using so many globals
// the active buffer with audio data
volatile uint8_t* buf_read;
// the secondary buffer being loaded with data from the SD card
volatile uint8_t* buf_load;
// which sample is currently being read from that sample buffer
volatile uint16_t sample_index = 0;
ISR(TIMER1_OVF_vect) {
  OCR1AL = *(buf_read + sample_index);
  sample_index++;
  if( sample_index >= BUFFER_SIZE ) {
    sample_index = 0;
    swap_buffers(&buf_read, &buf_load);
  }
}

int main(void) {

  // prepare timer1
  setup_timer1();

  // set up buffers
  buf_read = malloc(BUFFER_SIZE);
  buf_load = malloc(BUFFER_SIZE);
  if( buf_read == 0 || buf_load == 0 ) {
    // turn on err light
    DDRD = 0x01;
    set_mask(&PORTD, _BV(PORTD0));
    exit(1);
  }

  while(1) {
  }
}
