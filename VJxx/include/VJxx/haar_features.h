#ifndef VJXX_HAAR_FEATURES_H_
#define VJXX_HAAR_FEATURES_H_

#include "integral_image.h"

enum vjxx_feature_type {
  vjxx_feature_x2,
  vjxx_feature_y2,
  vjxx_feature_x3,
  vjxx_feature_y3,
  vjxx_feature_x2y2
};

int vjxx_haar_x2(
  vjxx_integral_image_t,
  unsigned int,
  unsigned int,
  unsigned int,
  unsigned int
);

int vjxx_haar_y2(
  vjxx_integral_image_t,
  unsigned int,
  unsigned int,
  unsigned int,
  unsigned int
);

int vjxx_haar_x3(
  vjxx_integral_image_t,
  unsigned int,
  unsigned int,
  unsigned int,
  unsigned int
);

int vjxx_haar_y3(
  vjxx_integral_image_t,
  unsigned int,
  unsigned int,
  unsigned int,
  unsigned int
);

int vjxx_haar_x2y2(
  vjxx_integral_image_t,
  unsigned int,
  unsigned int,
  unsigned int,
  unsigned int
);

#endif
