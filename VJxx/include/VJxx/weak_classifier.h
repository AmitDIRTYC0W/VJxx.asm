#ifndef VJXX_WEAK_CLASSIFIER_H_
#define VJXX_WEAK_CLASSIFIER_H_

#include <stdbool.h>

#include "haar_features.h"
#include "integral_image.h"

struct vjxx_weak_classifier {
  double alpha;

  int threshold;

  bool parity;

  enum vjxx_feature feature;

  unsigned int x0;
  unsigned int y0;
  unsigned int x1;
  unsigned int y1;
};

bool vjxx_weak_classify(
  struct vjxx_weak_classifier,
  struct vjxx_integral_image
);

#endif
