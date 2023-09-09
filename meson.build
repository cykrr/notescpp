project(
  'fonts', ['c', 'cpp'],
  version: '0.0.1',
  default_options: ['cpp_std=c++1z']
)

fonts_files = files(
  'main.cpp',
  'src/args.cpp',
  'src/fonts.cpp',
  'lib/glad/src/glad.cpp',
  'lib/nanovg/nanovg.c'
)

notes = executable(
  'notes',
  [ fonts_files],
  dependencies:[
    dependency('glfw3'),
    dependency('freetype2'),
    dependency('harfbuzz'),
    dependency('fontconfig'),
    dependency('cairo'),
    dependency('xkbcommon'),
    ],
  include_directories: [
    include_directories('include'),
    include_directories('lib'),
    include_directories('lib/nanovg'),
    include_directories('lib/glad/include'),
    ]
  )
