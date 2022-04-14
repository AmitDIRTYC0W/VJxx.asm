#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "bmp.h"

#define PATH_LENGTH 256
#define EXPECTED_VALUES { \
    255,   0, 255,   0, 255, \
      0, 255,   0, 255,   0, \
    255,   0, 255,   0, 255 \
  }
#define EXPECTED_WIDTH 5
#define EXPECTED_HEIGHT 3
#define EXPECTED_SIZE EXPECTED_WIDTH * EXPECTED_HEIGHT

int main(int, char * argv[]) {
  char path[PATH_LENGTH];
  strcpy(path, argv[1]);
  strcat(path, "/checkers.bmp");

  FILE *f = fopen(path, "rb");

  if (f == NULL) {
    return EXIT_FAILURE;
  }

  struct image picture;
  if (read_bmp_file(f, &picture) > 0) {
    return EXIT_FAILURE;
  }

  fclose(f);

  const char expected_values[] = EXPECTED_VALUES;

  if (picture.width != EXPECTED_WIDTH || picture.height != EXPECTED_HEIGHT) {
    return EXIT_FAILURE;
  }

  if (memcmp(picture.values, expected_values, EXPECTED_SIZE) != 0) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

