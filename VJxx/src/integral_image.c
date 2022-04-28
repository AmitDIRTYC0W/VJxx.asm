#include "VJxx/integral_image.h"

#include <stdlib.h>
#include <string.h>

unsigned char vjxx_integrate_image(struct vjxx_integral_image *dst, struct vjxx_image src) {
  dst->width = src.width + 1;
  dst->height = src.height + 1;
    
  dst->values = malloc(dst->width * dst->height * sizeof(*dst->values));
  if (dst->values == NULL) {
    perror("ERROR: Cannot allocate memory for the integral image");
    return EXIT_FAILURE;
  }
  
  // Create zero paddings.
  for (unsigned int x = 0; x < dst->width; x++) {
    dst->values[x] = 0;
  }
  for (unsigned int y = 1; y < dst->height; y++) {
    dst->values[dst->width * y] = 0;
  }
  
  // Integrate the image
  for (unsigned int y = 0; y < src.height; y++) {
    for (unsigned int x = 0; x < src.width; x++) {
      dst->values[dst->width * (y + 1) + x + 1] =
        src.values[src.width * y + x]
        + dst->values[dst->width * (y + 1) + x]
        + dst->values[dst->width * y + x + 1]
        - dst->values[dst->width * y + x];
    }
  }
  
  return EXIT_SUCCESS;
}

unsigned int vjxx_sum_area(
  struct vjxx_integral_image img,
  unsigned int x0,
  unsigned int y0,
  unsigned int x1,
  unsigned int y1
) {
  return
    img.values[img.width * y1 + x1]
    - img.values[img.width * y0 + x1]
    - img.values[img.width * y1 + x0]
    + img.values[img.width * y0 + x0];
}

#undef SRC_PIXEL_MAX
#undef INT_PIXEL_MAX
#undef MAX_PIXELS
