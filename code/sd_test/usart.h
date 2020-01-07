#ifndef USART_H
#define USART_H

#include <stdint.h>

#define USART 1

void transmit_string_flash(const char* arr, uint8_t len);
void init_usart0(void);

#endif
