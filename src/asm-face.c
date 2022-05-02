#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spng.h>

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
  FILE *picture_file;
  if (!strcmp("-", argv[1])) {
    picture_file = stdin;
  } else {
    picture_file = fopen(argv[1], "rb");
  }
  
  if (picture_file == NULL) {
    perror("ERROR: cannot read FILE");
    return EXIT_FAILURE;
  }
  
  // Decode the picture.
  int status;
  spng_ctx *spng_handle = spng_ctx_new(0);
  
  spng_set_png_file(spng_handle, picture_file);
  
  struct spng_ihdr picture_ihdr;
  if ((status = spng_get_ihdr(spng_handle, &picture_ihdr))) {
    fprintf(stderr, "ERROR: cannot decode FILE: %s\n", spng_strerror(status));
    spng_ctx_free(spng_handle);
    fclose(picture_file);
    return EXIT_FAILURE;
  }
  
  size_t picture_buffer_size;
  spng_decoded_image_size(spng_handle, SPNG_FMT_RGB8, &picture_buffer_size);
  unsigned char *picture_buffer = malloc(picture_buffer_size);
  
  status = spng_decode_image(spng_handle, picture_buffer, picture_buffer_size, SPNG_FMT_RGB8, 0);
  spng_ctx_free(spng_handle);
  fclose(picture_file);
  if (status) {
    fprintf(stderr, "ERROR: cannot decode FILE: %s\n", spng_strerror(status));
    return EXIT_FAILURE;
  }
   
  return 0;
}
