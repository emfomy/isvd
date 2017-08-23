#.rst:
# FindOpenMPLib
# ---------
#
# Locate the OpenMP Library.
#

if(OpenMP STREQUAL "GOMP")

  set(GOMP_LIBRARY "gomp" CACHE STRING "The GNU thread library.")

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
