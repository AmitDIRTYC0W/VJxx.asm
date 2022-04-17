#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "VJxx/bmp.h"
#include "VJxx/integral_image.h"

#define IN_VALUES { \
    255,   0, 255,   0, 255, \
      0, 255,   0, 255,   0, \
    255,   0, 255,   0, 255 \
  }
#define IN_WIDTH 5
#define IN_HEIGHT 3
#define IN_SIZE IN_WIDTH * IN_HEIGHT

#define EXPECTED_SUM 1020

int main() {
  struct vjxx_image picture;
  picture.width = IN_WIDTH;
  picture.height = IN_HEIGHT;
  picture.values = malloc(IN_SIZE);
  const char in_values[] = IN_VALUES;
  memcpy(picture.values, in_values, IN_WIDTH * IN_HEIGHT);

  struct vjxx_integral_image integral_img;
  if (vjxx_integrate_image(&integral_img, picture) > 0) {
    return EXIT_FAILURE;
  }

  free(picture.values);

  if (vjxx_sum_area(integral_img, 1, 1, 5, 3) != EXPECTED_SUM) {
    return EXIT_FAILURE;
  }

  free(integral_img.values);

  return EXIT_SUCCESS;
}

