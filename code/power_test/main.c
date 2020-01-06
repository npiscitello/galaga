#include <avr/io.h>

int main(void) {

  // set B6 (pin 9) output
  DDRB |= _BV(DDB6);

  // set B6 high
  PORTB |= _BV(PORTB6);

}

