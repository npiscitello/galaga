/*-------------------------------------------------------------------------*/
/* PFF - Low level disk control module for AVR            (C)ChaN, 2014    */
/*-------------------------------------------------------------------------*/

#include "diskio.h"

/*-------------------------------------------------------------------------*/
/* Platform dependent macros and functions needed to be modified           */
/*-------------------------------------------------------------------------*/

#include <avr/io.h>			/* Device specific include files */
#include <avr/pgmspace.h>
#include "usart.h"
// enable/disable serial debugging in usart.h

#define LEN_INIT 7
const char PROGMEM init[] = "init\r\n";
#define LEN_XMIT 6
const char PROGMEM xmit[] = "xmit\r\n";
#define LEN_RCV 5
const char PROGMEM rcv[] = "rcv\r\n";

#define CS_LOW()	PORTB &= ~_BV(PORTB7)	/* Set CS low */
#define	CS_HIGH()	PORTB |=  _BV(PORTB7)	/* Set CS high */
#define	IS_CS_LOW	!(PINB & _BV(PINB7))	/* Test if CS is low */

#define FCLK_SLOW() SPCR |= _BV(SPR1) | _BV(SPR0)   /* Set slow clock (F_CPU / 64) */
#define FCLK_FAST() SPCR &= ~_BV(SPR1) & ~_BV(SPR0)   /* Set fast clock (F_CPU / 2) */

void dly_100us (void);		/* usi.S: Delay 100 microseconds */
void init_spi (void);		  /* usi.S: Initialize MMC control ports */
void xmit_spi (BYTE d);   /* usi.S: Send a byte to the MMC */
BYTE rcv_spi (void);		  /* usi.S: Send a 0xFF to the MMC and get the received byte */

/* function implementations */
void dly_100us( void ) {
  // this project runs on an 8 MHz clock
  // turn on timer 2
  PRR &= ~_BV(PRTIM2);
  // set CTC mode
  TCCR2A = _BV(WGM21);
  // set prescaler = 8 (1 MHz)
  TCCR2B = _BV(CS21);
  // 1 tick per microsecond
  OCR2A = 100;
  // reset counter
  TCNT2 = 0;
  TIFR2 = 0xFF;
  // wait for counter to trip
  loop_until_bit_is_set(TIFR2, OCF2A);
  // reset counter
  TIFR2 = 0xFF;
  // turn off counter
  PRR |= _BV(PRTIM2);
  return;
}

void init_spi( void ) {
  transmit_string_flash(init, LEN_INIT);

  // outputs
  DDRB |= _BV(DDB7) | _BV(DDB3) | _BV(DDB5);

  // turn on and configure SPI peripheral
  PRR &= ~_BV(PRSPI);
  SPCR = _BV(MSTR) | _BV(SPR1) | _BV(SPR0);
  SPSR = _BV(SPI2X);
  SPCR = _BV(SPE);

  // gotta go fAST
  FCLK_FAST();

  transmit_string_flash(init, LEN_INIT);
  return;
}

void xmit_spi( BYTE d ) {
  transmit_string_flash(xmit, LEN_XMIT);
  SPDR = d;
  transmit_string_flash(xmit, LEN_XMIT);
  loop_until_bit_is_set(SPSR, SPIF);
  // must "access" the SPDR after reading SPSR to clear SPIF
  //SPDR & 0xFF;
  transmit_string_flash(xmit, LEN_XMIT);
  return;
}

BYTE rcv_spi( void ) {
  transmit_string_flash(rcv, LEN_RCV);
  xmit_spi(0xFF);
  transmit_string_flash(rcv, LEN_RCV);
  return SPDR;
}


/*--------------------------------------------------------------------------

   Module Private Functions

---------------------------------------------------------------------------*/

/* Definitions for MMC/SDC command */
#define CMD0	(0x40+0)	/* GO_IDLE_STATE */
#define CMD1	(0x40+1)	/* SEND_OP_COND (MMC) */
#define	ACMD41	(0xC0+41)	/* SEND_OP_COND (SDC) */
#define CMD8	(0x40+8)	/* SEND_IF_COND */
#define CMD16	(0x40+16)	/* SET_BLOCKLEN */
#define CMD17	(0x40+17)	/* READ_SINGLE_BLOCK */
#define CMD24	(0x40+24)	/* WRITE_BLOCK */
#define CMD55	(0x40+55)	/* APP_CMD */
#define CMD58	(0x40+58)	/* READ_OCR */


static BYTE CardType;


/*-----------------------------------------------------------------------*/
/* Send a command packet to MMC                                          */
/*-----------------------------------------------------------------------*/

static BYTE send_cmd (
	BYTE cmd,		/* 1st byte (Start + Index) */
	DWORD arg		/* Argument (32 bits) */
)
{
	BYTE n, res;


	if (cmd & 0x80) {	/* ACMD<n> is the command sequense of CMD55-CMD<n> */
		cmd &= 0x7F;
		res = send_cmd(CMD55, 0);
		if (res > 1) return res;
	}

	/* Select the card */
	CS_HIGH();
	rcv_spi();
	CS_LOW();
	rcv_spi();

	/* Send a command packet */
	xmit_spi(cmd);						/* Start + Command index */
	xmit_spi((BYTE)(arg >> 24));		/* Argument[31..24] */
	xmit_spi((BYTE)(arg >> 16));		/* Argument[23..16] */
	xmit_spi((BYTE)(arg >> 8));			/* Argument[15..8] */
	xmit_spi((BYTE)arg);				/* Argument[7..0] */
	n = 0x01;							/* Dummy CRC + Stop */
	if (cmd == CMD0) n = 0x95;			/* Valid CRC for CMD0(0) */
	if (cmd == CMD8) n = 0x87;			/* Valid CRC for CMD8(0x1AA) */
	xmit_spi(n);

	/* Receive a command response */
	n = 10;								/* Wait for a valid response in timeout of 10 attempts */
	do {
		res = rcv_spi();
	} while ((res & 0x80) && --n);

	return res;			/* Return with the response value */
}




/*--------------------------------------------------------------------------

   Public Functions

---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (void)
{
	BYTE n, cmd, ty, ocr[4];
	UINT tmr;

#if PF_USE_WRITE
	if (CardType != 0 && IS_CS_LOW) disk_writep(0, 0);	/* Finalize write process if it is in progress */
#endif
	init_spi();		/* Initialize ports to control MMC */
	CS_HIGH();
	for (n = 10; n; n--) rcv_spi();	/* 80 dummy clocks with CS=H */

	ty = 0;
	if (send_cmd(CMD0, 0) == 1) {			/* GO_IDLE_STATE */
		if (send_cmd(CMD8, 0x1AA) == 1) {	/* SDv2 */
			for (n = 0; n < 4; n++) ocr[n] = rcv_spi();		/* Get trailing return value of R7 resp */
			if (ocr[2] == 0x01 && ocr[3] == 0xAA) {			/* The card can work at vdd range of 2.7-3.6V */
				for (tmr = 10000; tmr && send_cmd(ACMD41, 1UL << 30); tmr--) dly_100us();	/* Wait for leaving idle state (ACMD41 with HCS bit) */
				if (tmr && send_cmd(CMD58, 0) == 0) {		/* Check CCS bit in the OCR */
					for (n = 0; n < 4; n++) ocr[n] = rcv_spi();
					ty = (ocr[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2;	/* SDv2 (HC or SC) */
				}
			}
		} else {							/* SDv1 or MMCv3 */
			if (send_cmd(ACMD41, 0) <= 1) 	{
				ty = CT_SD1; cmd = ACMD41;	/* SDv1 */
			} else {
				ty = CT_MMC; cmd = CMD1;	/* MMCv3 */
			}
			for (tmr = 10000; tmr && send_cmd(cmd, 0); tmr--) dly_100us();	/* Wait for leaving idle state */
			if (!tmr || send_cmd(CMD16, 512) != 0) {	/* Set R/W block length to 512 */
				ty = 0;
			}
		}
	}
	CardType = ty;
	CS_HIGH();
	rcv_spi();

	return ty ? 0 : STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read partial sector                                                   */
/*-----------------------------------------------------------------------*/

DRESULT disk_readp (
	BYTE *buff,		/* Pointer to the read buffer (NULL:Forward to the stream) */
	DWORD sector,	/* Sector number (LBA) */
	UINT offset,	/* Byte offset to read from (0..511) */
	UINT count		/* Number of bytes to read (ofs + cnt mus be <= 512) */
)
{
	DRESULT res;
	BYTE rc;
	UINT bc;


	if (!(CardType & CT_BLOCK)) sector *= 512;	/* Convert to byte address if needed */

	res = RES_ERROR;
	if (send_cmd(CMD17, sector) == 0) {	/* READ_SINGLE_BLOCK */

		bc = 40000;	/* Time counter */
		do {				/* Wait for data block */
			rc = rcv_spi();
		} while (rc == 0xFF && --bc);

		if (rc == 0xFE) {	/* A data block arrived */

			bc = 512 + 2 - offset - count;	/* Number of trailing bytes to skip */

			/* Skip leading bytes in the sector */
			while (offset--) rcv_spi();

			/* Receive a part of the sector */
      do {
        *buff++ = rcv_spi();
      } while (--count);

			/* Skip trailing bytes in the sector and block CRC */
			do rcv_spi(); while (--bc);

			res = RES_OK;
		}
	}

	CS_HIGH();
	rcv_spi();

	return res;
}



/*-----------------------------------------------------------------------*/
/* Write partial sector                                                  */
/*-----------------------------------------------------------------------*/

#if PF_USE_WRITE
DRESULT disk_writep (
	const BYTE *buff,	/* Pointer to the bytes to be written (NULL:Initiate/Finalize sector write) */
	DWORD sc			/* Number of bytes to send, Sector number (LBA) or zero */
)
{
	DRESULT res;
	UINT bc;
	static UINT wc;	/* Sector write counter */

	res = RES_ERROR;

	if (buff) {		/* Send data bytes */
		bc = sc;
		while (bc && wc) {		/* Send data bytes to the card */
			xmit_spi(*buff++);
			wc--; bc--;
		}
		res = RES_OK;
	} else {
		if (sc) {	/* Initiate sector write process */
			if (!(CardType & CT_BLOCK)) sc *= 512;	/* Convert to byte address if needed */
			if (send_cmd(CMD24, sc) == 0) {			/* WRITE_SINGLE_BLOCK */
				xmit_spi(0xFF); xmit_spi(0xFE);		/* Data block header */
				wc = 512;							/* Set byte counter */
				res = RES_OK;
			}
		} else {	/* Finalize sector write process */
			bc = wc + 2;
			while (bc--) xmit_spi(0);	/* Fill left bytes and CRC with zeros */
			if ((rcv_spi() & 0x1F) == 0x05) {	/* Receive data resp and wait for end of write process in timeout of 500ms */
				for (bc = 5000; rcv_spi() != 0xFF && bc; bc--) {	/* Wait for ready */
					dly_100us();
				}
				if (bc) res = RES_OK;
			}
			CS_HIGH();
			rcv_spi();
		}
	}

	return res;
}
#endif
