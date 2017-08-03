# Set complier flags
set(CMAKE_C_FLAGS "-std=c11 -O2 -g -Wall -Wextra -pedantic")
# set(CMAKE_C_FLAGS "-std=c11 -O0 -g -fsanitize=address -Wall -Wextra -pedantic")

if(ISVD_BUILD_BIN)
  set(findtype REQUIRED)
else()
  set(findtype "")
endif()

# Check compiler support
if(ISVD_BUILD_BIN)
  include(CheckCCompilerFlag)
  CHECK_C_COMPILER_FLAG("-std=c11" COMPILER_SUPPORTS_C11)
  if(NOT COMPILER_SUPPORTS_C11)
    message(
      FATAL_ERROR
      "The compiler ${CMAKE_C_COMPILER} has no C11 support. "
      "Please use a different C compiler."
    )
  endif()
endif()

# MPI
find_package(MPI ${findtype})
if(MPI_FOUND)
  list(APPEND INCS "${MPI_INCLUDE_PATH}")
  list(APPEND LIBS "${MPI_LIBRARIES}")
  set(COMFLGS "${COMFLGS} ${MPI_COMPILE_FLAGS}")
  set(LNKFLGS "${LNKFLGS} ${MPI_LINK_FLAGS}")
endif()

# MKL
if(ISVD_USE_MKL)
  find_package(MKL ${findtype})
  if(MKL_FOUND)
    list(APPEND INCS "${MKL_INCLUDES}")
    list(APPEND LIBS "${MKL_LIBRARIES}")
    set(COMFLGS "${COMFLGS} ${MKL_FLAGS}")
  endif()
endif()

# LAPACK
if(NOT ISVD_USE_MKL)
  find_package(LAPACK ${findtype})
  if(LAPACK_FOUND)
    list(APPEND LIBS "${LAPACK_LIBRARIES}")
  endif()
endif()

# CUDA & MAGMA
if(ISVD_USE_GPU)
  if(NOT CUDA_TOOLKIT_ROOT_DIR)
    if(DEFINED ENV{CUDA_TOOLKIT_ROOT_DIR})
      set(CUDA_TOOLKIT_ROOT_DIR "$ENV{CUDA_TOOLKIT_ROOT_DIR}")
    elseif(DEFINED ENV{CUDADIR})
      set(CUDA_TOOLKIT_ROOT_DIR "$ENV{CUDADIR}")
    endif()
  endif()
  set(CUDA_TOOLKIT_ROOT_DIR "${CUDA_TOOLKIT_ROOT_DIR}" CACHE PATH "The root path of CUDA toolkit." FORCE)

  find_package(CUDA ${findtype})
  find_package(MAGMA ${findtype})
  if(MAGMA_FOUND)
    list(APPEND INCS "${MAGMA_INCLUDES}")
    list(APPEND LIBS "${MAGMA_SPARSE_LIBRARY}" "${MAGMA_LIBRARY}")
  endif()
  if(CUDA_FOUND)
    list(APPEND INCS "${CUDA_INCLUDE_DIRS}")
    list(APPEND LIBS "${CUDA_cusparse_LIBRARY}" "${CUDA_cublas_LIBRARY}" "${CUDA_CUDART_LIBRARY}")
  endif()
endif()

# OpenMP
if(ISVD_OMP)
  set(OpenMP ${ISVD_OMP})

  find_package(OpenMP ${findtype})
  if(OpenMP_FOUND)
    set(COMFLGS "${COMFLGS} ${OpenMP_C_FLAGS}")
    set(LNKFLGS "${LNKFLGS} ${OpenMP_C_FLAGS}")
  endif()

  find_package(OpenMPLib ${findtype})
  if(OpenMPLib_FOUND)
    list(APPEND LIBS "${OpenMP_LIBRARIES}" "pthread")
  endif()

  unset(OpenMP)
elseif(ISVD_USE_GPU)
  set(OpenMP "GOMP")

  find_package(OpenMP ${findtype})
  find_package(OpenMPLib ${findtype})
  if(OpenMPLib_FOUND)
    list(APPEND LIBS "${OpenMP_LIBRARIES}" "pthread")
  endif()

  unset(OMP_LIBRARY)
  unset(OpenMP)
endif()

# GTest
if(ISVD_BUILD_TEST)
  find_package(GTest 1.8 REQUIRED)
endif()

# DOxygen
if(ISVD_BUILD_DOC)
  find_package(Doxygen REQUIRED)
endif()
