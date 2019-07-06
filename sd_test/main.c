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

  // call mmc_disk_timerproc every 10ms
  if( ticks_250us >= 40 ) {
    ticks_250us = 0;
    mmc_disk_timerproc();
  }

  FIL* file;
  void* voidptr;
  UINT buf1;
  UINT* buf2;
  f_read(file, voidptr, buf1, buf2);

  while(1) {}
}
