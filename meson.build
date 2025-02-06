project('drm-sandbox', 'c')

dep_libdrm = dependency('libdrm')

cc = meson.get_compiler('c')
cflags = [
    '-Wno-unused-parameter',
    '-fvisibility=hidden',
    '-Wmissing-prototypes',
    '-Wstrict-prototypes'
]

add_project_arguments(cflags, language: 'c')
add_project_arguments(cflags, language: 'cpp')

executable('01-rpi-version-ioctl',
    '01-rpi-version-ioctl.c',
    dependencies: [dep_libdrm]
)

executable('cursor-size',
    'cursor-size.c',
    dependencies: [dep_libdrm]
)

executable('in_formats',
    'in_formats.c',
    dependencies: [dep_libdrm]
)

executable('plane-alpha-prop',
    'plane-alpha-prop.c',
    dependencies: [dep_libdrm]
)
