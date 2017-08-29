# The CMake setting of 'check/'

isvd_set_config_var()

# Break
if(NOT ISVD_BUILD_TEST)

  # Add rule 'check'
  add_custom_target(
    check
    COMMAND eval "exit 1"
    COMMENT "${Esc}[1;33mWarning: Unit tests are not enabled! Please set 'ISVD_BUILD_TEST' using ccmake.${Esc}[0m"
  )

  return()
endif()

# GTest
if(GTEST_FOUND)
  list(APPEND INCS "${GTEST_INCLUDE_DIRS}")
  list(APPEND LIBS "${GTEST_BOTH_LIBRARIES}")
  list(APPEND DEFS "ISVD_USE_GTEST")
endif()

# Set include paths
include_directories(
  "${PROJECT_CONFIG_DIR}/include/c"
  SYSTEM
  "${PROJECT_SOURCE_DIR}/ext"
)

# Add subdirectories
add_subdirectory(src)

# Set libraries
list(APPEND LIBS checkisvd)
list(APPEND LIBS extmmio)

# Set definitions
list(APPEND DEFS "-DISVD_DATA_PATH=\"${PROJECT_SOURCE_DIR}/data\"")

# Configure files
isvd_configure_x_fn("${CMAKE_CURRENT_SOURCE_DIR}/check" "${CMAKE_CURRENT_CONFIG_DIR}/check" "${ISVD_S_TYPES}")
isvd_configure_x_fn("${CMAKE_CURRENT_SOURCE_DIR}/check" "${CMAKE_CURRENT_CONFIG_DIR}/check" "${ISVD_D_TYPES}")
isvd_configure_in_fn("${CMAKE_CURRENT_SOURCE_DIR}/check" "${CMAKE_CURRENT_CONFIG_DIR}/check")

# Include macros
include(check.cmake)

# Set unit tests
macro(ISVD_CHECK_FN xtypes)

  isvd_set_types(${xtypes})

  # CPU unit tests
  set(DEFS_TMP "${DEFS}")
  list(REMOVE_ITEM DEFS "ISVD_USE_GPU")

  # Sketching
  add_mpi_check(libisvd/core/stage/${x}_sketch_gaussian_projection "${XName} Precision Gaussian Projection Sketching check" "1;2;3;4;6;12")

  # Orthogonalization
  add_mpi_check(libisvd/core/stage/${x}_orthogonalize_gramian "${XName} Precision Gramian Orthogonalization check" "1;2;3;4;6;12")

  # Integration
  add_mpi_check(libisvd/core/stage/${x}_integrate_kolmogorov_nagumo "${XName} Precision Kolmogorov Nagumo Integration check" "1;2;3;4;6;12")
  add_mpi_check(libisvd/core/stage/${x}_integrate_wen_yin "${XName} Precision Wen Yin Integration check" "1;2;3;4;6;12")
  add_mpi_check(libisvd/core/stage/${x}_integrate_hierarchical_reduction "${XName} Precision Hierarchical Reduction Integration check" "1;2;3;4;6;12")

  # Postprocessing
  add_mpi_check(libisvd/core/stage/${x}_postprocess_gramian "${XName} Precision Gramian Postprocessing check" "1;2;3;4;6;12")
  add_mpi_check(libisvd/core/stage/${x}_postprocess_symmetric "${XName} Precision Symmetric Postprocessing check" "1;2;3;4;6;12")

  set(DEFS "${DEFS_TMP}")
  unset(DEFS_TMP)

  # GPU unit tests
  if(ISVD_USE_GPU)
  endif()
endmacro()

# Set double unit tests
isvd_check_fn("${ISVD_S_TYPES}")
isvd_check_fn("${ISVD_D_TYPES}")
unset(isvd_check_fn)

# Add rule 'build_check'
add_custom_target(
  build_check
  DEPENDS ${CMAKE_CHECK_TARGETS}
  COMMENT "Building unit tests"
)

# Add rule 'check'
add_custom_target(
  check
  COMMAND ${CMAKE_CTEST_COMMAND}
  DEPENDS ${CMAKE_CHECK_TARGETS}
  COMMENT "Running unit tests"
)
