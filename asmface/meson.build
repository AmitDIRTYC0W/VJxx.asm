asmface_inc = include_directories('include')
subdir('src')

asmface_dep = declare_dependency(
	link_with: asmface_lib,
	include_directories: asmface_inc,
)

subdir('tests')