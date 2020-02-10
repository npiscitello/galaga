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
// repeated names just makes the list longer, giving the rng more space to work
#define NUM_FILENAMES 45 - 1
PGM_P const filenames[] PROGMEM = {
  attack,
  capdest,
  chalstage,
  chalstage,
  chalover,
  chalover,
  chalperf,
  chalperf,
  coin,
  intro,
  intro,
  nameent,
  nameent,
  rescship,
  tracbeam,
  attack,
  capdest,
  chalstage,
  chalstage,
  chalover,
  chalover,
  chalperf,
  chalperf,
  coin,
  intro,
  intro,
  nameent,
  nameent,
  rescship,
  tracbeam,
  attack,
  capdest,
  chalstage,
  chalstage,
  chalover,
  chalover,
  chalperf,
  chalperf,
  coin,
  intro,
  intro,
  nameent,
  nameent,
  rescship,
  tracbeam,
};

// generate a (sorta not really) "random" number from ADC readings
uint8_t get_random_int( uint8_t max_val ) {
  uint8_t rand = 0;
  PRR &= ~_BV(PRADC);

  // ADC needs clock between 50kHz and 200kHz
  // prescaler = 64, 125kHz clock
  ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1);

  // sample the furthest pin from ground, ref against AVCC
  ADMUX = _BV(MUX2) | _BV(MUX0) | _BV(REFS0);

  // sample the lower 2 bits of the ADC 4 times
  for( int i = 0; i < 8; i += 2 ) {
    ADCSRA |= _BV(ADSC);
    while( ADCSRA & _BV(ADSC) ) {}
    // we could just use ADCL, but we need to read ADCH to clear it anyways and
    // this makes sure the compiler takes care of it.
    rand |= (ADCW & 0x0003) << i;
  }

  PRR |= _BV(PRADC);

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
