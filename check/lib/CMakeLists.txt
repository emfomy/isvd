# The CMake setting of 'check/lib'

isvd_set_config_var()

# Configure files
file(COPY "${PROJECT_CONFIG_DIR}/src/lib/" DESTINATION "${CMAKE_CURRENT_CONFIG_DIR}")
file(GLOB_RECURSE cfiles "${CMAKE_CURRENT_CONFIG_DIR}/*.c")
foreach(cfile ${cfiles})
  string(REGEX REPLACE "\\.c$" ".cxx" cxxfile ${cfile})
  file(RENAME ${cfile} ${cxxfile})
endforeach()

file(RENAME "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/core/param.cxx"
            "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/core/param.c")

# checkisvd_core_la
file(GLOB_RECURSE files "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/core/*"
                        "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/la/*"
                        "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/util/*")
add_library(checkisvd_core_la EXCLUDE_FROM_ALL ${files})
isvd_set_target(checkisvd_core_la)
isvd_set_target_omp(checkisvd_core_la CXX)
isvd_set_target_mpi(checkisvd_core_la CXX)
isvd_set_target_blas(checkisvd_core_la)
isvd_set_target_gtest(checkisvd_core_la)

# checkisvd_gpu_none
file(GLOB_RECURSE files "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/nogpu/*")
add_library(checkisvd_gpu_none EXCLUDE_FROM_ALL ${files})
isvd_set_target(checkisvd_gpu_none)
isvd_set_target_mpi(checkisvd_gpu_none CXX)
isvd_set_target_gtest(checkisvd_gpu_none)

# checkisvd_gpu_magma
if(ISVD_USE_GPU)
  file(GLOB_RECURSE files "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/gpu/*")
  add_library(checkisvd_gpu_magma EXCLUDE_FROM_ALL ${files})
  isvd_set_target(checkisvd_gpu_magma)
  isvd_set_target_mpi(checkisvd_gpu_magma CXX)
  isvd_set_target_gpu(checkisvd_gpu_magma)
  isvd_set_target_gtest(checkisvd_gpu_magma)
endif()
