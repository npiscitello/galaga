/* NOTE: I'm using the FTDI USB-Serial converter on the
 * SparkFun ESP8266 Thing Dev board because it's what I
 * had handy, and on mine the TX and RX pins and LEDs
 * are labeled backwards! To get this to work, I had to
 * connect the AVR TX pin to the pin labeled TX on the
 * ESP8266 Thing Dev board.
 *
 * Or, another way to look at it, the pins reflect the
 * Thing's relation to the computer: data on the TX pin
 * is transmitted to the computer and data on the RX
 * pin is received from the computer (this makes the
 * behavior of the LEDs make sense too).
 */

#include <avr/io.h>
#include <avr/pgmspace.h>

#define LEN_HELLO_WORLD_FLASH 14
const char PROGMEM hello_world_flash[] = "hello, world\r\n";

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



/* Transmit a string from RAM over UART
 *  arr: character array in RAM to pull data from
 *  len: integral length of transmission
 */
void transmit_string_ram(const char* arr, uint8_t len) {
  for( uint8_t i = 0; i < len; i++ ) {
    while( !( UCSR0A & _BV(UDRE0) ) ) {}
    UDR0 = arr[i];
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



/* hello world!
 */
int main(void) {

  init_usart0();

  transmit_string_flash(hello_world_flash, LEN_HELLO_WORLD_FLASH);
  transmit_string_ram("I'll foo your bar!\r\n", 20);

  while(1) {}
  return 0;
}
