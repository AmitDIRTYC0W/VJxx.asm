#ifndef VJXX_HAAR_FEATURES_H_
#define VJXX_HAAR_FEATURES_H_

#include "integral_image.h"

char vjxx_haar_x2(
  struct vjxx_integral_image,
  unsigned int,
  unsigned int,
  unsigned int,
  unsigned int
);

char vjxx_haar_y2(
  struct vjxx_integral_image,
  unsigned int,
  unsigned int,
  unsigned int,
  unsigned int
);

char vjxx_haar_x3(
  struct vjxx_integral_image,
  unsigned int,
  unsigned int,
  unsigned int,
  unsigned int
);

char vjxx_haar_y3(
  struct vjxx_integral_image,
  unsigned int,
  unsigned int,
  unsigned int,
  unsigned int
);

char vjxx_haar_x2y2(
  struct vjxx_integral_image,
  unsigned int,
  unsigned int,
  unsigned int,
  unsigned int
);

#endif
