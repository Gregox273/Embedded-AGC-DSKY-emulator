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
  
  fseek(source_file, 0, SEEK_END);
  int n = ftell(source_file);
  if(0 != (n&1))
  {
    printf("ROM image file size is odd");
    exit(EXIT_FAILURE);
  }
  
  n /= 2; // Convert byte-count to word count
  if (n > 36 * 02000)
  {
    printf("ROM image file larger than core memory");
    exit(EXIT_FAILURE);
  }
  
  fseek(source_file, 0, SEEK_SET);
  
  FILE *dest_file = fopen(dest,"wb");
  if(!dest_file)
  {
      printf("Failed to create destination file '%s'\n", dest);
      exit(EXIT_FAILURE);
  }
  
  unsigned char CoreRope[CORE_SIZE][2]; // Source buffer
  int16_t Fixed[40][02000];  // Dest buffer
  
  int i, j, Bank;

  for (Bank = 2, j = 0, i = 0; i < CORE_SIZE; i++)
  {
//    // Within the input file, the fixed-memory banks are arranged in the order
//    // 2, 3, 0, 1, 4, 5, 6, 7, ..., 35.  Therefore, we have to take a little care
//    // reordering the banks.
//    Fixed[Bank][j++] = (CoreRope[i][0] * 256 + CoreRope[i][1]) >> 1;
//    if (j == 02000)
//    {
//      j = 0;
//      // Bank filled.  Advance to next fixed-memory bank.
//      if (Bank == 2)
//        Bank = 3;
//      else if (Bank == 3)
//        Bank = 0;
//      else if (Bank == 0)
//        Bank = 1;
//      else if (Bank == 1)
//        Bank = 4;
//      else
//        Bank++;
//    }
    unsigned char In[2];
    uint16_t RawValue;
    fread(In, 1, 2, source_file);
    RawValue = In[0] * 256 + In[1];
    Fixed[Bank][j++] = RawValue >> 1;

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

  for(int b=0; b < 36; b++)
  {
      fwrite(Fixed[b], sizeof(Fixed[b][0]), 02000, dest_file);
  }
  
  // End
  fclose (source_file);
  fclose (dest_file);
  printf("Generated file \"%s\" from source \"%s\"\n", dest, source);

  return rtn;
}
