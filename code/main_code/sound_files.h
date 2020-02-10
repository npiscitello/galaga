#ifndef SOUND_FILES_H
#define SOUND_FILES_H

#include <avr/io.h>

// the filenames themselves are defined in sound_files.c - they don't need to be
// available to the rest of the code

// how long the longest filename string is, including null terminator
#define MAX_FILENAME_LEN 14

// fill filename_buffer with a filename selected at (pseudo) random
void get_filename(char* filename_buffer);

#endif
