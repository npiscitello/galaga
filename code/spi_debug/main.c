#include <avr/io.h>
#include <avr/pgmspace.h>
#include "usart.h"

// SPI pins and such
#define CS_LOW()	PORTB &= ~_BV(PORTB7)	/* Set CS low */
#define	CS_HIGH()	PORTB |=  _BV(PORTB7)	/* Set CS high */
#define	IS_CS_LOW	!(PINB & _BV(PINB7))	/* Test if CS is low */

#define FCLK_SLOW() SPCR |= _BV(SPR1) | _BV(SPR0)   /* Set slow clock (F_CPU / 64) */
#define FCLK_FAST() SPCR &= ~_BV(SPR1) & ~_BV(SPR0)   /* Set fast clock (F_CPU / 2) */



// USART debug messages
#define LEN_STARTUP 13
const char PROGMEM startup[] = "\r\n\r\nstartup\r\n";

#define LEN_INIT_S 12
const char PROGMEM init_s[] = "init start\r\n";
#define LEN_INIT 7
const char PROGMEM init[] = "init\r\n";
#define LEN_INIT_E 10
const char PROGMEM init_e[] = "init end\r\n";

#define LEN_XMIT_S 12
const char PROGMEM xmit_s[] = "xmit start\r\n";
#define LEN_XMIT 6
const char PROGMEM xmit[] = "xmit\r\n";
#define LEN_XMIT_E 10
const char PROGMEM xmit_e[] = "xmit end\r\n";

#define LEN_RCV_S 11
const char PROGMEM rcv_s[] = "rcv start\r\n";
#define LEN_RCV 5
const char PROGMEM rcv[] = "rcv\r\n";
#define LEN_RCV_E 9
const char PROGMEM rcv_e[] = "rcv end\r\n";

#define LEN_LOOP 6
const char PROGMEM loop[] = "loop\r\n";



void init_spi(void) {
  transmit_string_flash(init_s, LEN_INIT_S);

  // outputs
  DDRB |= _BV(DDB7) | _BV(DDB3) | _BV(DDB5);

  // turn on and configure SPI peripheral
  PRR &= ~_BV(PRSPI);
  SPCR = _BV(SPE) | _BV(MSTR);
  SPSR = _BV(SPI2X);

  // gotta go fAST
  FCLK_FAST();

  transmit_string_flash(init_e, LEN_INIT_E);
}

void xmit_spi(uint8_t d) {
  transmit_string_flash(xmit_s, LEN_XMIT_S);
  SPDR = d;
  //loop_until_bit_is_set(SPSR, SPIF);
  while(!(SPSR & (1 << SPIF))) {}
  transmit_string_flash(xmit_e, LEN_XMIT_E);
}

uint8_t rcv_spi(void) {
  transmit_string_flash(rcv_s, LEN_RCV_S);
  xmit_spi(0xFF);
  transmit_string_flash(rcv_e, LEN_RCV_E);
  return SPDR;
}



int main(void) {
  init_usart0();
  transmit_string_flash(startup, LEN_STARTUP);

  init_spi();
  // similar construct as in the petitFATFS code
  for(uint8_t n= 10; n; n--) {
    transmit_string_flash(loop, LEN_LOOP);
    rcv_spi();
  }
}
