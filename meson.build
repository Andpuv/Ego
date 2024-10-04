project('ego', 'c',
  version: '0.0.1',
  default_options: ['c_std=c99', 'warning_level=2']
)

# Find the Python3 executable

python3_executable = find_program('python3')

# Extract the build color from options

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

# Define the framework version information

# Run the Python script to convert the string to uppercase

scripts = files('res/scripts/to_uppercase.py')
result  = run_command(python3_executable, scripts, color, check: true)

# When {check:false} use this:
# ```meson
# if result.returncode() != 0
#   error('Error: cannot convert the color into its uppercase representation.')
# endif
# ```

# Set the color code for the version
framework_color = 'EGO_VERSION_COLOR_' + result.stdout().strip()

# Set the other version fields

framework_major = '0' # Set the major version number
framework_minor = '0' # Set the minor version number
framework_patch = '1' # Set the patch version number
framework_level = '0' # Set the level code for the version

# Configure the header file from the template

configured_version_header = configure_file(
  input:  'inc/config/ego-version.h.in',
  output: 'config-ego-version.h',
  configuration: {
    '__FRAMEWORK_VERSION_MAJOR__': framework_major,
    '__FRAMEWORK_VERSION_MINOR__': framework_minor,
    '__FRAMEWORK_VERSION_PATCH__': framework_patch,
    '__FRAMEWORK_VERSION_COLOR__': framework_color,
    '__FRAMEWORK_VERSION_LEVEL__': framework_level
  }
)

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
  include_dirname + '/ego.h',
)
headers += configured_version_header

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
