pictures_dir = join_paths(meson.current_source_dir(), 'pictures')

test(
	'BMP parser (standard file)',
	executable(
		'bmp_parser_standard',
		'bmp_parser_standard.c',
		dependencies: vjxx_dep
	),
	args: [ pictures_dir ],
)
#test('BMP parser (non-fully-supported file)', ...)
#test('BMP parser (unsupported file)', ...)
#test('BMP parser (non-BMP file)', ...)
test(
	'Integral image generation',
	executable(
		'integral_image',
		'integral_image.c',
		dependencies: vjxx_dep
	),
)
test(
	'Area summing',
	executable(
		'sum_area',
		'sum_area.c',
		dependencies: vjxx_dep
	),
)
test(
	'X2 Haar feature',
	executable(
		'haar_x2',
		'haar_x2.c',
		dependencies: vjxx_dep
	),
)
