# check/check.cmake

macro(_ADD_CHECK_PREDO checktype)
  # Set target name
  get_filename_component(checkname ${checkpath} NAME)
  if(NOT ${checktype} STREQUAL "")
    set(checkname ${checkname}_${checktype})
  endif()
  set(checktarget isvd_check_${checkname})

  # Set target
  file(GLOB_RECURSE files "${CMAKE_CURRENT_SOURCE_DIR}/${checkpath}.*"
                          "${CMAKE_CURRENT_SOURCE_DIR}/${checkpath}/${checktype}.*"
                          "${CMAKE_CURRENT_SOURCE_DIR}/${checkpath}/${checktype}/*.*")
  list(SORT files)
  list(REVERSE files)
  add_executable(${checktarget} EXCLUDE_FROM_ALL ${checkmain} ${files})
  isvd_set_target(${checktarget} "")
  target_compile_definitions(${checktarget} PUBLIC "ISVD_CHECK_NAME=\"${checkcomment}\"")
  set(CMAKE_CHECK_TARGETS ${CMAKE_CHECK_TARGETS} ${checktarget} PARENT_SCOPE)
  list(REVERSE files)
endmacro()

################################################################################

macro(_ADD_CHECK checktype)
  set(checkmain check.cxx)
  _add_check_predo("${checktype}" "")
  gtest_add_tests($<TARGET_FILE:${checktarget}> "" ${checkmain} ${files})

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

  gtest_add_mpi_tests($<TARGET_FILE:${checktarget}> "${listprocs}" "" ${checkmain} ${files})

  # Add rule
  foreach(procs ${listprocs})
    add_custom_target(
      check_${checkname}_${procs}
      COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${procs} ${CMAKE_ENV} OMP_NUM_THREADS=${OMP_THRDS} $<TARGET_FILE:${checktarget}>
      DEPENDS ${checktarget}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Run check ${checkpath}"
    )
  endforeach()
endmacro()

################################################################################

function(ADD_CHECK checkpath checkcomment)
  _add_check("")
endfunction()

function(ADD_CHECK_TEST checkpath checkcomment)
  _add_check("test")
endfunction()

function(ADD_CHECK_DEATH checkpath checkcomment)
  list(REMOVE_ITEM DEFS "ISVD_USE_GTEST")
  _add_check("death_test")
endfunction()

################################################################################

function(ADD_MPI_CHECK checkpath checkcomment listprocs)
  _add_mpi_check("" "${listprocs}")
endfunction()
