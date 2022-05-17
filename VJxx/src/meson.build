vjxx_src = [
	'integral_image.c',
	'area.c',
	'weak_classifier.c',
	'strong_classifier.c',
	'cascade_classifier.c',
]

vjxx_src += nasm_gen.process([
	#'integral_image.asm',
	'model.asm',
])

vjxx_lib = static_library(
	'VJxx',
	vjxx_src,
	include_directories: vjxx_inc,
)
