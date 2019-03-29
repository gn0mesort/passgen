project(
  'passgen',
  'cpp',
  version: '1.0.0',
  default_options: [
    'cpp_std=c++17',
    'cpp_args=-Wall -Wextra -Wpedantic'
  ]
)

name = meson.project_name()
version = meson.project_version()
arch = host_machine.cpu_family()
system = host_machine.system()

add_project_arguments(
  '-DMT_VERSION="' + version + '"',
  language: 'cpp'
)

deps = []
incs = [
  include_directories('include')
]
srcs = [
  'src/main.cpp',
  'src/passgen.cpp'
]

exe = executable(
  name + '.' + version + '.' + arch,
  srcs,
  dependencies: deps,
  include_directories: incs,
  install: true
)

custom_target(
  'compress_man',
  command: [
    find_program('scripts/compress_man.sh'),
    '@INPUT@',
    '@OUTPUT@'
  ],
  input: 'passgen.1',
  output: 'passgen.1.gz',
  build_by_default: true,
  install: true,
  install_dir: join_paths(get_option('mandir'), 'man1')
)

custom_target(
  'create_symlink',
  command: [
    find_program('scripts/create_symlink.sh'),
    '@INPUT@',
    '@OUTPUT@'
  ],
  input: exe,
  output: name,
  build_by_default: true,
  install: true,
  install_dir: get_option('bindir')
)
