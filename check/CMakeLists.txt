# The CMake setting of 'check/'

# Break
if(NOT ISVD_BUILD_TEST)
  return()
endif()

# GTest
if(GTEST_FOUND)
  list(APPEND INCS "${GTEST_INCLUDE_DIRS}")
  list(APPEND LIBS "${GTEST_BOTH_LIBRARIES}")
endif()

# Set include paths
include_directories(
  SYSTEM
  "${PROJECT_BINARY_DIR}/include/c"
  "${PROJECT_SOURCE_DIR}/include/c"
  "${PROJECT_BINARY_DIR}/src"
  "${PROJECT_SOURCE_DIR}/src"
  "${PROJECT_BINARY_DIR}/ext"
  "${PROJECT_SOURCE_DIR}/ext"
)

# Set libraries
list(APPEND LIBS extmmiox)

# Set definitions
list(APPEND DEFS "-DISVD_DATA_PATH=\"${PROJECT_SOURCE_DIR}/data\"")

# Include macros
include(check.cmake)

# CPU checks
set(DEFS_TMP "${DEFS}")
list(REMOVE_ITEM DEFS "ISVD_USE_GPU")

# Sketching
add_mpi_check(libisvd/core/stage_d/isvd_d_sketch_gaussian_projection "Gaussian Projection Sketching check" "1;2;3;4;6;12")

# Orthogonalization
add_mpi_check(libisvd/core/stage_d/isvd_d_orthogonalize_gramian "Gramian Orthogonalization check" "1;2;3;4;6;12")

# Integration
add_mpi_check(libisvd/core/stage_d/isvd_d_integrate_kolmogorov_nagumo "Kolmogorov Nagumo Integration check" "1;2;3;4;6;12")
add_mpi_check(libisvd/core/stage_d/isvd_d_integrate_wen_yin "Wen Yin Integration check" "1;2;3;4;6;12")
add_mpi_check(libisvd/core/stage_d/isvd_d_integrate_hierarchical_reduction "Hierarchical Reduction Integration check" "1;2;3;4;6;12")

# Postprocessing
add_mpi_check(libisvd/core/stage_d/isvd_d_postprocess_gramian "Gramian Postprocessing check" "1;2;3;4;6;12")
add_mpi_check(libisvd/core/stage_d/isvd_d_postprocess_symmetric "Symmetric Postprocessing check" "1;2;3;4;6;12")

set(DEFS "${DEFS_TMP}")
unset(DEFS_TMP)

# GPU checks
if(ISVD_USE_GPU)
endif()

# Add rule 'build_check'
add_custom_target(
  build_check
  DEPENDS ${CMAKE_CHECK_TARGETS}
  COMMENT "Building checks"
)

# Add rule 'check'
add_custom_target(
  check
  COMMAND ${CMAKE_CTEST_COMMAND}
  DEPENDS ${CMAKE_CHECK_TARGETS}
  COMMENT "Running checks"
)
