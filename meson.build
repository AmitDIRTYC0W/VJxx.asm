project(
	'asm-face',
	'c',
	version: '0.1.0',
    meson_version: '>= 0.59.0',
    default_options: [
    	'warning_level=2',
    	'werror=false',
    	'c_std=c99',
    ],
)

add_project_arguments(
	[ '-I' + meson.project_build_root(), ],
	language: 'c',
)

subdir('asmface')
subdir('src')