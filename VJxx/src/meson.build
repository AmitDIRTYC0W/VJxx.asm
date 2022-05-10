vjxx_src = [
	'haar_features.c',
	#'integral_image.c',
	'weak_classifier.c',
	'strong_classifier.c',
]

vjxx_src += nasm_gen.process([
	'integral_image.asm',
	#'haar_features.asm',
	'model.asm',
])

vjxx_lib = static_library(
	'VJxx',
	vjxx_src,
	include_directories: vjxx_inc,
)
