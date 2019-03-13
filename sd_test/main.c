#include <avr/io.h>
#include "ff.h"
#include "mmc_avr.h"

int main(void) {

  // call mmc_disk_timerproc every 10ms
  mmc_disk_timerproc();

  FIL* file;
  void* voidptr;
  UINT buf1;
  UINT* buf2;
  f_read(file, voidptr, buf1, buf2);

  while(1) {}
}
