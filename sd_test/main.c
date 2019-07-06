#include <avr/io.h>
#include <avr/interrupt.h>
#include "ff.h"
#include "mmc_avr.h"

void set_mask( volatile uint8_t* reg, uint8_t mask ) {
  *reg |= mask;
  return;
}

void clr_mask( volatile uint8_t* reg, uint8_t mask ) {
  *reg &= !mask;
  return;
}

// set up Timer0 to tick once every quarter millisecond
void timer0_setup(void) {

  // disable interrupts globally for setup
  cli();

  // set CTC mode
  set_mask(&TCCR0A, _BV(WGM01));

  // set prescaler = 8 (1 MHz w/ 8 MHz system clock)
  set_mask(&TCCR0B, _BV(CS01));

  // set reset point (250 ticks counts out 0.25 ms at 1 MHz)
  OCR0A = 250;

  // enable global interrupts
  sei();

  // turn on timer 0
  clr_mask(&PRR, _BV(PRTIM0));

  return;
}

volatile uint8_t ticks_250us = 0;
ISR(TIMER0_OVF_vect) {
  ticks_250us++;
}

int main(void) {

  timer0_setup();

  mmc_disk_timerproc();

  // PortD - LED output
  DDRD = 0xFF;

  FATFS fs;
  FRESULT res = f_mount( &fs, "", 1);
  switch( res ) {
    case FR_INVALID_DRIVE:
      set_mask(&PORTD, _BV(PORTD0));
      break;
    case FR_DISK_ERR:
      set_mask(&PORTD, _BV(PORTD1));
      break;
    case FR_NOT_READY:
      set_mask(&PORTD, _BV(PORTD2));
      break;
    case FR_NOT_ENABLED:
      set_mask(&PORTD, _BV(PORTD3));
      break;
    case FR_NO_FILESYSTEM:
      set_mask(&PORTD, _BV(PORTD4));
      break;
    default:
      set_mask(&PORTD, _BV(PORTD5));
      break;
  }

  FIL led_file;
  res = f_open( &led_file, "/led_on.txt", FA_OPEN_EXISTING );
  switch( res ) {
    case FR_DISK_ERR:
      break;
    case FR_INT_ERR:
      break;
    case FR_NOT_READY:
      break;
    case FR_NO_FILE:
      break;
    case FR_NO_PATH:
      break;
    case FR_INVALID_NAME:
      break;
    case FR_DENIED:
      break;
    case FR_EXIST:
      break;
    case FR_INVALID_OBJECT:
      break;
    case FR_WRITE_PROTECTED:
      break;
    case FR_INVALID_DRIVE:
      break;
    case FR_NOT_ENABLED:
      break;
    case FR_NO_FILESYSTEM:
      break;
    case FR_TIMEOUT:
      break;
    case FR_LOCKED:
      set_mask(&PORTD, _BV(PORTD6));
      break;
    case FR_NOT_ENOUGH_CORE:
      set_mask(&PORTD, _BV(PORTD7));
      break;
    case FR_TOO_MANY_OPEN_FILES:
      break;
    default:
      break;
  }

  while(1) {

    // call mmc_disk_timerproc every 10ms
    if( ticks_250us >= 40 ) {
      ticks_250us = 0;
      mmc_disk_timerproc();
    }

  }
}
