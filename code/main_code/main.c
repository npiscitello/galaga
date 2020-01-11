#include <avr/io.h>
#include "sound_files.h"

int main( void ) {
  char filename_buf[MAX_FILENAME_LEN];
  get_filename(filename_buf);
  return 0;
}
