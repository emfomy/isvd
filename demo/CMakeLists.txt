# The CMake setting of 'demo/'

# Break
if(NOT ISVD_BUILD_DEMO)
  return()
endif()

# Macro
macro(SET_TARGET target files)
  # Set target
  add_executable(isvd_${target} EXCLUDE_FROM_ALL ${files})

  isvd_set_target(isvd_${target})

  # Add run rule
  add_custom_target(
    run_${target}
    COMMAND ${CMAKE_COMMAND} -E env OMP_NUM_THREADS=${OMP_THRDS} ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPI_PROCS} $<TARGET_FILE:isvd_${target}> ${ARGN}
    DEPENDS isvd_${target}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running ${target}"
  )
endmacro()

# Set include paths
include_directories("${PROJECT_CONFIG_DIR}/include/c")

# C demo
set_target(cdemo cdemo.c ${PROJECT_SOURCE_DIR}/data/a.mtx /dev/null /dev/null /dev/null)
target_link_libraries(isvd_cdemo isvd extmmio)
target_include_directories(isvd_cdemo SYSTEM PUBLIC "${PROJECT_SOURCE_DIR}/ext")
