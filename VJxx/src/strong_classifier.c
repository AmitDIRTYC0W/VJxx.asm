#include "VJxx/strong_classifier.h"

#include "VJxx/weak_classifier.h"

bool vjxx_strong_classify(
  vjxx_strong_classifier_t classifier,
  vjxx_integral_image_t image,
  unsigned int scale,
  unsigned char scale_shift // TODO: Make scale_shift constanttttt
) {
  int sum = 0;

  for (size_t i = 0; i < NO_WEAK_CLASSIFIERS; i++) {
    // TODO Use branchless programming.
    if (vjxx_weak_classify(classifier.classifiers[i], image, scale, scale_shift)) {
      sum += classifier.classifiers[i].alpha;
    }
  }

  return sum > 0;
}
