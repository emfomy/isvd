# The main CMake setting

# Set project
project(ISVD)
# cmake_minimum_required(VERSION 3.0)
cmake_minimum_required(VERSION 2.8.12)
set(ISVD_NAME "Integrated Singular Value Decomposition")

# Set version number
set(ISVD_MAJOR_VERSION 1)
set(ISVD_MINOR_VERSION 0)
set(ISVD_PATCH_VERSION 2)
set(ISVD_VERSION "${ISVD_MAJOR_VERSION}.${ISVD_MINOR_VERSION}.${ISVD_PATCH_VERSION}")

# Set Makefile
set(CMAKE_COLOR_MAKEFILE ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Set module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# Include functions
include(cmake/functions.cmake)

# Sets the options
include(cmake/options.cmake)

# Sets the packages
include(cmake/packages.cmake)

# Add subdirectories
add_subdirectory(ext)
add_subdirectory(src)
add_subdirectory(demo)
add_subdirectory(check)
add_subdirectory(doxygen)

# Sets the flags
include(cmake/flags.cmake)

# Create configure files
include(cmake/configure.cmake)

# Display message
include(cmake/display.cmake)
