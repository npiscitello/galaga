#ifndef UTILS_H
#define UTILS_H

#include <avr/io.h>

void set_mask( volatile uint8_t* reg, uint8_t mask );

void clr_mask( volatile uint8_t* reg, uint8_t mask );

void stop_PWM(void);

void start_PWM(void);

void swap_buffers( volatile uint8_t** label_a, volatile uint8_t** label_b );

#endif
