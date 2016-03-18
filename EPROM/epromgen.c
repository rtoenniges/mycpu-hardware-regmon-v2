/****************************************************************************
 * This file creates the ALU-tables needed by MyCPU.
 * Author: Dennis Kuschel, K.-G.-Kiesinger-Allee 14, 28279 Bremen, Germany
 ****************************************************************************/

/* NOTE: This file was tested with the following compilers:
 *
 * Microsoft Visual C, Turbo C, GNU C
 *
 * To compile under Linux type  # gcc -Wall -D_LINUX -o alugen.out alugen.c
 */

#include <stdio.h>
#ifndef _LINUX
#include <conio.h>
#endif


/* #define SPLITFLAGFILE  - define this to create ALU version 1 table files */

/* file names */
#define FNAME_RAW       "RAW_BIN.bin"
#define FNAME_BIN       "hex_7seg.bin"


void SEG_LOW(unsigned char din1, unsigned char *pdout)
{
  switch (din1)
  {
    case 0x0 : *pdout = 0x3F; break;
	case 0x1 : *pdout = 0x6;  break;
	case 0x2 : *pdout = 0x5B; break;
	case 0x3 : *pdout = 0x4F; break;
	case 0x4 : *pdout = 0x66; break;
	case 0x5 : *pdout = 0x6D; break;
	case 0x6 : *pdout = 0x7D; break;
	case 0x7 : *pdout = 0x7;  break;
	case 0x8 : *pdout = 0x7F; break;
	case 0x9 : *pdout = 0x6F; break;
	case 0xA : *pdout = 0x77; break;
	case 0xB : *pdout = 0x7C; break;
	case 0xC : *pdout = 0x58; break;
	case 0xD : *pdout = 0x5E; break;
	case 0xE : *pdout = 0x79; break;
	case 0xF : *pdout = 0x71; break;
	default : break;
  };

}
void SEG_HIGH(unsigned char din1, unsigned char *pdout)
{
  switch (din1)
  {
    case 0x0 : *pdout = 0xBF; break;
	case 0x1 : *pdout = 0x86;  break;
	case 0x2 : *pdout = 0xDB; break;
	case 0x3 : *pdout = 0xCF; break;
	case 0x4 : *pdout = 0xE6; break;
	case 0x5 : *pdout = 0xED; break;
	case 0x6 : *pdout = 0xFD; break;
	case 0x7 : *pdout = 0x87;  break;
	case 0x8 : *pdout = 0xFF; break;
	case 0x9 : *pdout = 0xEF; break;
	case 0xA : *pdout = 0xF7; break;
	case 0xB : *pdout = 0xFC; break;
	case 0xC : *pdout = 0xD8; break;
	case 0xD : *pdout = 0xDE; break;
	case 0xE : *pdout = 0xF9; break;
	case 0xF : *pdout = 0xF1; break;
	default : break;
  };
}


static int generateBinary(void)
{
  FILE *fBinary;
  unsigned long ulAdr;
  unsigned char adrl, adrh;
  unsigned char d1;
  int sel;
  int status = 0;

  fBinary = fopen(FNAME_RAW,"wb");
  if (fBinary == NULL)
  {
    printf("failed to generate file\n");
    return -1;
  }

  for (ulAdr = 0; ulAdr < 0x200; ulAdr++)
  {

    /* generate data + flag table for 2 byte ALU operations */

    adrl = (unsigned char)(ulAdr & 0xF);
	adrh = (unsigned char)((ulAdr >> 4) & 0xF);
    sel = (int)((ulAdr >> 8) & 1);

    switch (sel)
    {
	  case 0 : SEG_LOW (adrl, &d1); break;
      case 1 : SEG_HIGH (adrh, &d1); break;
      default: break;
    };

      /* write table data to file */
      if (fputc(d1,fBinary) == EOF)
      {
        printf("error: disk full\n");
        status = -1;
        break;
      }
   }

  fclose(fBinary);
  return status;
}

int generateEpromImage(int fill, const char *srcfile, const char *dstfile)
{
  FILE *sf, *df;
  unsigned char b;
  int status = 0;

  sf = fopen(srcfile,"rb");
  if (sf == NULL)
  {
    printf("failed to open file\n");
    return -1;
  }
  df = fopen(dstfile,"wb");
  if (df == NULL)
  {
    fclose(sf);
    printf("failed to generate file\n");
    return -1;
  }

  while (fill > 0)
  {
    if (fputc(255, df) == EOF)
    {
      printf("error: disk full\n");
      status = -1;
      break;
    }
    fill--;
  }

  while (status == 0)
  {
    b = fgetc(sf);
    if (feof(sf))
      break;
    if (fputc(b, df) == EOF)
    {
      printf("error: disk full\n");
      status = -1;
    }
  }

  fclose(sf);
  fclose(df);
  return status;
}

int main()
{
  printf("EPROM Binary generator for Hex to 7Seg\n");
  if (generateBinary())
  {
    printf("failed to create Image\n");
    return 0;
  }
  
  if ((generateEpromImage(32256,  FNAME_RAW, FNAME_BIN) != 0))
  {
    printf("failed to create ALU\n");
    return 0;
  } 
  printf("\EPROM Binary successfully created:\n");
  return 0;
}
