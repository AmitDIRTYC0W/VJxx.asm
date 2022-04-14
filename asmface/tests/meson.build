pictures_dir = join_paths(meson.current_source_dir(), 'pictures')

test(
	'BMP parser (standard file)',
	executable(
		'bmp_parser_standard',
		'bmp_parser_standard.c',
		dependencies: asmface_dep
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
		dependencies: asmface_dep
	),
)
test(
	'Area summing',
	executable(
		'sum_area',
		'sum_area.c',
		dependencies: asmface_dep
	),
)
