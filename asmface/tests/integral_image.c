#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "bmp.h"
#include "integral_image.h"

#define IN_VALUES { \
    255,   0, 255,   0, 255, \
      0, 255,   0, 255,   0, \
    255,   0, 255,   0, 255 \
  }
#define IN_WIDTH 5
#define IN_HEIGHT 3
#define IN_SIZE IN_WIDTH * IN_HEIGHT

#define EXPECTED_VALUES { \
    0,    0,    0,    0,    0,    0, \
    0,  255,  255,  510,  510,  765, \
    0,  255,  510, 765, 1020, 1275, \
    0,  510,  765, 1275, 1530, 2040 \
}

int main() {
  struct image picture;
  picture.width = IN_WIDTH;
  picture.height = IN_HEIGHT;
  picture.values = malloc(IN_SIZE);
  const char in_values[] = IN_VALUES;
  memcpy(picture.values, in_values, IN_WIDTH * IN_HEIGHT);

  struct integral_image integral_img;
  if (integrate_image(&integral_img, picture) > 0) {
    return EXIT_FAILURE;
  }

  free(picture.values);

  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 6; x++) {
      printf("%4d ", integral_img.values[integral_img.width * y + x]);
    }
    puts("");
  }

  const unsigned int expected_values[] = EXPECTED_VALUES;

  // TODO Use memcmp.
  for (int i = 0; i < 24; i++) {
    printf("%d - %d\n", integral_img.values[i], expected_values[i]); // TODO
    if (integral_img.values[i] != expected_values[i]) {
      return EXIT_FAILURE;
    }
  }

  free(integral_img.values);

  return EXIT_SUCCESS;
}

