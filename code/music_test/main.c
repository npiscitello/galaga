#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include "pff.h"
#include "diskio.h"
#include "utils.h"

#define PWM_RESOLUTION 0x00FF

// used to test the self-power-off function
#define PWR_CONTROL 1

// USART output
#define USART 1

// how many bytes are in each of the double buffers
#define BUFFER_SIZE 512

#define TRY_SD_OP(A) if( A != FR_OK ) { error_exit(); }

volatile uint8_t flags = 0x00;
#define MSK_FLAG_SD_READING       0x01
#define MSK_FLAG_BUFFER_SWAPPED   0x02
#define MSK_FLAG_END_OF_FILE      0x04

// there's gotta be a better way to do this than using so many globals
// the active buffer with audio data
volatile uint8_t* buf_read;
// the secondary buffer being loaded with data from the SD car3
volatile uint8_t* buf_load;
// which sample is currently being read from that sample buffer
volatile uint16_t sample_index = 0;



/*** USART ***/
#define LEN_WAKEUP 8
const char PROGMEM wakeup[] = "wakeup\r\n";
#define LEN_BUFFER 13
const char PROGMEM buffer[] = "buffer init\r\n";
#define LEN_PWM 11
const char PROGMEM pwm[] = "pwm start\r\n";
#define LEN_LOAD 13
const char PROGMEM load[] = "buffer load\r\n";
#define LEN_SDINIT 10
const char PROGMEM sdinit[] = "sdc init\r\n";
#define LEN_MOUNT 11
const char PROGMEM mount[] = "sdc mount\r\n";
#define LEN_OPEN 11
const char PROGMEM open[] = "file open\r\n";
#define LEN_READ 11
const char PROGMEM read[] = "data read\r\n";

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



void setup_timer1(void) {
  // disable interrupts globally for setup
  cli();
  // set OC1A (PB1) to output
  DDRB = 0x00 | _BV(DDB1);
  // turn on timer 1
  PRR = 0xFF & !_BV(PRTIM1);

  // PWM setup
  // set pin behavior (non-inverted) and part of waveform mode (fast PWM, TOP=ICR1)
  TCCR1A = 0x00 | _BV(COM1A1) | _BV(WGM11);
  // set part of waveform mode (fast PWM, TOP=ICR1). Clock will be enabled later.
  TCCR1B = 0x00 | _BV(WGM13) | _BV(WGM12);
  // set TOP
  ICR1H = 0xFF & (PWM_RESOLUTION >> 8);
  ICR1L = 0xFF & (PWM_RESOLUTION);

  // waveform setup (load new value to OCR1A every TOP interrupt)
  // enable timer1 TOP interrupts and clear pending interrupts
  TIMSK1 = 0x00 | _BV(TOIE1);
  TIFR1 = 0xFF;
  // clear OCR1AH b/c we're only dealing with 8 bit for now
  OCR1AH = 0x00;

  // enable global interrupts
  sei();
}



void read_chunk( uint8_t* read_buf, uint16_t num_bytes ) {
  UINT bytes_read = 0;
  set_mask(&flags, MSK_FLAG_SD_READING);
  TRY_SD_OP( pf_read(read_buf, num_bytes, &bytes_read) );
  clr_mask(&flags, MSK_FLAG_SD_READING);
  if( bytes_read < BUFFER_SIZE ) {
    set_mask(&flags, MSK_FLAG_END_OF_FILE);
  }
  return;
}



// pump out a sample. If the SD card is still filling the other buffer, idle on the current
// sample until its done.
ISR(TIMER1_OVF_vect) {
  OCR1AL = *(buf_read + sample_index);
  sample_index++;
  if( sample_index >= BUFFER_SIZE ) {
    if( flags & MSK_FLAG_SD_READING ) {
      sample_index--;
    } else {
      sample_index = 0;
      swap_buffers(&buf_read, &buf_load);
      set_mask(&flags, MSK_FLAG_BUFFER_SWAPPED);
    }
  }
}



int main(void) {
  init_usart0();
  transmit_string_flash(wakeup, LEN_WAKEUP);

  // prepare timer1
  setup_timer1();
  // make sure we're not running the audio output
  stop_PWM();

  // enable output for debug lights
  DDRD = 0xFF;

#if PWR_CONTROL
  set_mask(&DDRB, _BV(DDB6));
  clr_mask(&PORTB, _BV(PORTB6));
#endif

  // set up buffers
  transmit_string_flash(buffer, LEN_BUFFER);
  buf_read = malloc(BUFFER_SIZE);
  buf_load = malloc(BUFFER_SIZE);
  if( (buf_read == 0) || (buf_load == 0) ) {
    error_exit();
  }
  set_mask(&PORTD, _BV(PORTD1));

  // pre-load buffer
  FATFS fs;
  do {
    err = 0;
    transmit_string_flash(sdinit, LEN_SDINIT);
    TRY_SD_OP( pf_mount( &fs ) );
    transmit_string_flash(mount, LEN_MOUNT);
    set_mask(&PORTD, _BV(PORTD2));
    TRY_SD_OP( pf_open( "SITB.PCM" ) );
    transmit_string_flash(open, LEN_OPEN);
    set_mask(&PORTD, _BV(PORTD3));
    read_chunk( (uint8_t*)buf_load, BUFFER_SIZE );
    transmit_string_flash(read, LEN_READ);
    set_mask(&PORTD, _BV(PORTD4));
  } while(err != 0);

  transmit_string_flash(pwm, LEN_PWM);
  // kick off audio
  swap_buffers(&buf_read, &buf_load);
  start_PWM();

  while(1) {
    transmit_string_flash(load, LEN_LOAD);
    // load new data every time the buffers swap
    if( flags & MSK_FLAG_BUFFER_SWAPPED ) {
      read_chunk( (uint8_t*)buf_load, BUFFER_SIZE );
      clr_mask(&flags, MSK_FLAG_BUFFER_SWAPPED);
      set_mask(&PORTD, _BV(PORTD5));
    }
    
    // if we hit the end of the file, reset the read pointer
    if( flags & MSK_FLAG_END_OF_FILE ) {
      TRY_SD_OP( pf_lseek(0) );
      clr_mask(&flags, MSK_FLAG_END_OF_FILE);
      set_mask(&PORTD, _BV(PORTD6));

#if PWR_CONTROL
      // put PB6 high to turn off the power
      set_mask(&PORTB, _BV(PORTB6));
#endif
    }
  }
}
