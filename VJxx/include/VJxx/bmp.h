#ifndef VJXX_BMP_H_
#define VJXX_BMP_H_

#include <stdio.h>

// This represents images in memory.
struct vjxx_image {
  // Store the width and height of the image in pixels.
  unsigned int width, height;
  
  // Store the green pixel values of the image. Green values are the most
  // informative and are all that's needed.
  unsigned char *values;
};

// This function reads a Windows BMP file and loads it to memory. It may
// print warnings to stderr. 
unsigned char vjxx_read_bmp_file(FILE *, struct vjxx_image *);

#endif
