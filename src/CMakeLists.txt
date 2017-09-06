# The CMake setting of 'src/'

isvd_set_config_var()

# Break
if(NOT ISVD_BUILD_LIB)
  return()
endif()

# RPath
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${LIB_FOLDER}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

# Macro
macro(SET_TARGET target files)
  # Set library
  add_library(${target} SHARED ${files})
  isvd_set_target(${target} ".so")
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

# libisvd
set_target(isvd /dev/null)
set_property(TARGET isvd PROPERTY LINKER_LANGUAGE C)

# libisvd_la
file(GLOB_RECURSE files "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/la/*")
set_target(isvd_la "${files}")
isvd_set_target_omp(isvd_la C)
isvd_set_target_mpi(isvd_la)
isvd_set_target_blas(isvd_la)
target_link_libraries(isvd isvd_la)

# libisvd_core
file(GLOB_RECURSE files "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/core/*")
set_target(isvd_core "${files}")
isvd_set_target_omp(isvd_core C)
isvd_set_target_mpi(isvd_core)
isvd_set_target_blas(isvd_core)
target_link_libraries(isvd_core isvd_la)
target_link_libraries(isvd isvd_core)

# libisvd_nogpu
file(GLOB_RECURSE files "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/nogpu/*")
set_target(isvd_nogpu "${files}")
isvd_set_target_omp(isvd_nogpu C)
isvd_set_target_mpi(isvd_nogpu)
isvd_set_target_blas(isvd_nogpu)
target_link_libraries(isvd_nogpu isvd_core)

# libisvd_gpu
if(ISVD_USE_GPU)
  file(GLOB_RECURSE files "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/gpu/*")
  set_target(isvd_gpu "${files}")
  isvd_set_target_omp(isvd_gpu C)
  isvd_set_target_mpi(isvd_gpu)
  isvd_set_target_blas(isvd_gpu)
  isvd_set_target_gpu(isvd_gpu)
  target_link_libraries(isvd_gpu isvd_core)
  target_link_libraries(isvd isvd_gpu)
else()
  target_link_libraries(isvd isvd_nogpu)
endif(ISVD_USE_GPU)
