#ifndef VJXX_INTEGRAL_IMAGE_H_
#define VJXX_INTEGRAL_IMAGE_H_

#include "VJxx/bmp.h"

// See https://en.wikipedia.org/wiki/Summed-area_table.

// This represents an integral image in memory.
struct vjxx_integral_image {
  // Store the width and height of the image in pixels.
  unsigned int width, height;
  
  // Store the summed pixel values.
  unsigned int *values;
};

// This function generates integral images from regular images.
unsigned char vjxx_integrate_image(struct vjxx_integral_image *, struct vjxx_image);

// This function returns the sum of all the values in a given rectuangular area
// in an image. The ranges are exclusive.
unsigned int vjxx_sum_area(
  struct vjxx_integral_image,
  unsigned int,
  unsigned int,
  unsigned int,
  unsigned int
);

#endif
