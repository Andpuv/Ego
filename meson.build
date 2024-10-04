project('ego', 'c',
  version: '0.1',
  default_options: ['c_std=c99', 'warning_level=2']
)

color = get_option('color')
is_red_build   = 'red'   == color
is_green_build = 'green' == color
is_blue_build  = 'blue'  == color
is_gray_build  = 'gray'  == color

if is_red_build
  add_project_arguments('-g', '-DDEBUG', '-D__EGO_DEBUG__', language: 'c')
else
  add_project_arguments('-DNDEBUG', language: 'c')
endif

# Detect the headers, resources, sources, and tests

include_dirname  = 'inc'
resource_dirname = 'res'
source_dirname   = 'src'
test_dirname     = 'test'

include_directory  = include_directories(include_dirname)
resource_directory = include_directories(resource_dirname)
source_directory   = include_directories(source_dirname)
test_directory     = include_directories(test_dirname)

headers = files(
  include_dirname + '/ego-version.h',
  include_dirname + '/ego.h'
)

sources = files(
  source_dirname + '/ego-version.c'
)

resources = files(
  resource_dirname + '/project/' + color + '/ego-flame.svg',
  resource_dirname + '/project/' + color + '/ego-human.svg',
  resource_dirname + '/project/' + color + '/ego-name.svg'
)

# Framework libraries

framework_archive = static_library('ego',
  sources,
  install: true,
  include_directories: include_directory
)

framework_library = shared_library('ego',
  sources,
  install: true,
  include_directories: include_directory
)

# Unit tests

test_version = executable('test_version',
  'test/version.c',
  include_directories: include_directory,
  link_with: framework_archive
)

test('version test', test_version)

# Install headers and resources

install_headers(headers, subdir: 'ego')
install_data(resources, install_dir: 'share/ego')
