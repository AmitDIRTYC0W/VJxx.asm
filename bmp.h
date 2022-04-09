#ifndef BMP_H_
#define BMP_H_

#include <stdio.h>

// This represents images in memory.
struct image {
  // Store the width and height of the image in pixels.
  unsigned int width, height;
};

// This function reads a Windows BMP file and loads it to memory. It may
// print warnings to stderr. 
int read_bmp_file(FILE *, struct image *);

#endif
