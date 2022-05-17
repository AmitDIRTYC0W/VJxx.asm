#include "VJxx/strong_classifier.h"

#include "VJxx/integral_image.h"
#include "VJxx/weak_classifier.h"

bool vjxx_strong_classify(
  vjxx_strong_classifier_t classifier,
  vjxx_area_t *area_cursor,
  vjxx_weak_classifier_t *weak_classifier_cursor,
  vjxx_integral_image_t picture,
  unsigned int x0,
  unsigned int y0
) {
  int value = 0;
  for (unsigned char i = 0; i < classifier.no_weak_classifiers; i++) {
    value += vjxx_weak_classify(*weak_classifier_cursor, area_cursor, picture, x0, y0);
    weak_classifier_cursor++;
  }

  printf("wert.: %d\tschwelle.: %d\n", value, classifier.threshold);
  return value <= classifier.threshold;
}
