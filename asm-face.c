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

// This function parses the command line arguments.
const char * parse_arguments(int argc, char *argv[], int *status) {
  if (argc == 2) {
    if (!strcmp("-h", argv[1]) || !strcmp("--help", argv[1])) {
      printf(HELP_MESSAGE, argv[0]);
      *status = EXIT_SUCCESS;
    } else {      
      *status = -1;
    }
  } else {
    fputs("ERROR: invalid usage\n", stderr);
    *status = EXIT_FAILURE;
  }
  
  return argv[1];
}

int main(int argc, char *argv[]) {
  int status;
  
  const char *filename = parse_arguments(argc, argv, &status);
  if (status >= 0) {
    return status;
  }

  FILE *f;
  f = fopen(filename, "rb");
  if (f == NULL) {
    perror("ERROR: cannot read FILE");
    return EXIT_FAILURE;
  }
  
  read_bmp_file(f, &status);
  
  fclose(f);
  
  return 0;
}
