#.rst:
# FindOpenMPLib
# ---------
#
# Locate the OpenMP Library.
#

if(OpenMP STREQUAL "GOMP")

  list(APPEND CMAKE_FIND_LIBRARY_SUFFIXES .so.1)
  find_library(
    GOMP_LIBRARY
    NAMES gomp
    DOC "libgomp"
  )

  if(NOT GOMP_LIBRARY)
    set(GOMP_LIBRARY "-lgomp" CACHE STRING "The GNU thread library.")
  endif()

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(
    OpenMPLib DEFAULT_MSG GOMP_LIBRARY
  )

  set(OpenMP_LIBRARIES "${GOMP_LIBRARY}")

elseif(OpenMP STREQUAL "IOMP")

  find_library(
    IOMP_LIBRARY
    NAMES iomp5
    HINTS "${INTEL_ROOT}/lib/intel64" "${INTEL_ROOT}/compiler/lib/intel64"
    DOC "The Intel thread library."
  )

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(
    OpenMPLib DEFAULT_MSG IOMP_LIBRARY
  )

  set(OpenMP_LIBRARIES "${IOMP_LIBRARY}")

endif()
