#ifndef VJXX_STRONG_CLASSIFIER_H_
#define VJXX_STRONG_CLASSIFIER_H_

#include <stdbool.h>

#include "integral_image.h"
#include "weak_classifier.h"

#define NO_WEAK_CLASSIFIERS 128

typedef struct {
  vjxx_weak_classifier_t classifiers[NO_WEAK_CLASSIFIERS];
} vjxx_strong_classifier_t;

bool vjxx_strong_classify(
  vjxx_strong_classifier_t,
  vjxx_integral_image_t,
  unsigned int,
  unsigned char
);

#endif
