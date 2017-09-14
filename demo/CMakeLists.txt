# The CMake setting of 'demo/'

# Break
if(NOT ISVD_BUILD_DEMO)
  return()
endif()

# Macro
macro(SET_TARGET name files)
  set(target "isvd_${name}")
  add_executable(${target} EXCLUDE_FROM_ALL ${files})

  isvd_set_target(${target})

  # Add run rule
  add_custom_target(
    run_${name}
    COMMAND ${CMAKE_ENV} ${ENVS} ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPI_PROCS} $<TARGET_FILE:${target}> ${ARGN}
    DEPENDS ${target}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running ${name}"
  )
endmacro()

# Set include paths
include_directories("${PROJECT_BINARY_DIR}/include/c")

# C demo
set_target(cdemo cdemo.c ${PROJECT_SOURCE_DIR}/data/a.mtx /dev/null /dev/null /dev/null)
target_link_libraries(isvd_cdemo isvd extmmio)
target_include_directories(isvd_cdemo ${SYSTEM} PUBLIC "${PROJECT_SOURCE_DIR}/ext/mmio")

# C test
set_target(ctest ctest.c)
target_link_libraries(isvd_ctest isvd)
