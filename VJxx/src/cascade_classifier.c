#include "VJxx/cascade_classifier.h"

bool vjxx_cascade_classify(
	vjxx_cascade_classifier_t classifier,
	vjxx_area_t *area_cursor,
	vjxx_weak_classifier_t *weak_classifier_cursor,
	vjxx_strong_classifier_t *strong_classifier_cursor,
	vjxx_integral_image_t picture,
	unsigned int x0,
	unsigned int y0
) {
	for (unsigned char i = 0; i < classifier.no_stages; i++) {
		if (
			!vjxx_strong_classify(
				*strong_classifier_cursor,
				area_cursor,
				weak_classifier_cursor,
				picture,
				x0,
				y0
			)
		) {
			printf("fehlgeschlagen bei:\t%d\n", i);
			return false;
		}
		strong_classifier_cursor++;
	}

	return true;
}
