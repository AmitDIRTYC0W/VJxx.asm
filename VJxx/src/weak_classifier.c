#include "../include/VJxx/weak_classifier.h"

bool vjxx_weak_classify(
  vjxx_weak_classifier_t classifier,
  vjxx_integral_image_t img,
  unsigned int x0,
  unsigned int y0,
  unsigned int size,
) {
  int absolute_x0 = x0 + ((size * classifier.x0) >> size_shift);
  int absolute_y0 = y0 + ((size * classifier.y0) >> size_shift);
  int width = (size * classifier.width) >> size_shift;
  int height = (size * classifier.height) >> size_shift;

  int value;
  switch (classifier.feature_type) {
    case vjxx_feature_x2:
      value = vjxx_haar_x2(img, absolute_x0, absolute_y0, width, height);
    case vjxx_feature_y2:
      value = vjxx_haar_y2(img, absolute_x0, absolute_y0, width, height);
    case vjxx_feature_x3:
      value = vjxx_haar_x3(img, absolute_x0, absolute_y0, width, height);
    case vjxx_feature_y3:
      value = vjxx_haar_y3(img, absolute_x0, absolute_y0, width, height);
    case vjxx_feature_x2y2:
      value = vjxx_haar_x2y2(img, absolute_x0, absolute_y0, width, height);
  }

  return value * classifier.parity > classifier.threshold * width * height * classifier.parity;
}
