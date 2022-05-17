#ifndef VJXX_STRONG_CLASSIFIER_H_
#define VJXX_STRONG_CLASSIFIER_H_

#include <stdbool.h>

#include "integral_image.h"
#include "weak_classifier.h"

typedef struct {
	unsigned char no_weak_classifiers;

	int threshold;
} vjxx_strong_classifier_t;

bool vjxx_strong_classify(
	vjxx_strong_classifier_t classifier,
	vjxx_area_t *area_cursor,
	vjxx_weak_classifier_t *weak_classifier_cursor,
	vjxx_integral_image_t picture,
	unsigned int x0,
	unsigned int y0
);

#endif
