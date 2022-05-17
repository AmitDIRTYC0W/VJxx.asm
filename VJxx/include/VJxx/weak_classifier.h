#ifndef VJXX_WEAK_CLASSIFIER_H_
#define VJXX_WEAK_CLASSIFIER_H_

#include <stdbool.h>

#include "integral_image.h"
#include "area.h"

typedef struct {
	unsigned char feature_length;

	int threshold;

	short alpha_negative, alpha_positive;
} vjxx_weak_classifier_t;

short vjxx_weak_classify(
	vjxx_weak_classifier_t classifier,
	vjxx_area_t *area_cursor,
	vjxx_integral_image_t picture,
	unsigned int x0,
	unsigned int y0
);

#endif
