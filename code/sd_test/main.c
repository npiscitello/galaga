#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "usart.h"
#include "pff.h"
#include "diskio.h"

#define ASCII_1 0x31
#define ASCII_2 0x32
#define ASCII_3 0x33
#define ASCII_4 0x34
#define ASCII_5 0x35
#define ASCII_6 0x36
#define ASCII_7 0x37

// run a connectivity test instead of a content test
#define CONN_TEST 1
// enable/disable serial debugging in usart.h

#define LEN_STARTUP 13
const char PROGMEM startup[] = "\r\n\r\nstartup\r\n";
#define LEN_CONN_TEST_STR 11
const char PROGMEM conn_test_str[] = "conn test\r\n";
#define LEN_FRS_UNKNOWN 17
const char PROGMEM frs_unknown[] = "unknown FRESULT\r\n";
#define LEN_FRS_OK 7
const char PROGMEM frs_ok[] = "FR_OK\r\n";
#define LEN_FRS_NOT_READY 14
const char PROGMEM frs_not_ready[] = "FR_NOT_READY\r\n";
#define LEN_FRS_DISK_ERR 13
const char PROGMEM frs_disk_err[] = "FR_DISK_ERR\r\n";
#define LEN_FRS_NO_FILESYSTEM 18
const char PROGMEM frs_no_filesystem[] = "FR_NO_FILESYSTEM\r\n";

void print_fresult(FRESULT res) {
  switch(res) {
    case FR_OK:
      transmit_string_flash(frs_ok, LEN_FRS_OK);
      break;
    case FR_NOT_READY:
      transmit_string_flash(frs_not_ready, LEN_FRS_NOT_READY);
      break;
    case FR_DISK_ERR:
      transmit_string_flash(frs_disk_err, LEN_FRS_DISK_ERR);
      break;
    case FR_NO_FILESYSTEM:
      transmit_string_flash(frs_no_filesystem, LEN_FRS_NO_FILESYSTEM);
      break;
    default:
      transmit_string_flash(frs_unknown, LEN_FRS_UNKNOWN);
      break;
  }
}



void set_mask( volatile uint8_t* reg, uint8_t mask ) {
  *reg |= mask;
  return;
}

void clr_mask( volatile uint8_t* reg, uint8_t mask ) {
  *reg &= ~mask;
  return;
}

// set up Timer0 to tick once every quarter millisecond
void timer0_setup(void) {
  // disable interrupts globally for setup
  cli();
  // turn on timer 0
  clr_mask(&PRR, _BV(PRTIM0));
  // set CTC mode
  set_mask(&TCCR0A, _BV(WGM01));
  // set prescaler = 8 (1 MHz w/ 8 MHz system clock)
  set_mask(&TCCR0B, _BV(CS01));
  // set reset point (250 ticks counts out 0.25 ms at 1 MHz)
  OCR0A = 250;
  // enable timer 1 interrupts
  set_mask(&TIMSK0, _BV(OCIE0A));
  // enable global interrupts
  sei();
  return;
}

volatile uint8_t ticks_250us = 0;
volatile uint8_t ticks_10ms = 0;
ISR(TIMER0_COMPA_vect) {
  ticks_250us++;
  if( ticks_250us >= 40 ) {
    ticks_250us = 0;
    ticks_10ms++;
  }
}

// oooooo this global feels really wrong but oh well
unsigned int* NULL;
FRESULT sd_ops(uint8_t* file_data, uint8_t file_data_len) {
  FATFS fs;
  FRESULT res;

  res = pf_mount( &fs );
  if( res != FR_OK ) {
    return res;
  }

  res = pf_open( "LED_ON.TXT" );
  if( res != FR_OK ) {
    return res;
  }

  res = pf_read( file_data, file_data_len,  NULL );

  return res;
}

int main(void) {
  init_usart0();
  transmit_string_flash(startup, LEN_STARTUP);
#if CONN_TEST == 1
  transmit_string_flash(conn_test_str, LEN_CONN_TEST_STR);
  FATFS fs;
  FRESULT res;

  do {
  res = pf_mount( &fs );
  } while (res != FR_OK);
  print_fresult(res);
#else
  // PortD - LED output
  DDRD = 0xFF;

  timer0_setup();

  uint8_t led_byte;
  FRESULT res;

  while(1) {

    // show when the second is about to trigger
    if( ticks_10ms == 90 ) {
      clr_mask(&PORTD, 0xFF);
      set_mask(&PORTD, _BV(PORTD0));
    }
    if( ticks_10ms == 95 ) {
      clr_mask(&PORTD, _BV(PORTD0));
    }

    // update the outputs every second
    if( ticks_10ms >= 100 ) {
      ticks_10ms = 0;
      res = sd_ops(&led_byte, 1);
      if( res == FR_OK ) {
        uint8_t msk_led;
        switch( led_byte ) {
          case ASCII_1:
            msk_led = _BV(1);
            break;
          case ASCII_2:
            msk_led = _BV(2);
            break;
          case ASCII_3:
            msk_led = _BV(3);
            break;
          case ASCII_4:
            msk_led = _BV(4);
            break;
          case ASCII_5:
            msk_led = _BV(5);
            break;
          case ASCII_6:
            msk_led = _BV(6);
            break;
          case ASCII_7:
            msk_led = _BV(7);
            break;
          default:
            msk_led = 0xFE;
        }
        set_mask(&PORTD, msk_led);
       } else {
        set_mask(&PORTD, _BV(PORTD0));
        clr_mask(&PORTD, ~_BV(PORTD0));
      }
    }
  }
#endif
}
