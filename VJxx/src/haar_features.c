#include "VJxx/haar_features.h"

// TODO This can be optimised much further (sum_area's parameters can be pre-
// calculated during training).

// TODO Actually think about this code (i.e. maximum values and such).

int vjxx_haar_x2(
	struct vjxx_integral_image img,
	unsigned int x0,
	unsigned int y0,
	unsigned int x1,
	unsigned int y1
) {
	unsigned int width = x1 - x0;
	unsigned int left = vjxx_sum_area(img, x0, y0, ((x0 * 2) + width) / 2, y1);
	unsigned int right = vjxx_sum_area(img, x0, y0, ((x0 * 2) + width) / 2 + 1, y1);
  return left - right;
}

int vjxx_haar_y2(
	struct vjxx_integral_image img,
	unsigned int x0,
	unsigned int y0,
	unsigned int x1,
	unsigned int y1
) {
	unsigned int height = y1 - y0;
	unsigned int top = vjxx_sum_area(img, x0, y0, x1, ((y0 * 2) + height) / 2);
	unsigned int bottom = vjxx_sum_area(img, x0, ((y0 * 2) + height) / 2 + 1, x1, y1);
	return top - bottom;
}

int vjxx_haar_x3(
  struct vjxx_integral_image img,
  unsigned int x0,
  unsigned int y0,
  unsigned int x1,
  unsigned int y1
) {
  unsigned int width = x1 - x0;
  unsigned int left = vjxx_sum_area(img, x0, y0, ((x0 * 3) + width) / 3, y1);
  unsigned int middle = vjxx_sum_area(img, ((x0 * 3) + width) / 3 + 1, y0, ((x0 * 3) + 2 * width) / 3, y1);
  unsigned int right = vjxx_sum_area(img, ((x0 * 3) + 2 * width) / 3 + 1, y0, x1, y1);
  return left + right - middle;
}


int vjxx_haar_y3(
  struct vjxx_integral_image img,
  unsigned int x0,
  unsigned int y0,
  unsigned int x1,
  unsigned int y1
) {
  unsigned int height = y1 - y0;
  unsigned int top = vjxx_sum_area(img, x0, y0, x1, ((y0 * 3) + height) / 3);
  unsigned int middle = vjxx_sum_area(img, x0, ((y0 * 3) + height) / 3 + 1, x1, ((y0 * 3) + 2 * height) / 3);
  unsigned int bottom = vjxx_sum_area(img, x0, ((y0 * 3) + 2 * height) / 3, x1, y1);
  return top + bottom - middle;
}

int vjxx_haar_x2y2(
  struct vjxx_integral_image img,
  unsigned int x0,
  unsigned int y0,
  unsigned int x1,
  unsigned int y1
) {
  unsigned int width = x1 - x0;
  unsigned int height = y1 - y0;
  unsigned int top_left = vjxx_sum_area(img, x0, y0, ((x0 * 2) + width) / 2, ((y0 * 2) + height) / 2);
  unsigned int top_right = vjxx_sum_area(img, ((x0 * 2) + width) / 2 + 1, y0, x1, ((y0 * 2) + height) / 2);
  unsigned int bottom_left = vjxx_sum_area(img, x0, ((y0 * 2) + height) / 2 + 1, ((x0 * 2) + width) / 2, y1);
  unsigned int bottom_right = vjxx_sum_area(img, ((x0 * 2) + width) / 2 + 1, ((y0 * 2) + height) / 2 + 1, x1, y1);
  return top_left + bottom_right - top_right - bottom_left;
}
