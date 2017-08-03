#.rst:
# FindMKL
# ---------
#
# Locate the Intel Math Kernel Library.
#

if(NOT INTEL_ROOT)
  if(DEFINED ENV{INTELROOT})
    set(INTEL_ROOT "$ENV{INTELROOT}")
  elseif(DEFINED ENV{INTEL_ROOT})
    set(INTEL_ROOT "$ENV{INTEL_ROOT}")
  endif()
endif()

if(NOT MKL_ROOT)
  if(DEFINED ENV{MKLROOT})
    set(MKL_ROOT "$ENV{MKLROOT}")
  elseif(DEFINED ENV{MKL_ROOT})
    set(MKL_ROOT "$ENV{MKL_ROOT}")
  elseif(DEFINED INTEL_ROOT)
    get_filename_component(MKL_ROOT "${INTEL_ROOT}/../mkl" REALPATH)
  endif()
endif()

unset(MKL_FLAG CACHE)
unset(MKL_INCLUDE CACHE)
unset(MKL_LIBRARY_CORE CACHE)
unset(MKL_LIBRARY_THREAD CACHE)
unset(MKL_LIBRARY_LP CACHE)

################################################################################

if(NOT MKL_ILP64)
  set(mkllib  "mkl_intel_lp64")
  set(mklflag "-m64")
else()
  set(mkllib  "mkl_intel_ilp64")
  set(mklflag "-DMKL_ILP64 -m64")
endif()

################################################################################

set(MKL_FLAG "${mklflag}" CACHE PATH "The compiler flag of Intel MKL." FORCE)

################################################################################

find_path(
  MKL_INCLUDE mkl.h
  HINTS "${MKL_ROOT}/include"
  DOC "The include directory of Intel MKL."
)

################################################################################

find_library(
  MKL_LIBRARY_CORE
  NAMES mkl_core
  HINTS "${MKL_ROOT}/lib/intel64"
  DOC "The core library of Intel MKL."
)

if(MKL_OMP STREQUAL "GOMP")
  find_library(
    MKL_LIBRARY_GNU_THREAD
    NAMES mkl_gnu_thread
    HINTS "${MKL_ROOT}/lib/intel64"
    DOC "The GNU thread library of Intel MKL."
  )
  set(MKL_LIBRARY_THREAD ${MKL_LIBRARY_GNU_THREAD})
elseif(MKL_OMP STREQUAL "IOMP")
  find_library(
    MKL_LIBRARY_INTEL_THREAD
    NAMES mkl_intel_thread
    HINTS "${MKL_ROOT}/lib/intel64"
    DOC "The Intel thread library of Intel MKL."
  )
  set(MKL_LIBRARY_THREAD ${MKL_LIBRARY_INTEL_THREAD})
else()
  find_library(
    MKL_LIBRARY_SEQUENTIAL
    NAMES mkl_sequential
    HINTS "${MKL_ROOT}/lib/intel64"
    DOC "The sequential library of Intel MKL."
  )
  set(MKL_LIBRARY_THREAD ${MKL_LIBRARY_SEQUENTIAL})
endif()

find_library(
  MKL_LIBRARY_LP
  NAMES ${mkllib}
  HINTS "${MKL_ROOT}/lib/intel64"
  DOC "The integer library of Intel MKL."
)

################################################################################

if(NOT MKL_ROOT AND MKL_INCLUDE)
  get_filename_component(MKL_ROOT "${MKL_INCLUDE}/.." REALPATH)
endif()

if(NOT INTEL_ROOT AND MKL_ROOT)
  get_filename_component(INTEL_ROOT "${MKL_ROOT}/../compiler" REALPATH)
endif()

set(MKL_ROOT "${MKL_ROOT}" CACHE PATH "The root path of Intel MKL." FORCE)
set(INTEL_ROOT "${INTEL_ROOT}" CACHE PATH "The root path of Intel Parallel Studio." FORCE)

################################################################################

include(FindPackageHandleStandardArgs)
set(MKL_LIBS "${MKL_LIBRARY_LP};${MKL_LIBRARY_THREAD};${MKL_LIBRARY_CORE}")
if(MKL_OMP)
  find_package_handle_standard_args(
    MKL DEFAULT_MSG MKL_LIBS MKL_LIBRARY_CORE MKL_LIBRARY_THREAD MKL_LIBRARY_LP MKL_INCLUDE MKL_FLAG
  )
else()
  find_package_handle_standard_args(
    MKL DEFAULT_MSG MKL_LIBS MKL_LIBRARY_CORE MKL_LIBRARY_THREAD MKL_LIBRARY_LP MKL_INCLUDE MKL_FLAG
  )
endif()

mark_as_advanced(MKL_LIBRARY_CORE MKL_LIBRARY_GNU_THREAD MKL_LIBRARY_INTEL_THREAD MKL_LIBRARY_SEQUENTIAL MKL_LIBRARY_LP MKL_INCLUDE MKL_FLAG)

set(MKL_INCLUDES  "${MKL_INCLUDE}")
set(MKL_LIBRARIES "-Wl,--no-as-needed" "${MKL_LIBRARY_LP}" "${MKL_LIBRARY_THREAD}" "${MKL_LIBRARY_CORE}" "m" "dl")
set(MKL_FLAGS     "${MKL_FLAG}")
