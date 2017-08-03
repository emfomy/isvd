#.rst:
# FindOpenMPLib
# ---------
#
# Locate the OpenMP Library.
#

if(OpenMP STREQUAL "GOMP")
  set(GOMP_LIBRARY "gomp" CACHE STRING "The GNU thread library." FORCE)
  set(OMP_LIBRARY ${GOMP_LIBRARY})
elseif(OpenMP STREQUAL "IOMP")
  find_library(
    IOMP_LIBRARY
    NAMES iomp5
    HINTS "${INTEL_ROOT}/lib/intel64"
    DOC "The Intel thread library."
  )
  set(OMP_LIBRARY ${IOMP_LIBRARY})
else()
  unset(OMP_LIBRARY)
endif()

################################################################################

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  OpenMPLib DEFAULT_MSG OMP_LIBRARY
)

mark_as_advanced(OMP_LIBRARY)

set(OpenMP_LIBRARIES "${OMP_LIBRARY}")
