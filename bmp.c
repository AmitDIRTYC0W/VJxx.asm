#include "bmp.h"

#include <stdlib.h>
#include <string.h>

// See http://www.dragonwins.com/domains/getteched/bmp/bmpfileformat.htm and
// https://en.wikipedia.org/wiki/BMP_file_format#File_structure.

struct bmp_file_header {
  // These characters represent the file type; 'BM' is for Windows BMP
  // files.
  char type[2];
  
  // This is the size of the file in bytes.
  unsigned int size;
  
  // Declare two reserved fields no one ever used, the values of both should
  // be 0. 
  unsigned short reserved1, reserved2;
  
  // This fields stores the offset to the start of the pixel data, from the
  // start of the file in bytes. 
  unsigned int offBits;
};

int read_bmp_file_header(FILE *f) {
  // Load the header to memory.
  struct bmp_file_header contents;
  fread(&contents, sizeof(struct bmp_file_header), 1, f);
  
  // Assert the file is a Windows BMP file.
  if (memcmp(contents.type, "BM", sizeof(contents.type))) {
    fputs("ERROR: FILE is not a Windows BMP file.\n", stderr);
    return EXIT_FAILURE;
  }
  
  // Skip checking the file size make sense, assume the file is valid.
  
  // Warn the user if the file uses unknown/unsupported extensions.
  if (contents.reserved1 != 0 || contents.reserved2 != 0) {
    fputs("WARNING: FILE utilises unsupported format extensions.\n", stderr);
  }
  
  return -1;
}

int read_bmp_file(FILE *f) {
  int res;
  
  if ((res = read_bmp_file_header(f)) >= 0) {
    return res;
  }
  
  return -1;
}
