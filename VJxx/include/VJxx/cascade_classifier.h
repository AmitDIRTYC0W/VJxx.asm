#ifndef VJXX_CASCADE_CLASSIFIER_H_
#define VJXX_CASCADE_CLASSIFIER_H_

#include <stdbool.h>

#include "integral_image.h"
#include "strong_classifier.h"

typedef struct {
	unsigned char no_stages;
} vjxx_cascade_classifier_t;

bool vjxx_cascade_classify(
	vjxx_cascade_classifier_t classifier,
	vjxx_area_t *area_cursor,
	vjxx_weak_classifier_t *weak_classifier_cursor,
	vjxx_strong_classifier_t *strong_classifier_cursor,
	vjxx_integral_image_t picture,
	unsigned int x0,
	unsigned int y0
);

#endif
