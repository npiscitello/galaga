#include <avr/io.h>

int main() {

  // set OC1A (PB1) to output
  DDRB = 0x00 | _BV(DDB1);

  // turn on timer 1
  PRR = 0xFF & !_BV(PRTIM1);

  // set pin behavior (non-inverted) and part of waveform mode (fast PWM, TOP=ICR1)
  TCCR1A = 0x00 | _BV(COM1A1) | _BV(WGM11);
  //TCCR1A = 0x00 | _BV(COM1A1) | _BV(WGM11) | _BV(WGM10);
  // set part of waveform mode (fast PWM, TOP=ICR1) and clock prescaler (clk/1)
  TCCR1B = 0x00 | _BV(WGM13) | _BV(WGM12) | _BV(CS10);
  //TCCR1B = 0x00 | _BV(WGM12) | _BV(CS10);
  // set TOP (higher value means higher resolution, lower frequency)
  ICR1H = 0x03;
  ICR1L = 0xFF;

  // volume
  OCR1AH = 0x00;
  OCR1AL = 0x01;

  while(1) {
  }
}
