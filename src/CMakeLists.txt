# The CMake setting of 'src/'

isvd_set_config_var()

SET(BUILD_SHARED_LIBS ON)

# RPath
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${LIB_FOLDER}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

# Macro
macro(SET_TARGET target files)
  # Set library
  add_library(${target} SHARED ${files})
  isvd_set_target(${target})
  set_property(TARGET ${target} PROPERTY VERSION ${ISVD_VERSION})
  install(TARGETS ${target} LIBRARY DESTINATION ${LIB_FOLDER})
endmacro()

# Set include paths
include_directories("${PROJECT_CONFIG_DIR}/include/c"
                    "${CMAKE_CURRENT_CONFIG_DIR}")

# Configure files
isvd_configure_x_fn("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_CONFIG_DIR}" "${ISVD_S_TYPES}")
isvd_configure_x_fn("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_CONFIG_DIR}" "${ISVD_D_TYPES}")
isvd_configure_fn("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_CONFIG_DIR}")

# Break
if(NOT ISVD_BUILD_LIB)
  return()
endif()

# libisvd
set_target(isvd /dev/null)
set_property(TARGET isvd PROPERTY LINKER_LANGUAGE C)

# libisvd_core
file(GLOB_RECURSE files "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/core/*"
                        "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/util/*")
set_target(isvd_core "${files}")
isvd_set_target_omp(isvd_core C)
isvd_set_target_mpi(isvd_core C)
isvd_set_target_blas(isvd_core)
target_link_libraries(isvd isvd_core)

# libisvd_la
if(ISVD_OMP)
  string(TOLOWER ${ISVD_OMP} isvd_omp)
  set(isvd_omp "_${isvd_omp}")
else()
  set(isvd_omp "")
endif()
if(ISVD_USE_MKL)
  set(isvd_la isvd_la_mkl${isvd_omp})
else()
  set(isvd_la isvd_la_blas${isvd_omp})
endif(ISVD_USE_MKL)
file(GLOB_RECURSE files "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/la/*")
set_target(${isvd_la} "${files}")
isvd_set_target_omp(${isvd_la} C)
isvd_set_target_mpi(${isvd_la} C)
isvd_set_target_blas(${isvd_la})
target_link_libraries(isvd ${isvd_la})

# libisvd_gpu_none
file(GLOB_RECURSE files "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/nogpu/*")
set_target(isvd_gpu_none "${files}")
isvd_set_target_omp(isvd_gpu_none C)
isvd_set_target_mpi(isvd_gpu_none C)
isvd_set_target_blas(isvd_gpu_none)

# libisvd_gpu
if(ISVD_USE_GPU)
  file(GLOB_RECURSE files "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/gpu/*")
  set_target(isvd_gpu_magma "${files}")
  isvd_set_target_omp(isvd_gpu_magma C)
  isvd_set_target_mpi(isvd_gpu_magma C)
  isvd_set_target_blas(isvd_gpu_magma)
  isvd_set_target_gpu(isvd_gpu_magma)
  target_link_libraries(isvd isvd_gpu_magma)
else()
  target_link_libraries(isvd isvd_gpu_none)
endif(ISVD_USE_GPU)
