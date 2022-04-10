#ifndef INTEGRAL_IMAGE_H_
#define INTEGRAL_IMAGE_H_

#include "bmp.h"

// See https://en.wikipedia.org/wiki/Summed-area_table.

// This represents an integral image in memory.
struct integral_image {
  // Store the width and height of the image in pixels.
  unsigned int width, height;
  
  // Store the summed pixel values.
  unsigned int *values;
};

// This function generates integral images from regular images.
unsigned char integrate_image(struct integral_image *, struct image *);

#endif