#include "bmp.h"

#include <stdlib.h>
#include <string.h>

// This parser parses most Windows BMP v3 files. It should be forgiving and
// be able to parse other Windows BMP versions, and even malformed files.
// However, files must
// • be uncompressed,
// • use the RGB888 pixel format,
// • contain only one image
// • and have their pixel data ordered from bottom to top.

// See http://www.dragonwins.com/domains/getteched/bmp/bmpfileformat.htm and
// https://en.wikipedia.org/wiki/BMP_file_format#File_structure.

// This struct represents the binary structure of a Windows BMP file header.
struct bmp_file_header {
  // These characters represent the file type; 'BM' is for Windows BMP
  // files.
  char type[2];
  
  // This is the size of the file in bytes.
  unsigned int size;
  
  // Declare two reserved fields no one ever used, the values of both should
  // be 0. 
  unsigned short reserved1, reserved2;
  
  // This fields stores the offset to the start of the pixel data, from the
  // start of the file in bytes. 
  unsigned int off_bits;
} __attribute__((__packed__));

// This function parses BMP file headers and verifies that f is a BMP file. It
// retrieves the address of the pixel data in bytes from the file's beginning.
// It assumes the cursor is at the beginning of the file.
unsigned char read_bmp_file_header(FILE *f, unsigned int *pixel_data) {
  // Load the header to memory.
  struct bmp_file_header contents;
  if (fread(&contents, sizeof(struct bmp_file_header), 1, f) < 1) {
    perror("ERROR: Whilst reading FILE");
    return EXIT_FAILURE;
  }
  
  // Assert the file is a Windows BMP file.
  if (memcmp(contents.type, "BM", sizeof(contents.type))) {
    fputs("ERROR: FILE is not a Windows BMP file.\n", stderr);
    return EXIT_FAILURE;
  }
  
  *pixel_data = contents.off_bits;
  
  // Skip checking the file size make sense, assume the file is valid.
  
  // Warn the user if the file uses unknown/unsupported extensions.
  if (contents.reserved1 != 0 || contents.reserved2 != 0) {
    fputs("WARNING: FILE utilises unsupported format extensions.\n", stderr);
  }
  
  return EXIT_SUCCESS;
}

struct bmp_image_header {
  // This represents the size of the header in bytes (should be 40).
  unsigned int header_size;
  
  // This represents the width of the image in pixels.
  unsigned int width;
  
  // This reprsesents the height of the image in pixels. The pixel data is ordered from botto
  // to top. If this value is negative, it is ordered from top to bottom.
  signed int height;
  
  // This represents the number of colour planes in the image (must be 1).
  unsigned short colour_planes;
  
  // This represents the no. of bits in a pixel.
  unsigned short bit_count;
  
  // There are more fields this program does no need.
} __attribute__((__packed__));

// This function parses BMP v3 image headers and stores revelevant data from
// them. It assumes the cursor is after the file header.
unsigned char read_bmp_image_header(FILE *f, struct image *img) {
  // Load the header to memory.
  struct bmp_image_header contents;
  if (fread(&contents, sizeof(struct bmp_image_header), 1, f) < 1) {
    perror("ERR:R Whilst reading FILE");
    return EXIT_FAILURE;
  }
  
  if (contents.bit_count != 24) {
      fputs("ERROR: FILE uses an unsupported pixel format.\n", stderr);
      return EXIT_FAILURE;
  }
  
  // Store the width and the height of the image.
  if (contents.height > 0) {
    img->height = contents.height;
  } else {
    fputs("ERROR: FILE is gay.", stderr);
    return EXIT_FAILURE;
  }

  img->width = contents.width;
  
  if (contents.header_size != 40) {
    fputs("WARNING: FILE is of an unsupported Windows BMP version.\n", stderr);
  }

  if (contents.colour_planes != 1) {
      fputs("WARNING: FILE is uses an odd no. of colour planes.\n", stderr);
  }

  return EXIT_SUCCESS;
}

// This structure represents a pixel in a BMP image pixel data.
struct rgb888 {
  // Red, green and blue values.
  unsigned char r, g, b;
} __attribute__((__packed__));

// This function load an image's pixel data to memory.
unsigned char read_bmp_pixel_data(FILE *f, struct image *img) {
  img->values = malloc(img->width * img->height);
  if (img->values == NULL) {
    perror("ERROR: Cannot allocate memory for the image");
    return EXIT_FAILURE;
  }

  // The size of the padding at the end of each row  in the file in bytes.
  size_t row_padding = 3 - (((img->width * sizeof(struct rgb888)) - 1) | 0x3);
  
  for (unsigned int y = 0; y < img->height; y++) {
    // TODO There might be a more efficent way of doing this.
    
    struct rgb888 buff[img->width];
    
    if (fread(&buff, sizeof(struct rgb888), img->width, f) < img->width) {
      perror("ERROR: Whilst reading FILE");
      return EXIT_FAILURE;
    }
    
    if (fseek(f, row_padding, SEEK_CUR) != 0) {
      perror("ERROR: Whilst reading FILE");
      return EXIT_FAILURE;
    }
    
    // TODO Use memory in a more clever way, we _need_ padding.
    for (unsigned int x = 0; x < img->width; x++) {
      img->values[img->width * (img->height - y - 1) + x] = buff[x].g;
    }
  }
    
  return EXIT_SUCCESS;
}


unsigned char read_bmp_file(FILE *f, struct image *img) {
  unsigned int pixel_data;
  if (read_bmp_file_header(f, &pixel_data) != EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }

  if (read_bmp_image_header(f, img) != EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }
  
  fseek(f, pixel_data, SEEK_SET);
  
  if (read_bmp_pixel_data(f, img) > 0) {
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
