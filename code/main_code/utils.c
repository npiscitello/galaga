#include "utils.h"

unsigned char err = 0;

void set_mask( volatile uint8_t* reg, uint8_t mask ) {
  *reg |= mask;
  return;
}

void clr_mask( volatile uint8_t* reg, uint8_t mask ) {
  *reg &= ~mask;
  return;
}

void stop_PWM(void) {
  clr_mask(&TCCR1B, _BV(CS12) | _BV(CS11) | _BV(CS10));
}

void start_PWM(void) {
  set_mask(&TCCR1B, _BV(CS10));
}


void swap_buffers( volatile uint8_t** label_a, volatile uint8_t** label_b ) {
  volatile uint8_t* placeholder = *label_a;
  *label_a = *label_b;
  *label_b = placeholder;
  return;
}

