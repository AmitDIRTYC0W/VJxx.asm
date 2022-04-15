#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"
#include "haar_features.h"
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
  if (integrate_image(&integral_img, picture) > 0) {
    free(picture.values);
    return EXIT_FAILURE;
  }

  free(picture.values);

  printf("HAAR eyes: %d\n", haar_y3(integral_img, 420, 440, 490, 480));
  printf("HAAR face: %d\n", haar_x3(integral_img, 980, 705, 1035, 750));
  printf("HAAR legs/dress: %d\n", haar_y2(integral_img, 421, 1026, 531, 1129));
  printf("HAAR belt: %d\n", haar_x2y2 (integral_img, 620, 630, 680, 725));
  printf("HAAR cosplay thingy: %d\n", haar_x2y2 (integral_img, 380, 570, 475, 666));
  
  free(integral_img.values);
  
  return 0;
}
