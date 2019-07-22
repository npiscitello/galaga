#include <avr/io.h>
#include <avr/interrupt.h>
#include "pff.h"
#include "diskio.h"

#define ASCII_1 0x31
#define ASCII_2 0x32
#define ASCII_3 0x33
#define ASCII_4 0x34
#define ASCII_5 0x35
#define ASCII_6 0x36
#define ASCII_7 0x37

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
}
