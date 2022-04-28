vjxx_src = [
	'bmp.c',
	'haar_features.c',
	#'integral_image.c',
	'weak_classifier.c',
]

vjxx_src += nasm_gen.process([
	'integral_image.asm',
])

vjxx_lib = static_library(
	'VJxx',
	vjxx_src,
	include_directories: vjxx_inc,
)
