#include "../include/VJxx/weak_classifier.h"

bool vjxx_weak_classify(
  struct vjxx_weak_classifier classifier,
  struct vjxx_integral_image img
) {
  int value;

  switch (classifier.feature) {
    case vjxx_feature_x2:
      value = vjxx_haar_x2(img, classifier.x0, classifier.y0, classifier.x1, classifier.y1);
    case vjxx_feature_y2:
      value = vjxx_haar_y2(img, classifier.x0, classifier.y0, classifier.x1, classifier.y1);
    case vjxx_feature_x3:
      value = vjxx_haar_x3(img, classifier.x0, classifier.y0, classifier.x1, classifier.y1);
    case vjxx_feature_y3:
      value = vjxx_haar_y3(img, classifier.x0, classifier.y0, classifier.x1, classifier.y1);
    case vjxx_feature_x2y2:
      value = vjxx_haar_x2y2(img, classifier.x0, classifier.y0, classifier.x1, classifier.y1);
  }

  short average_value = value / img.width * img.height;
  // TODO divide average_value by 40 and deviation...

  if (classifier.parity) {
    return value > classifier.threshold;
  } else {
    return value < classifier.threshold;
  }
}
