nasm = find_program('nasm')
nasm_gen = generator(
	nasm,
 	output  : '@BASENAME@.o',
	arguments : [
		'-f', meson.get_external_property('nasm_format'),
		'@INPUT@',
		'-o', '@OUTPUT@'
	]
)

vjxx_inc = include_directories('include')
subdir('src')

vjxx_dep = declare_dependency(
	link_with: vjxx_lib,
	include_directories: vjxx_inc,
)

subdir('tests')