#include "haar_features.h"

int horizontal_edge_feature(
	struct integral_image img,
	unsigned int x0,
	unsigned int y0,
	unsigned int x1,
	unsigned int y1
) {
	unsigned int height = y1 - y0;
  int area = height * (x1 - x0);
	unsigned int top = sum_area(img, x0, y0, x1, ((y0 << 1) + height) / 2);
	unsigned int bottom = sum_area(img, x0, ((y0 << 1) + height) / 2 + 1, x1, y1);
  unsigned int top_a = top / area;
  unsigned int bottom_a = bottom / area;
	int diff = top - bottom;

  int ret = diff / area;

	return ret;
}
