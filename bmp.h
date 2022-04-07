#ifndef BMP_H_
#define BMP_H_

#include <stdio.h>

// This function reads a Windows BMP file and loads it to memory. It may
// print warnings to stderr. 
void read_bmp_file(FILE *, int *);

#endif
