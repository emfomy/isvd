#.rst:
# FindMAGMA
# ---------
#
# Locate the MAGMA Library.
#

if(NOT MAGMA_ROOT)
  if(DEFINED ENV{MAGMAROOT})
    set(MAGMA_ROOT "$ENV{MAGMAROOT}")
  elseif(DEFINED ENV{MAGMA_ROOT})
    set(MAGMA_ROOT "$ENV{MAGMA_ROOT}")
  elseif(DEFINED ENV{MAGMADIR})
    set(MAGMA_ROOT "$ENV{MAGMADIR}")
  endif()
endif()

################################################################################

find_path(
  MAGMA_INCLUDE magma.h
  HINTS "${MAGMA_ROOT}/include"
  DOC "The include directory of MAGMA."
)

find_library(
  MAGMA_LIBRARY
  NAMES magma
  HINTS "${MAGMA_ROOT}/lib"
  DOC "The library of MAGMA."
)

find_library(
  MAGMA_SPARSE_LIBRARY
  NAMES magma_sparse
  HINTS "${MAGMA_ROOT}/lib"
  DOC "The sparse library of MAGMA."
)

################################################################################

if(NOT MAGMA_ROOT AND DEFINED MAGMA_INCLUDE)
  get_filename_component(MAGMA_ROOT "${MAGMA_INCLUDE}/.." REALPATH)
endif()
set(MAGMA_ROOT "${MAGMA_ROOT}" CACHE PATH "The root path of MAGMA." FORCE)

################################################################################

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  MAGMA DEFAULT_MSG MAGMA_LIBRARY MAGMA_SPARSE_LIBRARY MAGMA_INCLUDE
)

mark_as_advanced(MAGMA_LIBRARY MAGMA_SPARSE_LIBRARY MAGMA_INCLUDE)

################################################################################

set(MAGMA_INCLUDES  "${MAGMA_INCLUDE}")
set(MAGMA_LIBRARIES "${MAGMA_SPARSE_LIBRARY}" "${MAGMA_LIBRARY}")
