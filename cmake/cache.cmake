# Set install prefix
set(CMAKE_INSTALL_PREFIX "/opt/isvd-${ISVD_MAJOR_VERSION}.${ISVD_MINOR_VERSION}" CACHE PATH "Install path prefix, prepended onto install directories.")

# Set build type
set(CMAKE_BUILD_TYPE "Simple" CACHE STRING "Choose the type of build, options are: Simple Debug Release RelWithDebInfo MinSizeRel.")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Simple;Debug;Release;RelWithDebInfo;MinSizeRel")
if(NOT CMAKE_BUILD_TYPE STREQUAL "Simple" AND NOT CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT CMAKE_BUILD_TYPE STREQUAL "Release" AND NOT CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo" AND NOT CMAKE_BUILD_TYPE STREQUAL "MinSizeRel" )
  message(FATAL_ERROR "CMAKE_BUILD_TYPE must be either Simple, Debug, Release, RelWithDebInfo or MinSizeRel.")
endif()

# Set default flags
set(CMAKE_C_FLAGS       "-std=c99   -Wall -Wextra -pedantic -fPIC ${CMAKE_C_EXTRA_FLAGS}" CACHE STRING "Flags used by the compiler during all build types.")
set(CMAKE_CXX_FLAGS     "-std=c++98 -Wall -Wextra -pedantic -fPIC ${CMAKE_CXX_EXTRA_FLAGS}" CACHE STRING "Flags used by the compiler during all build types.")
if(ISVD_USE_FORTRAN)
  set(CMAKE_Fortran_FLAGS "-std=f95   -Wall -Wextra -pedantic -fPIC ${CMAKE_Fortran_EXTRA_FLAGS}" CACHE STRING "Flags used by the compiler during all build types.")
endif()

# Set core flags
set(CMAKE_C_FLAGS_SIMPLE   "-O2 -g" CACHE STRING "Flags used by the compiler during simple builds.")
set(CMAKE_CXX_FLAGS_SIMPLE "-O2 -g" CACHE STRING "Flags used by the compiler during simple builds.")
mark_as_advanced(CMAKE_C_FLAGS_SIMPLE CMAKE_CXX_FLAGS_SIMPLE)
if(ISVD_USE_FORTRAN)
  set(CMAKE_Fortran_FLAGS_SIMPLE "-O2 -g" CACHE STRING "Flags used by the compiler during simple builds.")
  mark_as_advanced(CMAKE_Fortran_FLAGS_SIMPLE)
endif()

# Set debug flags
set(CMAKE_C_FLAGS_DEBUG   "-O1 -g -fsanitize=address" CACHE STRING "Flags used by the compiler during debug builds.")
set(CMAKE_CXX_FLAGS_DEBUG "-O1 -g -fsanitize=address" CACHE STRING "Flags used by the compiler during debug builds.")
if(ISVD_USE_FORTRAN)
  set(CMAKE_Fortran_FLAGS_DEBUG "-O1 -g -fsanitize=address" CACHE STRING "Flags used by the compiler during debug builds.")
  mark_as_advanced(CMAKE_Fortran_FLAGS_DEBUG)
endif()
