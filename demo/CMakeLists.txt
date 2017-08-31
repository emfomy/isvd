# The CMake setting of 'demo/'

# Break
if(NOT ISVD_BUILD_DEMO)
  return()
endif()

# Macro
macro(SET_TARGET target files)
  # Set target
  add_executable(isvd_${target} EXCLUDE_FROM_ALL ${files})

  # Add run rule
  add_custom_target(
    run_${target}
    COMMAND OMP_NUM_THREADS=${OMP_THRDS} ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPI_PROCS} $<TARGET_FILE:isvd_${target}> ${ARGN}
    DEPENDS isvd_${target}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running ${target}"
  )
endmacro()

# C test
set_target(ctest ctest.c)
target_include_directories(isvd_ctest PUBLIC "${PROJECT_CONFIG_DIR}/include/c")
add_dependencies(isvd_ctest isvd)
target_link_libraries(isvd_ctest isvd)

# Fortran test
if(ISVD_USE_FORTRAN)
  set_target(ftest ftest.f90)
  target_include_directories(isvd_ftest PUBLIC "${PROJECT_CONFIG_DIR}/include/fortran")
  # add_dependencies(isvd_ftest isvd)
  # target_link_libraries(isvd_ftest isvd)
endif()
