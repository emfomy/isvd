# check/check.cmake

macro(_ADD_CHECK_PREDO checktype)
  # Set target name
  get_filename_component(checkname ${checkpath} NAME)
  if(NOT ${checktype} STREQUAL "")
    set(checkname ${checkname}_${checktype})
  endif()
  set(checktarget isvd_check_${checkname})

  # Set target
  file(GLOB_RECURSE files "${CMAKE_CURRENT_CONFIG_DIR}/check/${checkpath}.*"
                          "${CMAKE_CURRENT_CONFIG_DIR}/check/${checkpath}/${checktype}.*"
                          "${CMAKE_CURRENT_CONFIG_DIR}/check/${checkpath}/${checktype}/*.*")
  list(SORT files)
  list(REVERSE files)
  add_executable(${checktarget} EXCLUDE_FROM_ALL ${checkmain} ${files})
  isvd_set_target(${checktarget})
  target_compile_definitions(${checktarget} PUBLIC "ISVD_CHECK_NAME=\"${checkcomment}\"")
  add_dependencies(build_check ${checktarget})
  list(REVERSE files)
endmacro()

################################################################################

macro(_ADD_CHECK checktype)
  set(checkmain check.cxx)
  _add_check_predo("${checktype}" "")

  # Add test
  if(ISVD_VERBOSE_TEST)
    gtest_add_tests($<TARGET_FILE:${checktarget}> "" ${checkmain} ${files})
  else()
    add_test(NAME ${checkname} COMMAND $<TARGET_FILE:${checktarget}>)
  endif()

  # Add rule
  add_custom_target(
    check_${checkname}
    COMMAND $<TARGET_FILE:${checktarget}>
    DEPENDS ${checktarget}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Run check ${checkpath}"
  )
endmacro()

macro(_ADD_MPI_CHECK checktype listprocs)
  set(checkmain check_mpi.cxx)
  _add_check_predo("${checktype}")

  # Add test
  if(ISVD_VERBOSE_TEST)
    gtest_add_mpi_tests($<TARGET_FILE:${checktarget}> "${listprocs}" "" ${checkmain} ${files})
  else()
    foreach(procs ${listprocs})
      add_test(NAME ${checkname}_${procs} COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${procs} ${CMAKE_ENV} ${ENVS} $<TARGET_FILE:${checktarget}>)
    endforeach()
  endif()

  # Add rule
  foreach(procs ${listprocs})
    add_custom_target(
      check_${checkname}_${procs}
      COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${procs} ${CMAKE_ENV} ${ENVS} $<TARGET_FILE:${checktarget}>
      DEPENDS ${checktarget}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Run check ${checkpath}"
    )
  endforeach()
endmacro()

################################################################################

function(ADD_CHECK_CPU checkpath checkcomment)
  _add_check("")
  isvd_set_target_check_cpu(${checktarget})
endfunction()

function(ADD_CHECK_GPU checkpath checkcomment)
  _add_check("")
  isvd_set_target_check_gpu(${checktarget})
endfunction()

################################################################################

function(ADD_MPI_CHECK_CPU checkpath checkcomment listprocs)
  _add_mpi_check("" "${listprocs}")
  isvd_set_target_check_cpu(${checktarget})
endfunction()

function(ADD_MPI_CHECK_GPU checkpath checkcomment listprocs)
  _add_mpi_check("" "${listprocs}")
  isvd_set_target_check_gpu(${checktarget})
endfunction()
