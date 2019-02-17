#include "ff.h"
#include "diskio.h"

DSTATUS status_state = STA_NODISK | STA_NOINIT;

DSTATUS disk_status( BYTE pdrv ) {
  status_state &= !STA_NODISK;
  return status_state;
}

DSTATUS disk_initialize( BYTE pdrv ) {
  status_state &= !STA_NOINIT;
  return status_state;
}

DRESULT disk_read( BYTE pdrv, BYTE* buff, DWORD sector, UINT count ) {
  return RES_NOTRDY;
}
