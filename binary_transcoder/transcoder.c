/*
 * AGC binary transcoder.
 * Based on EmbeddedDemo.c by Ron Burkey (part of yaAGC)
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define CORE_SIZE (044 * 02000)

int main(int argc, char **argv) 
{
  int rtn = 0;
  char *source = argv[1];
  char *dest = argv[2];
  
  FILE *source_file = fopen(source,"rb");
  if(!source_file)
  {
    printf("Failed to open source file '%s'\n", source);
    exit(EXIT_FAILURE);
  }
  
  FILE *dest_file = fopen(dest,"wb");
  if(!dest_file)
  {
      printf("Failed to create destination file '%s'\n", dest);
      exit(EXIT_FAILURE);
  }
  
  unsigned char CoreRope[CORE_SIZE][2]; // Source buffer
  int16_t Fixed[40][02000];  // Dest buffer
  
  fread(CoreRope, sizeof(CoreRope), 1, source_file);
  
  int i, j, Bank;

  Bank = 2;
  for (Bank = 2, j = 0, i = 0; i < CORE_SIZE; i++)
  {
    // Within the input file, the fixed-memory banks are arranged in the order
    // 2, 3, 0, 1, 4, 5, 6, 7, ..., 35.  Therefore, we have to take a little care
    // reordering the banks.
    Fixed[Bank][j++] = (CoreRope[i][0] * 256 + CoreRope[i][1]) >> 1;
    if (j == 02000)
    {
      j = 0;
      // Bank filled.  Advance to next fixed-memory bank.
      if (Bank == 2)
        Bank = 3;
      else if (Bank == 3)
        Bank = 0;
      else if (Bank == 0)
        Bank = 1;
      else if (Bank == 1)
        Bank = 4;
      else
        Bank++;
    }
  }
  
  fwrite(Fixed, sizeof(Fixed), 1, dest_file);
  
  // End
  fclose (source_file);
  fclose (dest_file);
  printf("Generated file \"%s\" from source \"%s\"\n", dest, source);

  return rtn;
}
