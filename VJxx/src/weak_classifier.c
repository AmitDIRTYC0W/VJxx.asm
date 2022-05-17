#include "../include/VJxx/weak_classifier.h"

short vjxx_weak_classify(
	vjxx_weak_classifier_t classifier,
	vjxx_area_t *area_cursor,
	vjxx_integral_image_t picture,
	unsigned int x0,
	unsigned int y0
) {
	int value = 0;
	for (unsigned char i = 0; i < classifier.feature_length; i++) {
		value += vjxx_sum_area(*area_cursor, picture, x0, y0);
		area_cursor++;
	}

	return
		value <= classifier.threshold
		? classifier.alpha_positive
		: classifier.alpha_negative;
}
