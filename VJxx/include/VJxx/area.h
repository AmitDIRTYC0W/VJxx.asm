#ifndef VJXX_AREA_H_
#define VJXX_AREA_H_

#include "VJxx/integral_image.h"

#define SCALE_BS 12

typedef struct {
	unsigned char x0, y0, width, height;

	char weight;
} vjxx_area_t;

void vjxx_scale_area(
	vjxx_area_t source,
	vjxx_area_t *scaled,
	unsigned short scale
);

// This function returns the sum of all the values in a given area
// in an image. The ranges are exclusive.
int vjxx_sum_area(
	vjxx_area_t area,
 	vjxx_integral_image_t picture,
 	unsigned int x0,
 	unsigned int y0
);

#endif