#include <avr/pgmspace.h>
#include "sound_files.h"
#include "utils.h"

const char attack[] PROGMEM = "ATTACK.PCM";       // enemy descending
const char capdest[] PROGMEM = "CAPDEST.PCM";     // captured ship destoryed
const char capship[] PROGMEM = "CAPSHIP.PCM";     // ship captured
const char chalstage[] PROGMEM = "CHLSTGE.PCM"; // begin challenge stage
const char chalover[] PROGMEM = "CHLOVER.PCM";   // end of challenge stage
const char chalperf[] PROGMEM = "CHLPERF.PCM";   // perfect challenge stage
const char coin[] PROGMEM = "COIN.PCM";           // coin inserted
const char die[] PROGMEM = "DIE.PCM";             // ship destroyed
const char intro[] PROGMEM = "INTRO.PCM";         // stage intro music
const char nameent[] PROGMEM = "NAMEENT.PCM";     // name entry
const char oneup[] PROGMEM = "ONEUP.PCM";         // extra life sound
const char rescship[] PROGMEM = "RSCSHIP.PCM";   // ship rescued
const char tracbeam[] PROGMEM = "TRACBM.PCM";   // ship able to be captures

// only include filenames that you want to play here
// include a name multiple times if you want it to be more likely to be played
// we must subtract one b/c that's the max index of the list
#define NUM_FILENAMES 10 - 1
PGM_P const filenames[] PROGMEM = {
  attack,
  capdest,
  chalstage,
  chalover,
  chalperf,
  coin,
  intro,
  nameent,
  rescship,
  tracbeam
};

// generate a (sorta not really) "random" number from ADC readings
uint8_t get_random_int( uint8_t max_val ) {
  uint8_t rand = 0;
  PRR &= ~_BV(PRADC);

  // enable w/ prescaler of 32 (results in an ADC frequency a bit higher than
  // spec, but we specifically want bad data)
  ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS0);

  // all ADC pins are used as LED outputs, sample the internal temp sensor
  ADMUX = _BV(MUX3) | _BV(REFS0);

  // sample the lower 2 bits of the ADC 4 times
  for( int i = 0; i < 8; i += 2 ) {
    ADCSRA |= _BV(ADSC);
    while( ADCSRA & _BV(ADSC) ) {}
    // we could just use ADCL, but we need to read ADCH to clear it anyways and
    // this makes sure the compiler takes care of it.
    rand |= (ADCW & 0x0003) << i;
  }

  PRR |= _BV(PRADC);

  PORTC = rand % max_val;
  return rand % max_val;
}

/* see https://www.nongnu.org/avr-libc/user-manual/pgmspace.html for info on how
to read the strings - it'll look like
strcpy_P(ram_buf, (PGM_P)pgm_read_word(&(filenames[i])));
*/

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
