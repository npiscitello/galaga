#include "utils.h"

void set_mask( volatile uint8_t* reg, uint8_t mask ) {
  *reg |= mask;
  return;
}

void clr_mask( volatile uint8_t* reg, uint8_t mask ) {
  *reg &= ~mask;
  return;
}

void swap_buffers( volatile uint8_t** label_a, volatile uint8_t** label_b ) {
  volatile uint8_t* placeholder = *label_a;
  *label_a = *label_b;
  *label_b = placeholder;
  return;
}

