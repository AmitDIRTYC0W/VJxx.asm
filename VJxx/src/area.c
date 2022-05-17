#include "VJxx/area.h"

void vjxx_scale_area(
	vjxx_area_t source,
	vjxx_area_t *scaled,
	unsigned short scale
) {
	scaled->x0 = (source.x0 * scale) >> SCALE_BS;
	scaled->y0 = (source.y0 * scale) >> SCALE_BS;
	scaled->width = (source.width * scale) >> SCALE_BS;
	scaled->height = (source.height * scale) >> SCALE_BS;
}

int vjxx_sum_area(
	vjxx_area_t area,
	vjxx_integral_image_t picture,
	unsigned int x0,
	unsigned int y0
) {
	return 0;
	/*
	x0 += area.x0;
	y0 += area.y0;

	return 0;

	int value = picture.values[picture.width * y0 + x0];
	x0 += area.width;
	value -= picture.values[picture.width * y0 + x0];
	y0 += area.height;
	value += picture.values[picture.width * y0 + x0];
	x0 -= area.width;
	value += picture.values[picture.width * y0 + x0];

	value *= area.weight;

	return value;*/
}
