#include <avr/io.h>
#include <avr/pgmspace.h>
#include "usart.h"

#if USART == 1
/* Transmit a string from flash over UART
 *  arr: character array in flash to pull data from
 *  len: integral length of transmission
 */
void transmit_string_flash(const char* arr, uint8_t len) {
  for( uint8_t i = 0; i < len; i++ ) {
    while( !( UCSR0A & _BV(UDRE0) ) ) {}
    // YCM won't like this, it's AVR compiler magic
    UDR0 = pgm_read_byte_near(arr + i);
  }
  return;
}

/* Initialize the usart peripheral
 *
 * 8 data bits, 1 stop bit, no parity, 115200 baud
 */
void init_usart0(void) {
  PRR = 0xFF & ~_BV(PRUSART0);
  UCSR0A = _BV(U2X0);
  UCSR0B = _BV(TXEN0);
  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
  UBRR0H = 0;
  UBRR0L = 8;
  return;
}

#else
void transmit_string_flash(const char* arr, uint8_t len) {
  return;
}

void init_usart0(void) {
  return;
}
#endif
