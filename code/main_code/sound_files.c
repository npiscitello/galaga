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
#define NUM_FILENAMES 11
PGM_P const filenames[] PROGMEM = {
  chalstage,
  capdest,
  coin,
  attack,
  capship,
  tracbeam,
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

  // IEEE-defined random number as a placeholder
  return 4;
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
