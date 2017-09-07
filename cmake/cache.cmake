# Set install prefix
set(CMAKE_INSTALL_PREFIX "/opt/isvd-${ISVD_MAJOR_VERSION}.${ISVD_MINOR_VERSION}" CACHE PATH "Install path prefix, prepended onto install directories.")

# Set build type
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ";Debug;Release;RelWithDebInfo;MinSizeRel")
if(NOT CMAKE_BUILD_TYPE STREQUAL "" AND NOT CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT CMAKE_BUILD_TYPE STREQUAL "Release" AND NOT CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo" AND NOT CMAKE_BUILD_TYPE STREQUAL "MinSizeRel" )
  message(FATAL_ERROR "CMAKE_BUILD_TYPE must be either empty, Debug, Release, RelWithDebInfo or MinSizeRel.")
endif()

# Set default flags
set(CMAKE_C_FLAGS   "-std=c99   -Wall -Wextra -pedantic -fPIC ${CILP64}" CACHE STRING "Flags used by the compiler during all build types.")
set(CMAKE_CXX_FLAGS "-std=c++98 -Wall -Wextra -pedantic -fPIC ${CILP64}" CACHE STRING "Flags used by the compiler during all build types.")

# Set debug flags
set(CMAKE_C_FLAGS_DEBUG   "-O2 -g -fsanitize=address" CACHE STRING "Flags used by the compiler during debug builds.")
set(CMAKE_CXX_FLAGS_DEBUG "-O2 -g -fsanitize=address" CACHE STRING "Flags used by the compiler during debug builds.")
