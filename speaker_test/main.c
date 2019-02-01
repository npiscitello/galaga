#include <avr/io.h>
#include <avr/interrupt.h>

// we want an ~2kHz sine wave, so we need 16 samples
#define NUM_SAMPLES 16
uint8_t samples[] = {
  128, 177, 219, 246, 250, 246, 219, 177, 128, 79, 37, 10, 0, 10, 37, 79
};
uint8_t sample_index = 0;

ISR(TIM1_OVF_vect) {
  // we're only working with 8-bit here
  OCR1AL = samples[sample_index];
  if( sample_index < NUM_SAMPLES ) {
    sample_index++;
  } else {
    sample_index = 0;
  }
}

int main() {

  // set OC1A (PB1) to output
  DDRB = 0x00 | _BV(DDB1);

  // turn on timer 1
  PRR = 0xFF & !_BV(PRTIM1) & !_BV(PRTIM0);

  // PWM setup
  // set pin behavior (non-inverted) and part of waveform mode (fast PWM, TOP=ICR1)
  TCCR1A = 0x00 | _BV(COM1A1) | _BV(WGM11);
  // set part of waveform mode (fast PWM, TOP=ICR1) and clock prescaler (clk/1)
  TCCR1B = 0x00 | _BV(WGM13) | _BV(WGM12) | _BV(CS10);
  // set TOP (higher value means higher resolution, lower frequency)
  ICR1H = 0x00;
  ICR1L = 0xFF;

  // waveform setup (load new value to OCR1A every TOP interrupt)
  // enable global interrupts
  sei();
  // enable timer1 TOP interrupts
  TIMSK1 = 0x00 | _BV(TOV1);
  // clear OCR1AH b/c we're only dealing with 8 bit for now
  OCR1AH = 0x00;

  while(1) {
  }
}
