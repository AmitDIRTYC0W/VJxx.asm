#include "integral_image.h"

#include <stdlib.h>
#include <string.h>

// Calculate the maximum no. of pixels that can be in a source image.
#define SRC_PIXEL_MAX ((2 << 8) - 1)
#define INT_PIXEL_MAX (((long)2 << 32) - 1)
#define MAX_PIXELS (INT_PIXEL_MAX / SRC_PIXEL_MAX)

unsigned char integrate_image(struct integral_image *dst, struct image src) {
  if ((long)(src.width) * (long)(src.height) > MAX_PIXELS) {
    fputs("ERROR: The image contains too many pixels🥵\n", stderr);
    return EXIT_FAILURE;
  }

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
        src.values[dst->width * y + x]
        + dst->values[dst->width * (y + 1) + x]
        + dst->values[dst->width * y + x + 1]
        - dst->values[dst->width * y + x];
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

