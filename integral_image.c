#include "integral_image.h"

#include <stdlib.h>

// Calculate the maximum no. of pixels that can be in a source image.
#define SRC_PIXEL_MAX ((2 << 8) - 1)
#define INT_PIXEL_MAX (((long)2 << 32) - 1)
#define MAX_PIXELS (INT_PIXEL_MAX / SRC_PIXEL_MAX)

unsigned char integrate_image(struct integral_image *dst, struct image *src) {
  if ((long)(src->width) * (long)(src->height) > MAX_PIXELS) {
    fputs("ERROR: The image contains too many pixels🥵\n", stderr);
    return EXIT_FAILURE;
  }

  dst->width = src->width;
  dst->height = src->height;
  
  dst->values = malloc(dst->width * dst->height * sizeof(*dst->values));
  if (dst->values == NULL) {
    perror("ERROR: Cannot allocate memory for the integral image");
    return EXIT_FAILURE;
  }
  
  // Pass 1: Place the left-most, top-most pixel in dst.
  dst->values[0] = src->values[0];
  
  // Pass 2: Integrate the top-most row.
  for (unsigned int x = 1; x < dst->width; x++) {
    dst->values[x] = dst->values[x - 1] + src->values[x];
  }
  
  // Pass 3: Integrate the left-most column.
  for (unsigned int y = 1; y < dst->height; y++) {
    dst->values[dst->width * y] = dst->values[dst->width * (y - 1)] + src->values[dst->width * y];
  }
  
  // Pass 4: Integrate the rest of the image.
  for (unsigned int y = 1; y < dst->height; y++) {
    for (unsigned int x = 1; x < dst->width; x++) {
      dst->values[dst->width * y + x] =
        src->values[dst->width * y + x]
        + dst->values[dst->width * y + x - 1]
        + dst->values[dst->width * (y - 1) + x]
        - dst->values[dst->width * (y - 1) + x - 1];
    }
  }
  
  return EXIT_SUCCESS;
}

unsigned int sum_area(
  struct integral_image img,
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