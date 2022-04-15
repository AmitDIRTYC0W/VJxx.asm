#include "haar_features.h"

// TODO This can be optimised much further (sum_area's parameters can be pre-
// calculated during training).

// TODO Actually think about this code (i.e. maximum values and such).

char haar_x2(
	struct integral_image img,
	unsigned int x0,
	unsigned int y0,
	unsigned int x1,
	unsigned int y1
) {
	unsigned int width = x1 - x0;
  unsigned int area = width * (y1 - y0);
	unsigned int left = sum_area(img, x0, y0, ((x0 * 2) + width) / 2, y1);
	unsigned int right = sum_area(img, x0, y0, ((x0 * 2) + width) / 2 + 1, y1);
	int diff = left - right;
  return diff / area;
}

char haar_y2(
	struct integral_image img,
	unsigned int x0,
	unsigned int y0,
	unsigned int x1,
	unsigned int y1
) {
	unsigned int height = y1 - y0;
  unsigned int area = height * (x1 - x0);
	unsigned int top = sum_area(img, x0, y0, x1, ((y0 * 2) + height) / 2);
	unsigned int bottom = sum_area(img, x0, ((y0 * 2) + height) / 2 + 1, x1, y1);
	int diff = top - bottom;
  return diff / area;
}

char haar_x3(
  struct integral_image img,
  unsigned int x0,
  unsigned int y0,
  unsigned int x1,
  unsigned int y1
) {
  unsigned int width = x1 - x0;
  unsigned int area = width * (y1 - y0);
  unsigned int left = sum_area(img, x0, y0, ((x0 * 3) + width) / 3, y1);
  unsigned int middle = sum_area(img, ((x0 * 3) + width) / 3 + 1, y0, ((x0 * 3) + 2 * width) / 3, y1);
  unsigned int right = sum_area(img, ((x0 * 3) + 2 * width) / 3 + 1, y0, x1, y1);
  int diff = (left + right) / 2 - middle;
  return diff / area;
}


char haar_y3(
  struct integral_image img,
  unsigned int x0,
  unsigned int y0,
  unsigned int x1,
  unsigned int y1
) {
  unsigned int height = y1 - y0;
  unsigned int area = height * (x1 - x0);
  unsigned int top = sum_area(img, x0, y0, x1, ((y0 * 3) + height) / 3);
  unsigned int middle = sum_area(img, x0, ((y0 * 3) + height) / 3 + 1, x1, ((y0 * 3) + 2 * height) / 3);
  unsigned int bottom = sum_area(img, x0, ((y0 * 3) + 2 * height) / 3, x1, y1);
  int diff = (top + bottom) / 2 - middle;
  return diff / area;
}

char haar_x2y2(
  struct integral_image img,
  unsigned int x0,
  unsigned int y0,
  unsigned int x1,
  unsigned int y1
) {
  unsigned int width = x1 - x0;
  unsigned int height = y1 - y0;
  unsigned int area = width * height;
  unsigned int top_left = sum_area(img, x0, y0, ((x0 * 2) + width) / 2, ((y0 * 2) + height) / 2);
  unsigned int top_right = sum_area(img, ((x0 * 2) + width) / 2 + 1, y0, x1, ((y0 * 2) + height) / 2);
  unsigned int bottom_left = sum_area(img, x0, ((y0 * 2) + height) / 2 + 1, ((x0 * 2) + width) / 2, y1);
  unsigned int bottom_right = sum_area(img, ((x0 * 2) + width) / 2 + 1, ((y0 * 2) + height) / 2 + 1, x1, y1);
  int diff = top_left + bottom_right - top_right - bottom_left;
  return diff / area;
}
