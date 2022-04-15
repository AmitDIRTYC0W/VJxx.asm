#ifndef HAAR_FEATURES_H_
#define HAAR_FEATURES_H_

#include "integral_image.h"

char haar_x2(
  struct integral_image,
  unsigned int,
  unsigned int,
  unsigned int,
  unsigned int
);

char haar_y2(
  struct integral_image,
  unsigned int,
  unsigned int,
  unsigned int,
  unsigned int
);

char haar_x3(
  struct integral_image,
  unsigned int,
  unsigned int,
  unsigned int,
  unsigned int
);

char haar_y3(
  struct integral_image,
  unsigned int,
  unsigned int,
  unsigned int,
  unsigned int
);

char haar_x2y2(
  struct integral_image,
  unsigned int,
  unsigned int,
  unsigned int,
  unsigned int
);

#endif
