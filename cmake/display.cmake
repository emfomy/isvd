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
message(STATUS "Set 'ISVD_OMP'                  to select OpenMP library. [OFF/GOMP/IOMP] (Require 'ISVD_BLAS = MKL')")
# message(STATUS "Set 'ISVD_USE_GPU'              to enable GPU support.")
message(STATUS "")
message(STATUS "Set 'GTEST_ROOT'                for the root path of Google Test.         (Require 'ISVD_BUILD_TEST')")
message(STATUS "Set 'INTEL_ROOT'                for the root path of Intel libraries.     (Require 'ISVD_BLAS = MKL')")
message(STATUS "Set 'MKL_ROOT'                  for the root path of Intel MKL.           (Require 'ISVD_BLAS = MKL')")
message(STATUS "Set 'MPI_PROCS'                 to set the number of MPI processes used in demo codes.")
message(STATUS "Set 'OMP_THRDS'                 to set the number of OpenMP threads used in demo/check codes.")
message(STATUS "")
message(STATUS "================================================================================")
message(STATUS "")

# Display options
message(STATUS "Build libraries:                ${ISVD_BUILD_LIB}")
message(STATUS "Build demo codes:               ${ISVD_BUILD_DEMO}")
message(STATUS "Build unit tests:               ${ISVD_BUILD_TEST}")
message(STATUS "Build documentation:            ${ISVD_BUILD_DOC}")

message(STATUS "")

# Display compilers
message(STATUS "Use C   Compiler:               ${CMAKE_C_COMPILER}")
message(STATUS "Use C++ Compiler:               ${CMAKE_CXX_COMPILER}")

message(STATUS "")

# Display libraries
if(ISVD_OMP)
  message(STATUS "Use OpenMP:                     ${OpenMP_C_FLAGS} ${OpenMP_LIBRARIES}")
else()
  message(STATUS "Use OpenMP:                     OFF")
endif()

if(ISVD_BUILD_BIN)
  message(STATUS "Use MPI:                        ${MPI_LIBRARIES}")
else()
  message(STATUS "Use MPI:                        OFF")
endif()

if(ISVD_BUILD_BIN)
  if(NOT ISVD_USE_MKL)
    set(LAPACK_LIBS ${LAPACK_LIBRARIES})
    list(REMOVE_DUPLICATES LAPACK_LIBS)
    message(STATUS "Use BLAS:                       ${LAPACK_LIBS}")
  else()
    message(STATUS "Use BLAS: (Intel MKL)           ${MKL_LIBS}")
  endif()
endif()

# if(ISVD_BUILD_BIN AND ISVD_USE_GPU)
#   message(STATUS "Use GPU:                        ${CUDA_TOOLKIT_ROOT_DIR}")
#   message(STATUS "Use MAGMA:                      ${MAGMA_LIBRARIES}")
# else()
#   message(STATUS "Use GPU:                        OFF")
# endif()

if(ISVD_BUILD_TEST)
  message(STATUS "Use Google Test:                ${GTEST_BOTH_LIBRARIES}")
else()
  message(STATUS "Use Google Test:                OFF")
endif()

if(ISVD_BUILD_DOC)
  message(STATUS "Use Doxygen:                    ${DOXYGEN_EXECUTABLE}")
else()
  message(STATUS "Use Doxygen:                    OFF")
endif()

message(STATUS "")

if(NOT ISVD_USE_ILP64)
  message(STATUS "Integer type:                   32bit integer (LP64)")
else()
  message(STATUS "Integer type:                   64bit integer (ILP64)")
endif()

if(ISVD_BUILD_BIN)
  message(STATUS "MPI processes (demo only):      ${MPI_PROCS}")
  message(STATUS "OpenMP threads (demo only):     ${OMP_THRDS}")
endif()

message(STATUS "")
message(STATUS "================================================================================")
message(STATUS "")

# Display flags
message(STATUS "C   Compiler & flags:           ${CMAKE_C_COMPILER} ${ISVD_C_FLAGS}")
message(STATUS "C++ Compiler & flags:           ${CMAKE_CXX_COMPILER} ${ISVD_CXX_FLAGS}")
message(STATUS "Link flags:                     ${ISVD_LNKFLGS}")
message(STATUS "Include pathes:                 ${ISVD_INCS}")
message(STATUS "Libraries:                      ${ISVD_LIBS}")

message(STATUS "")
message(STATUS "================================================================================")
message(STATUS "")
