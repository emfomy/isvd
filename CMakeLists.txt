# The main CMake setting

cmake_minimum_required(VERSION 2.8.11)

# Compatibility with old versions
include(cmake/old.cmake)

# Set project
set(ISVD_NAME "Integrated Singular Value Decomposition")
set(ISVD_MAJOR_VERSION 1)
set(ISVD_MINOR_VERSION 3)
set(ISVD_PATCH_VERSION 2)
set(ISVD_VERSION "${ISVD_MAJOR_VERSION}.${ISVD_MINOR_VERSION}.${ISVD_PATCH_VERSION}")
if(NOT CMAKE_VERSION VERSION_LESS 3.0.0)
  cmake_policy(SET CMP0048 OLD)
endif()

# Set cache options
include(cmake/cache.cmake)

# Initialize project
project(ISVD)

# Set Makefile
set(CMAKE_COLOR_MAKEFILE ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Set module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# Variables
string(ASCII 27 Esc)

# Set the options
include(cmake/options.cmake)

# Set the packages
include(cmake/packages.cmake)

# Create configure files
include(cmake/configure.cmake)

# Set variables
include(cmake/vars.cmake)

# Add subdirectories
add_subdirectory(ext)
add_subdirectory(src)
add_subdirectory(demo)
add_subdirectory(share)
add_subdirectory(check)
add_subdirectory(doxygen)
add_subdirectory(cpplint)

# Display message
include(cmake/display.cmake)
