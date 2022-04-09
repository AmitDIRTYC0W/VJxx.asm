#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

#define HELP_MESSAGE \
  "Usage: %s [FILE]\n" \
  "Detect human faces in a picture.\n" \
  "\n" \
  "With no FILE, or when FILE is -, read standard input.\n" \
  "\n" \
  "  -h, --help     display this help and exit\n"

int main(int argc, char *argv[]) {
  int res;

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
  if ((res = read_bmp_file(f, &picture)) >= 0) {
    return res;
  }
  
  fclose(f);
  
  return 0;
}
