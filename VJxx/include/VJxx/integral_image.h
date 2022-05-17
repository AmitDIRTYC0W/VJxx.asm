#ifndef VJXX_INTEGRAL_IMAGE_H_
#define VJXX_INTEGRAL_IMAGE_H_

#include <stdint.h>

// See https://en.wikipedia.org/wiki/Summed-area_table.

// This represents an integral image in memory.
typedef struct {
  // Store the width and height of the image in pixels.
  unsigned int width, height;
  
  // Store the summed pixel values.
  unsigned int *values;
} vjxx_integral_image_t;

// This function generates integral images from regular images.
void vjxx_integrate_image(vjxx_integral_image_t *, unsigned char *, uint32_t, uint32_t);

#endif
