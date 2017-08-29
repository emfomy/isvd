# The CMake setting of 'demo/'

# Break
if(NOT ISVD_BUILD_DEMO)
  return()
endif()

# Macro
macro(SET_TARGET target files)
  # Set target
  add_executable(isvd_${target} EXCLUDE_FROM_ALL ${files})

  isvd_set_target(isvd_${target} "")

  # Add run rule
  add_custom_target(
    run_${target}
    COMMAND OMP_NUM_THREADS=${OMP_THRDS} ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPI_PROCS} $<TARGET_FILE:isvd_${target}> ${ARGN}
    DEPENDS isvd_${target}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running ${target}"
  )
endmacro()

# Set include paths
include_directories("${PROJECT_CONFIG_DIR}/include/c")

# Set target
set_target(ctest ctest.c)
add_dependencies(isvd_ctest isvd)
target_link_libraries(isvd_ctest isvd)
