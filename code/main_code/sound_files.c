#include <avr/pgmspace.h>
#include "sound_files.h"

const char oneup[] PROGMEM = "ONEUP.PCM";         // extra life sound
const char attack[] PROGMEM = "ATTACK.PCM";       // enemy descending
const char tracbeam[] PROGMEM = "TRACBEAM.PCM";   // ship able to be captures
const char capdest[] PROGMEM = "CAPDEST.PCM";     // captured ship destoryed
const char chalover[] PROGMEM = "CHALOVER.PCM";   // end of challenge stage
const char chalperf[] PROGMEM = "CHALPERF.PCM";   // perfect challenge stage
const char chalstage[] PROGMEM = "CHALSTAGE.PCM"; // begin challenge stage
const char coin[] PROGMEM = "COIN.PCM";           // coin inserted
const char die[] PROGMEM = "DIE.PCM";             // ship destroyed
const char capship[] PROGMEM = "CAPSHIP.PCM";     // ship captured
const char rescship[] PROGMEM = "RESCSHIP.PCM";   // ship rescued
const char nameent[] PROGMEM = "NAMEENT.PCM";     // name entry
const char intro[] PROGMEM = "INTRO.PCM";         // stage intro music

// only include filenames that you want to play here
// include a name multiple times if you want it to be more likely to be played
#define NUM_FILENAMES 14
PGM_P const filenames[] PROGMEM = {
  chalstage,
  chalstage,
  capdest,
  coin,
  attack,
  capship,
  tracbeam,
  intro,
  intro,
  intro,
  chalperf,
  chalover,
  rescship,
  nameent
};

/* see https://www.nongnu.org/avr-libc/user-manual/pgmspace.html for info on how
to read the strings - it'll look like
strcpy_P(ram_buf, (PGM_P)pgm_read_word(&(filenames[i])));
*/

// generate a (sorta not really) "random" number from ADC readings
uint8_t get_random_int( uint8_t max_val ) {
  // sample the lower 2 bits of the ADC 4 times and mod by max_val
  uint8_t rand = 0;
  PRR &= ~_BV(PRADC);

  // enable w/ prescaler of 32 (results in an ADC frequency a bit higher than
  // spec, but we specifically want bad data)
  ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS0);

  // all ADC pins are used as LED outputs, sample the internal temp sensor
  ADMUX = _BV(MUX3) | _BV(REFS0);

  for( int i = 0; i < 8; i += 2 ) {
    ADCSRA |= _BV(ADSC);
    while( (ADCSRA & _BV(ADSC)) == 1 ) {}
    // we could just use ADCL, but we need to read ADCH to clear it anyways and
    // this makes sure the compiler takes care of it.
    rand |= (ADCW & 0x0003) << i;
  }

  PRR |= _BV(PRADC);

  return rand;
}

void get_filename( char* filename_buffer ) {
  // C programmers don't measure dicks, they measure oneliners
  // also, YCM hates this cuz it's AVR compiler magic I guess? <shrug>
  strcpy_P(
      filename_buffer, (PGM_P)pgm_read_word(
        &(filenames[get_random_int(NUM_FILENAMES)])
        )
      );
  return;
}
