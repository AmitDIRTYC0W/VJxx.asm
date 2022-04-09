#include "bmp.h"

#include <stdlib.h>
#include <string.h>

// See http://www.dragonwins.com/domains/getteched/bmp/bmpfileformat.htm and
// https://en.wikipedia.org/wiki/BMP_file_format#File_structure.

// This struct represents the binary structure of a Windows BMP v3 file header.
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
  unsigned int off_bits;
} __attribute__((__packed__));

// This function parses BMP file headers and verifies that f is a BMP file. It
// assumes the cursor is at the beginning of the file.
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

struct bmp_image_header {
  // This represents the size of the header in bytes (should be 40).
  unsigned int header_size;
  
  // This represents the width of the image in pixels.
  unsigned int width;
  
  // This reprsesents the height of the image in pixels. The pixel data is ordered from botto
  // to top. If this value is negative, it is ordered from top to bottom.
  signed int height;
  
  // This represents the number of colour planes in the image (must be 1).
  unsigned short colour_planes;
  
  // This represents the no. of bits in a pixel.
  unsigned short bit_count;
  
  // There are more fields this program does no need.
} __attribute__((__packed__));

// This function parses BMP v3 image headers and stores revelevant data from
// them. It assumes the cursor is after the file header.
int read_bmp_image_header(FILE *f, struct image *img) {
  // Load the header to memory.
  struct bmp_image_header contents;
  fread(&contents, sizeof(struct bmp_image_header), 1, f);
  
  // Store the width and the height of the image.
  if (contents.height > 0) {
    img->height = contents.height;
  } else {
    fputs("ERROR: FILE is gay.", stderr);
    return EXIT_FAILURE;
  }

  img->width = contents.width;
  
  if (contents.header_size != 40) {
    fputs("WARNING: FILE is of an unsupported Windows BMP version.\n", stderr);
  }

  if (contents.colour_planes != 1) {
      fputs("WARNING: FILE is uses an odd no. of colour planes.\n", stderr);
  }
  
  if (contents.bit_count != 24) {
      fputs("ERROR: FILE uses an unsupported pixel format.\n", stderr);
      return EXIT_FAILURE;
  }

  return -1;
}

int read_bmp_file(FILE *f, struct image *img) {
  int res;
  
  if ((res = read_bmp_file_header(f)) >= 0) {
    return res;
  }

  if ((res = read_bmp_image_header(f, img)) >= 0) {
    return res;
  }
  
  return -1;
}
