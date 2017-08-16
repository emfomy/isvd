# Set default variables
set(INCS "")
set(LIBS "")
set(DEFS "")
set(COMFLGS "")
set(LNKFLGS "")

# Set install prefix
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "/opt/isvd-${ISVD_MAJOR_VERSION}.${ISVD_MINOR_VERSION}" CACHE PATH "The install path prefix." FORCE)
endif()

# Set options
option(ISVD_BUILD_LIB     "Build libraries."      "ON")
option(ISVD_BUILD_DRIVER  "Build driver codes."   "ON")
option(ISVD_BUILD_DEMO    "Build demo codes."     "ON")
option(ISVD_BUILD_TEST    "Build test codes."     "OFF")
option(ISVD_BUILD_DOC     "Build documentation."  "OFF")
option(ISVD_USE_GPU       "Enable GPU support."   "OFF")

set(ISVD_INDEX_TYPE "32" CACHE STRING "Index type. [32/64]")
set_property(CACHE ISVD_INDEX_TYPE PROPERTY STRINGS "32;64")
if(NOT ISVD_INDEX_TYPE STREQUAL "32" AND NOT ISVD_INDEX_TYPE STREQUAL "64" )
  message(FATAL_ERROR "ISVD_INDEX_TYPE must be either 32 or 64")
endif()

# set(ISVD_BLAS "BLAS" CACHE STRING "Selected BLAS/LAPACK library. [BLAS/MKL]")
# set_property(CACHE ISVD_BLAS PROPERTY STRINGS "BLAS;MKL")
# if(NOT ISVD_BLAS STREQUAL "BLAS" AND NOT ISVD_BLAS STREQUAL "MKL" )
#   message(FATAL_ERROR "BLAS must be either BLAS or MKL")
# endif()
set(ISVD_BLAS "MKL" CACHE STRING "Selected BLAS/LAPACK library. [BLAS/MKL]")
set_property(CACHE ISVD_BLAS PROPERTY STRINGS "MKL")
if(NOT ISVD_BLAS STREQUAL "MKL" )
  message(FATAL_ERROR "BLAS must be MKL")
endif()

set(ISVD_OMP "OFF" CACHE STRING "Selected OpenMP library. [OFF/GOMP/IOMP] (Require 'ISVD_BLAS = MKL')")
set_property(CACHE ISVD_OMP PROPERTY STRINGS "OFF;GOMP;IOMP")
if(NOT ISVD_OMP STREQUAL "OFF" AND NOT ISVD_OMP STREQUAL "GOMP" AND NOT ISVD_OMP STREQUAL "IOMP" )
  message(FATAL_ERROR "ISVD_OMP must be either OFF, GOMP, or IOMP")
endif()

set(MPI_PROCS 4 CACHE STRING "The number of MPI processes used in demo codes.")
set(OMP_PROCS 4 CACHE STRING "The number of OpenMP processes used in demo codes.")

# Set variables
if(ISVD_BUILD_DEMO OR ISVD_BUILD_DRIVER OR ISVD_BUILD_LIB OR ISVD_BUILD_TEST)
  set(ISVD_BUILD_BIN "ON")
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
  list(APPEND DEFS "ISVD_USE_ILP64")
endif()

if(ISVD_BLAS STREQUAL "MKL")
  list(APPEND DEFS "ISVD_USE_MKL")
  set(MKL_ILP64 ${ISVD_USE_ILP64})
  set(ISVD_USE_MKL "ON")
else()
  unset(MKL_ILP64)
  set(ISVD_USE_MKL "OFF")
endif()

set(MKL_OMP ${ISVD_OMP})

if(ISVD_USE_GPU)
  list(APPEND DEFS "ISVD_USE_GPU")
  if(ISVD_USE_ILP64)
    list(APPEND DEFS "MAGMA_ILP64")
  endif()
endif()

# Enable testing
if(ISVD_BUILD_TEST)
  enable_testing()
endif()
