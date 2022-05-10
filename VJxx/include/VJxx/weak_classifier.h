#ifndef VJXX_WEAK_CLASSIFIER_H_
#define VJXX_WEAK_CLASSIFIER_H_

#include <stdbool.h>

#include "haar_features.h"
#include "integral_image.h"

typedef struct {
  short alpha;

  int threshold;

  char parity;

  enum vjxx_feature feature_type;

  unsigned int x0;
  unsigned int y0;
  unsigned int width;
  unsigned int height;
} vjxx_weak_classifier_t;

bool vjxx_weak_classify(
  vjxx_weak_classifier_t,
  vjxx_integral_image_t,
  unsigned int,
  unsigned int,
  unsigned int,
  unsigned char
);

#endif
