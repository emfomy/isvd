# Check Compiler
if(CMAKE_C_COMPILER_ID STREQUAL "Intel" OR CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  set(ISVD_USE_ICC "ON")
else()
  set(ISVD_USE_ICC "OFF")
endif()

# Set options
option(ISVD_BUILD_LIB     "Build libraries."            "ON")
option(ISVD_BUILD_DEMO    "Build demo codes."           "ON")
option(ISVD_BUILD_TEST    "Build unit tests."           "OFF")
option(ISVD_BUILD_DOC     "Build documentation."        "ON")
option(ISVD_USE_GPU       "Enable GPU support."         "OFF")
option(ISVD_TEST_DEEP     "Enable deep unit tests."     "ON")
option(ISVD_TEST_VERBOSE  "Enable verbose unit tests."  "ON")

set(ISVD_INDEX_TYPE "32" CACHE STRING "Index type. [32/64]")
set_property(CACHE ISVD_INDEX_TYPE PROPERTY STRINGS "32;64")
if(NOT ISVD_INDEX_TYPE STREQUAL "32" AND NOT ISVD_INDEX_TYPE STREQUAL "64" )
  message(FATAL_ERROR "ISVD_INDEX_TYPE must be either 32 or 64")
endif()

set(ISVD_BLAS "BLAS" CACHE STRING "Selected BLAS/LAPACK library. [BLAS/MKL]")
set_property(CACHE ISVD_BLAS PROPERTY STRINGS "BLAS;MKL")
if(NOT ISVD_BLAS STREQUAL "BLAS" AND NOT ISVD_BLAS STREQUAL "MKL" )
  message(FATAL_ERROR "BLAS must be either BLAS or MKL")
endif()

set(ISVD_OMP "OFF" CACHE STRING "Selected OpenMP library. [OFF/GOMP/IOMP]")
unset(ISVD_OMP)
set_property(CACHE ISVD_OMP PROPERTY STRINGS "OFF;GOMP;IOMP")
if(NOT ISVD_OMP STREQUAL "OFF" AND NOT ISVD_OMP STREQUAL "GOMP" AND NOT ISVD_OMP STREQUAL "IOMP" )
  message(FATAL_ERROR "ISVD_OMP must be either OFF, GOMP, or IOMP")
endif()
if(ISVD_USE_ICC AND ISVD_OMP STREQUAL "GOMP")
  message(FATAL_ERROR "Intel ICC is not compatible with GNU OpenMP")
endif()

set(MPI_PROCS 4 CACHE STRING "The number of MPI processes used in demo codes.")
set(OMP_THRDS 4 CACHE STRING "The number of OpenMP threads used in demo/check codes.")

# Set variables
if(ISVD_BUILD_LIB OR ISVD_BUILD_DEMO OR ISVD_BUILD_TEST)
  set(ISVD_BUILD_BIN "ON")
else()
  set(ISVD_BUILD_BIN "OFF")
endif()

if(ISVD_INDEX_TYPE STREQUAL "32")
  set(BIN_SUFFIX "")
  set(BIN_FOLDER "bin")
  set(LIB_FOLDER "lib")
  set(ISVD_USE_ILP64 "OFF")
else()
  set(BIN_SUFFIX "_64")
  set(BIN_FOLDER "bin64")
  set(LIB_FOLDER "lib64")
  set(ISVD_USE_ILP64 "ON")
  set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -DISVD_USE_ILP64")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DISVD_USE_ILP64")
endif()

if(ISVD_BLAS STREQUAL "MKL")
  set(MKL_ILP64 ${ISVD_USE_ILP64})
  set(ISVD_USE_MKL "ON")
else()
  unset(MKL_ILP64)
  set(ISVD_USE_MKL "OFF")
endif()

set(MKL_OMP ${ISVD_OMP})
if(NOT ISVD_OMP)
  set(OMP_THRDS 1)
endif()

# Enable testing
if(ISVD_BUILD_TEST)
  enable_testing()
endif()

# Set environment variables
list(APPEND ENVS "OMP_NUM_THREADS=${OMP_THRDS}")
list(APPEND ENVS "ASAN_OPTIONS=color=always:protect_shadow_gap=0")
