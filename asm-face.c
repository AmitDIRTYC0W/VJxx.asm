#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"
#include "integral_image.h"

#define HELP_MESSAGE \
  "Usage: %s [FILE]\n" \
  "Detect human faces in a picture.\n" \
  "\n" \
  "With no FILE, or when FILE is -, read standard input.\n" \
  "\n" \
  "  -h, --help     display this help and exit\n"

int main(int argc, char *argv[]) {
  // Check validity of the command line arguments.
  if (argc != 2) {
    fputs("ERROR: invalid usage\n", stderr);
    return EXIT_FAILURE;
  }

  // If asked to, print an help message.
  if (!strcmp("-h", argv[1]) || !strcmp("--help", argv[1])) {
    printf(HELP_MESSAGE, argv[0]);
    return EXIT_SUCCESS;
  } 
  
  // Read FILE.
  FILE *f;
  if (!strcmp("-", argv[1])) {
    f = stdin;
  } else {
    f = fopen(argv[1], "rb");
  }
  
  if (f == NULL) {
    perror("ERROR: cannot read FILE");
    return EXIT_FAILURE;
  }
  
  // Load the picture to memory.
  struct image picture;
  if (read_bmp_file(f, &picture) > 0) {
    return EXIT_FAILURE;
  }
  
  fclose(f);
  
  // Calculate the integral image.
  struct integral_image integral_img;
  if (integrate_image(&integral_img, &picture) > 0) {
    return EXIT_FAILURE;
  }
  
  free(picture.values);
  
  int A0 = sum_area(integral_img, 390, 640, 550, 805);
  int A1 = sum_area(integral_img, 600, 460, 700, 500);
  
  printf("AREA #0: %d\n", A0 / (550 - 390) / (805 - 640));
  printf("AREA #1: %d\n", A1 / (700 - 600) / (800 - 460));
  
  free(integral_img.values);
  
  return 0;
}
