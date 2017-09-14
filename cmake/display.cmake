# Color output
function(DISP item var)
  if(var STREQUAL "ON")
    message(STATUS "${item}${Esc}[32m✔${Esc}[0m")
  elseif(var STREQUAL "OFF")
    message(STATUS "${item}${Esc}[31m✘${Esc}[0m")
  else()
    message(STATUS "${item}${var}")
  endif()
endfunction()

# Display message
message(STATUS "")
message(STATUS "================================================================================")
message(STATUS "")
message(STATUS "${ISVD_NAME} (iSVD) ${ISVD_VERSION}")
message(STATUS "")
message(STATUS "================================================================================")
message(STATUS "")
message(STATUS "Set 'ISVD_BLAS'                 to select BLAS/LAPACK library. [BLAS/MKL]")
message(STATUS "Set 'ISVD_BUILD_DEMO'           to build demo codes.")
message(STATUS "Set 'ISVD_BUILD_DOC'            to build documentation.")
message(STATUS "Set 'ISVD_BUILD_LIB'            to build libraries.")
message(STATUS "Set 'ISVD_BUILD_TEST'           to build unit tests.")
message(STATUS "Set 'ISVD_INDEX_TYPE'           to select index type. [32/64]")
message(STATUS "Set 'ISVD_OMP'                  to select OpenMP library. [OFF/GOMP/IOMP]")
message(STATUS "Set 'ISVD_USE_GPU'              to enable GPU support.")
message(STATUS "Set 'ISVD_VERBOSE_TEST'         to enable verbose unit tests.")
message(STATUS "")
message(STATUS "Set 'GTEST_ROOT'                for the root path of Google Test.     (Require 'ISVD_BUILD_TEST')")
message(STATUS "Set 'INTEL_ROOT'                for the root path of Intel libraries. (Require 'ISVD_BLAS = MKL')")
message(STATUS "Set 'MKL_ROOT'                  for the root path of Intel MKL.       (Require 'ISVD_BLAS = MKL')")
message(STATUS "Set 'MPI_PROCS'                 for the number of MPI processes used in demo codes.")
message(STATUS "Set 'OMP_THRDS'                 for the number of OpenMP threads used in demo/check codes.")
message(STATUS "")
message(STATUS "================================================================================")
message(STATUS "")

# Display options
disp("Build libraries:                " "${ISVD_BUILD_LIB}")
disp("Build demo codes:               " "${ISVD_BUILD_DEMO}")
disp("Build unit tests:               " "${ISVD_BUILD_TEST}")
disp("Build documentation:            " "${ISVD_BUILD_DOC}")

message(STATUS "")

disp("BLAS library:                   " "${ISVD_BLAS}")
disp("OpenMP library:                 " "${ISVD_OMP}")
disp("Enable GPU:                     " "${ISVD_USE_GPU}")
if(NOT ISVD_USE_ILP64)
  disp("Integer type:                   " "32bit integer (LP64)")
else()
  disp("Integer type:                   " "64bit integer (ILP64)")
endif()
disp("Verbose unit tests:             " "${ISVD_VERBOSE_TEST}")

message(STATUS "")
message(STATUS "================================================================================")
message(STATUS "")

# Display install prefix
disp("Install path:                   " "${CMAKE_INSTALL_PREFIX}")
disp("Install include directory:      " "${CMAKE_INSTALL_PREFIX}/include")
disp("Install library directory:      " "${CMAKE_INSTALL_PREFIX}/${LIB_FOLDER}")

message(STATUS "")

disp("Build type:                     " "${CMAKE_BUILD_TYPE}")

message(STATUS "")

# Display compilers
disp("Use C   Compiler:               " "${CMAKE_C_COMPILER}")
disp("Use C++ Compiler:               " "${CMAKE_CXX_COMPILER}")

message(STATUS "")

string(TOUPPER "CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE}" cflag_name)
string(TOUPPER "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}" cxxflag_name)

disp("Use C   flags:                  " "${CMAKE_C_FLAGS} ${${cflag_name}}")
disp("Use C++ flags:                  " "${CMAKE_CXX_FLAGS} ${${cxxflag_name}}")

message(STATUS "")

# Display libraries

if(ISVD_BUILD_BIN AND ISVD_OMP)
  disp("Use OpenMP:                     " "${OpenMP_C_FLAGS} ${OpenMP_LIBRARIES}")
else()
  disp("Use OpenMP:                     " "OFF")
endif()

if(ISVD_BUILD_BIN)
  disp("Use MPI:                        " "${MPI_C_LIBRARIES}")
else()
  disp("Use MPI:                        " "OFF")
endif()

if(ISVD_BUILD_BIN)
  if(NOT ISVD_USE_MKL)
    set(LAPACK_LIBS ${LAPACK_LIBRARIES})
    list(REMOVE_DUPLICATES LAPACK_LIBS)
    disp("Use BLAS:                       " "${LAPACK_LIBS}")
  else()
    disp("Use BLAS: (Intel MKL)           " "${MKL_LIBS}")
  endif()
endif()

if(ISVD_BUILD_BIN AND ISVD_USE_GPU)
  disp("Use GPU:                        " "${CUDA_TOOLKIT_ROOT_DIR}")
  disp("Use MAGMA:                      " "${MAGMA_LIBRARIES}")
else()
  disp("Use GPU:                        " "OFF")
endif()

if(ISVD_BUILD_TEST)
  disp("Use Google Test:                " "${GTEST_BOTH_LIBRARIES}")
else()
  disp("Use Google Test:                " "OFF")
endif()

if(ISVD_BUILD_DOC)
  disp("Use Doxygen:                    " "${DOXYGEN_EXECUTABLE}")
else()
  disp("Use Doxygen:                    " "OFF")
endif()

message(STATUS "")

if(ISVD_BUILD_BIN)
  disp("MPI processes (demo only):      " "${MPI_PROCS}")
  disp("OpenMP threads (demo only):     " "${OMP_THRDS}")
endif()

message(STATUS "")
message(STATUS "================================================================================")
message(STATUS "")

if(ISVD_BUILD_BIN)
  if(ISVD_BLAS STREQUAL "BLAS" AND ISVD_OMP)
    message(${DEPRECATION} "${Esc}[1;33mPlain BLAS library might not support OpenMP multithreading.${Esc}[0m")
  endif()

  if(ISVD_BLAS STREQUAL "BLAS" AND ISVD_USE_ILP64)
    message(${DEPRECATION} "${Esc}[1;33mPlain BLAS library might not support 64bit integer.${Esc}[0m")
  endif()

  if(NOT ISVD_BLAS STREQUAL "MKL")
    message(${DEPRECATION} "${Esc}[1;33mIntel MKL is not enabled. Recommended to use it for better performance.${Esc}[0m")
  endif()

  if(ISVD_BLAS STREQUAL "MKL" AND NOT ISVD_OMP)
    message(${DEPRECATION} "${Esc}[1;33mOpenMP is not enabled. Recommended to use it for better performance.${Esc}[0m")
  endif()

  if(CMAKE_COMPILER_IS_GNUCC AND NOT CMAKE_C_COMPILER_VERSION VERSION_GREATER 7 AND ISVD_USE_GPU AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(${DEPRECATION} "${Esc}[1;33mGPU routines with GCC under 7.0 might crash in debug mode.${Esc}[0m")
  endif()
endif()
