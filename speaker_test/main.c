#include <avr/io.h>
#include <avr/interrupt.h>

// higher resolution means a lower frequency
#define PWM_RESOLUTION 0x00FF

// we want an ~2kHz sine wave, so we need 16 samples
#define NUM_SAMPLES 32
uint8_t sine_samples[] = {
  128, 153, 177, 198, 219, 233, 246, 248, 250, 248, 246, 233, 219, 198, 177, 153,
  128, 104, 79, 58, 37, 24, 10, 5, 0, 5, 10, 24, 37, 58, 79, 104
};
uint8_t square_samples[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255
};
uint8_t sample_index = 0;

/*
ISR(TIM1_OVF_vect) {
  OCR1AL = samples[(sample_index++)%NUM_SAMPLES];
}
*/

ISR(TIM0_OVF_vect) {
  OCR0A = sine_samples[(sample_index++)%NUM_SAMPLES];
}


int main() {

  // disable interrupts globally for setup
  cli();

  /*
  // set OC1A (PB1) to output
  DDRB = 0x00 | _BV(DDB1);

  // turn on timer 1
  PRR = 0xFF & !_BV(PRTIM1);

  // PWM setup
  // set pin behavior (non-inverted) and part of waveform mode (fast PWM, TOP=ICR1)
  TCCR1A = 0x00 | _BV(COM1A1) | _BV(WGM11);
  // set part of waveform mode (fast PWM, TOP=ICR1) and clock prescaler (clk/1)
  TCCR1B = 0x00 | _BV(WGM13) | _BV(WGM12) | _BV(CS10);
  // set TOP
  ICR1H = 0xFF & (PWM_RESOLUTION >> 8);
  ICR1L = 0xFF & (PWM_RESOLUTION);

  // waveform setup (load new value to OCR1A every TOP interrupt)
  // enable timer1 TOP interrupts and clear pending interrupts
  TIMSK1 = 0x00 | _BV(TOIE1);
  TIFR1 = 0xFF;
  // clear OCR1AH b/c we're only dealing with 8 bit for now
  OCR1AH = 0x00;
  */

  // set OC1A (PB1) to output
  DDRD = 0x00 | _BV(DDD6);

  // turn on timer 0
  PRR = 0xFF & !_BV(PRTIM0);

  // PWM setup
  // set pin behavior (non-inverted) and waveform mode (fast PWM, max resolution)
  TCCR0A = 0x00 | _BV(COM0A1) | _BV(WGM01) | _BV(WGM00);
  // clock prescaler (clk/1)
  TCCR0B = 0x00 | _BV(CS00);
  // clock prescaler (clk/8)
  //TCCR0B = 0x00 | _BV(CS01);

  // waveform setup (load new value to OCR1A every TOP interrupt)
  // enable timer1 TOP interrupts and clear pending interrupts
  //TIMSK0 = 0x00 | _BV(TOIE0);
  //TIFR0 = 0xFF;

  // enable global interrupts
  sei();

  while(1) {
    // simulate an overflow interrupt
    // this loop takes about 256 timer ticks to run
    for(uint8_t j = 0; j < 0x52; j++) {}
    OCR0A = square_samples[(sample_index++)%NUM_SAMPLES];
  }
}
