# The CMake setting of 'check/src'

isvd_set_config_var()

# Configure files
file(COPY "${PROJECT_CONFIG_DIR}/src/" DESTINATION "${CMAKE_CURRENT_CONFIG_DIR}")
file(GLOB_RECURSE cfiles "${CMAKE_CURRENT_CONFIG_DIR}/*.c")
foreach(cfile ${cfiles})
  string(REGEX REPLACE "\\.c$" ".cxx" cxxfile ${cfile})
  file(RENAME ${cfile} ${cxxfile})
endforeach()

file(RENAME "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/core/param.cxx"
            "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/core/param.c")

# checkisvd
file(GLOB_RECURSE files "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/core/*"
                        "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/la/*"
                        "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/util/*"
                        "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/nogpu/*")
add_library(checkisvd EXCLUDE_FROM_ALL ${files})
isvd_set_target(checkisvd)
isvd_set_target_omp(checkisvd CXX)
isvd_set_target_mpi(checkisvd CXX)
isvd_set_target_blas(checkisvd)
isvd_set_target_gtest(checkisvd)

# checkisvd_gpu
if(ISVD_USE_GPU)
  file(GLOB_RECURSE files "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/core/*"
                          "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/la/*"
                          "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/util/*"
                          "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/gpu/*")
  add_library(checkisvd_gpu EXCLUDE_FROM_ALL ${files})
  isvd_set_target(checkisvd_gpu)
  isvd_set_target_omp(checkisvd_gpu CXX)
  isvd_set_target_mpi(checkisvd_gpu CXX)
  isvd_set_target_blas(checkisvd_gpu)
  isvd_set_target_gpu(checkisvd_gpu)
  isvd_set_target_gtest(checkisvd_gpu)
endif()
