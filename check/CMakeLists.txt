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

# Add rule 'build_check'
add_custom_target(
  build_check
  COMMENT "Building unit tests"
)

# Add rule 'check'
add_custom_target(
  check
  COMMAND ${CMAKE_CTEST_COMMAND}
  DEPENDS build_check
  COMMENT "Running unit tests"
)

# Target rule
function(ISVD_SET_TARGET_CHECK_CPU target)
  isvd_set_target_omp(${target} CXX)
  isvd_set_target_mpi(${target} CXX)
  isvd_set_target_blas(${target})
  isvd_set_target_gtest(${target})
  target_link_libraries(${target} checkisvd_gpu_none checkisvd_core_la extmmio)
  target_compile_definitions(${target} PRIVATE "-DISVD_DATA_PATH=\"${PROJECT_SOURCE_DIR}/data\"")
endfunction()

function(ISVD_SET_TARGET_CHECK_GPU target)
  isvd_set_target_omp(${target} CXX)
  isvd_set_target_mpi(${target} CXX)
  isvd_set_target_blas(${target})
  isvd_set_target_gtest(${target})
  isvd_set_target_gpu(${target})
  target_link_libraries(${target} checkisvd_gpu_magma checkisvd_core_la extmmio)
  target_compile_definitions(${target} PRIVATE "-DISVD_DATA_PATH=\"${PROJECT_SOURCE_DIR}/data\"")
endfunction()

# Set include paths
include_directories("${CMAKE_CURRENT_CONFIG_DIR}/lib"
                    "${PROJECT_BINARY_DIR}/include/c"
                    "${PROJECT_CONFIG_DIR}/src/lib"
             SYSTEM "${PROJECT_SOURCE_DIR}/ext/mmio")

# Set environment variables
list(APPEND ENVS "GTEST_COLOR=1")

# Add subdirectories
add_subdirectory(lib)

# Configure files
isvd_configure_x_fn("${CMAKE_CURRENT_SOURCE_DIR}/check" "${CMAKE_CURRENT_CONFIG_DIR}/check" "${ISVD_S_TYPES}")
isvd_configure_x_fn("${CMAKE_CURRENT_SOURCE_DIR}/check" "${CMAKE_CURRENT_CONFIG_DIR}/check" "${ISVD_D_TYPES}")
isvd_configure_fn("${CMAKE_CURRENT_SOURCE_DIR}/check" "${CMAKE_CURRENT_CONFIG_DIR}/check")

# Include macros
include(check.cmake)

# Set unit tests
macro(ISVD_CHECK_FN xtypes)

  isvd_set_types(${xtypes})

  # Sketching
  add_mpi_check_cpu(libisvd/core/stage/${x}_sketch_gaussian_projection "${XName} Precision Gaussian Projection Sketching" "1;2;3;4;6;12")

  # Orthogonalization
  add_mpi_check_cpu(libisvd/core/stage/${x}_orthogonalize_gramian "${XName} Precision Gramian Orthogonalization" "1;2;3;4;6;12")
  add_mpi_check_cpu(libisvd/core/stage/${x}_orthogonalize_tall_skinny_qr "${XName} Precision Tall-Skinny QR Orthogonalization" "1;2;4")

  # Integration
  add_mpi_check_cpu(libisvd/core/stage/${x}_integrate_kolmogorov_nagumo "${XName} Precision Kolmogorov-Nagumo Integration" "1;2;3;4;6;12")
  if(NOT "${x}" STREQUAL "s")
    add_mpi_check_cpu(libisvd/core/stage/${x}_integrate_wen_yin "${XName} Precision Wen-Yin Integration" "1;2;3;4;6;12")
  endif()
  add_mpi_check_cpu(libisvd/core/stage/${x}_integrate_hierarchical_reduction "${XName} Precision Hierarchical Reduction Integration" "1;2;3;4;6;12")

  # Postprocessing
  add_mpi_check_cpu(libisvd/core/stage/${x}_postprocess_gramian "${XName} Precision Gramian Postprocessing" "1;2;3;4;6;12")
  add_mpi_check_cpu(libisvd/core/stage/${x}_postprocess_tall_skinny_qr "${XName} Precision Tall-Skinny QR Postprocessing" "1;2;4;8;16")
  add_mpi_check_cpu(libisvd/core/stage/${x}_postprocess_symmetric "${XName} Precision Symmetric Postprocessing" "1;2;3;4;6;12")

  # GPU unit tests
  if(ISVD_USE_GPU)

    # Sketching
    add_mpi_check_gpu(libisvd/gpu/stage/${x}_sketch_gaussian_projection_gpu "${XName} Precision GPU Gaussian Projection Sketching" "1;2;4")

    # Postprocessing
    add_mpi_check_gpu(libisvd/gpu/stage/${x}_postprocess_gramian_gpu "${XName} Precision GPU Gramian Postprocessing" "1;2;4")
    add_mpi_check_gpu(libisvd/gpu/stage/${x}_postprocess_tall_skinny_qr_gpu "${XName} Precision GPU Tall-Skinny QR Postprocessing" "1;2;4")
    add_mpi_check_gpu(libisvd/gpu/stage/${x}_postprocess_symmetric_gpu "${XName} Precision GPU Symmetric Postprocessing" "1;2;4")
  endif()
endmacro()

# Set double unit tests
isvd_check_fn("${ISVD_S_TYPES}")
isvd_check_fn("${ISVD_D_TYPES}")
unset(isvd_check_fn)
