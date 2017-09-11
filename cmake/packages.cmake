if(ISVD_BUILD_BIN)
  set(findtype REQUIRED)
else()
  set(findtype "")
endif()

# Check compiler support
if(ISVD_BUILD_BIN)
  string(REGEX REPLACE " " ";" cflags "${CMAKE_C_FLAGS}")
  include(CheckCCompilerFlag)
  foreach(cflag ${cflags})
    string(TOUPPER ${cflag} cflagname)
    string(REGEX REPLACE "=" "_" cflagname ${cflagname})
    string(REGEX REPLACE "\\+" "X" cflagname ${cflagname})
    CHECK_C_COMPILER_FLAG(${cflag} C_SUPPORTS_${cflagname})
    if(NOT C_SUPPORTS_${cflagname})
      message(
        FATAL_ERROR
        "The compiler ${CMAKE_C_COMPILER} does not support ${cflag}. "
        "Please use a different C compiler."
      )
    endif()
  endforeach()

  string(REGEX REPLACE " " ";" cxxflags "${CMAKE_CXX_FLAGS}")
  include(CheckCXXCompilerFlag)
  foreach(cxxflag ${cxxflags})
    string(TOUPPER ${cxxflag} cxxflagname)
    string(REGEX REPLACE "=" "_" cxxflagname ${cxxflagname})
    string(REGEX REPLACE "\\+" "X" cxxflagname ${cxxflagname})
    CHECK_CXX_COMPILER_FLAG(${cxxflag} CXX_SUPPORTS_${cxxflagname})
    if(NOT CXX_SUPPORTS_${cxxflagname})
      message(
        FATAL_ERROR
        "The compiler ${CMAKE_CXX_COMPILER} does not support ${cxxflag}. "
        "Please use a different CXX compiler."
      )
    endif()
  endforeach()
endif()

# Set target
find_library(
  M_LIBRARY
  NAMES m
  DOC "libm"
)
if(NOT M_LIBRARY)
  set(M_LIBRARY "-lm" CACHE STRING "libm" FORCE)
endif()
find_library(
  PTHREAD_LIBRARY
  NAMES pthread
  DOC "libpthread"
)
if(NOT PTHREAD_LIBRARY)
  set(PTHREAD_LIBRARY "-lpthread" CACHE STRING "libpthread" FORCE)
endif()
mark_as_advanced(M_LIBRARY PTHREAD_LIBRARY)

function(ISVD_SET_TARGET target)
  set_property(TARGET ${target} PROPERTY OUTPUT_NAME "${target}${BIN_SUFFIX}")
  target_link_libraries(${target} ${M_LIBRARY} ${PTHREAD_LIBRARY})
  set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS " -Wl,--no-as-needed")
endfunction()

# OpenMP
if(ISVD_OMP)
  set(OpenMP ${ISVD_OMP})
  find_package(OpenMP ${findtype})
  find_package(OpenMPLib ${findtype})
  unset(OpenMP)

  function(ISVD_SET_TARGET_OMP target lang)
    target_link_libraries(${target} ${OpenMP_LIBRARIES})
    set_property(TARGET ${target} APPEND_STRING PROPERTY COMPILE_FLAGS " ${OpenMP_${lang}_FLAGS}")
    set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS    " ${OpenMP_${lang}_FLAGS}")
  endfunction()
elseif(ISVD_USE_GPU)
  set(OpenMP "GOMP")
  find_package(OpenMP ${findtype})
  find_package(OpenMPLib ${findtype})
  unset(OpenMP)

  function(ISVD_SET_TARGET_OMP target lang)
    target_link_libraries(${target} ${OpenMP_LIBRARIES})
  endfunction()
else()
  function(ISVD_SET_TARGET_OMP target lang)
  endfunction()
endif()

# MPI
find_package(MPI ${findtype})
function(ISVD_SET_TARGET_MPI target lang)
  target_include_directories(${target} ${SYSTEM} PUBLIC "${MPI_${lang}_INCLUDE_PATH}")
  target_link_libraries(${target} ${MPI_${lang}_LIBRARIES})
  target_compile_definitions(${target} PUBLIC "OMPI_SKIP_MPICXX")
  target_compile_definitions(${target} PUBLIC "MPICH_SKIP_MPICXX")
  set_property(TARGET ${target} APPEND_STRING PROPERTY COMPILE_FLAGS " ${MPI_${lang}_COMPILE_FLAGS}")
  set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS    " ${MPI_${lang}_LINK_FLAGS}")
endfunction()

# MKL
if(ISVD_USE_MKL)
  find_package(MKL ${findtype})
  function(ISVD_SET_TARGET_BLAS target)
    target_include_directories(${target} ${SYSTEM} PUBLIC ${MKL_INCLUDES})
    target_link_libraries(${target} ${MKL_LIBRARIES})
    target_compile_definitions(${target} PUBLIC "ISVD_USE_MKL")
    set_property(TARGET ${target} APPEND_STRING PROPERTY COMPILE_FLAGS " ${MKL_FLAGS}")
  endfunction()
endif()

# LAPACK
if(NOT ISVD_USE_MKL)
  find_package(LAPACK ${findtype})
  function(ISVD_SET_TARGET_BLAS target)
    target_link_libraries(${target} ${LAPACK_LIBRARIES})
  endfunction()
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

  find_package(CUDA ${findtype})
  find_package(MAGMA ${findtype})

  set(CUDA_TOOLKIT_ROOT_DIR "${CUDA_TOOLKIT_ROOT_DIR}" CACHE PATH "The root path of CUDA toolkit." FORCE)
  unset(CUDA_TOOLKIT_ROOT_DIR)

  function(ISVD_SET_TARGET_GPU target)
    target_include_directories(${target} ${SYSTEM} PUBLIC ${MAGMA_INCLUDES} ${CUDA_INCLUDE_DIRS})
    target_link_libraries(${target} ${MAGMA_SPARSE_LIBRARY} ${MAGMA_LIBRARY} ${CUDA_cusparse_LIBRARY} ${CUDA_cublas_LIBRARY} ${CUDA_CUDART_LIBRARY})
    target_compile_definitions(${target} PUBLIC "ISVD_USE_GPU")
  endfunction()
else()
  function(ISVD_SET_TARGET_GPU target)
  endfunction()
endif()

# GTest
if(ISVD_BUILD_TEST)
  find_package(GTest 1.8 REQUIRED)

  function(ISVD_SET_TARGET_GTEST target)
    target_include_directories(${target} ${SYSTEM} PUBLIC ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${target} ${GTEST_BOTH_LIBRARIES})
    target_compile_definitions(${target} PUBLIC "ISVD_USE_GTEST")
    set_property(TARGET ${target} APPEND_STRING PROPERTY COMPILE_FLAGS " ${MPI_COMPILE_FLAGS}")
    set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS    " ${MPI_LINK_FLAGS}")
  endfunction()
endif()

# DOxygen
if(ISVD_BUILD_DOC)
  find_package(Doxygen REQUIRED)
endif()
