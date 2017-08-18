////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/util/omp.h
/// @brief   The OpenMP utilities.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_UTIL_OMP_H_
#define _ISVD_UTIL_OMP_H_

#include <isvd/def.h>
#ifdef _OPENMP
  #include <omp.h>
#endif  // _OPENMP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  util_module
/// @brief  Returns the number of threads in the current team.
///
/// @return  The number of threads in the current team.
///
static inline omp_int_t isvd_getOmpSize( void ) {
#ifdef _OPENMP
  return omp_get_max_threads();
#else  // _OPENMP
  return 1;
#endif  // _OPENMP
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  util_module
/// @brief  Returns a unique thread identification number within the current team.
///
/// @return  The thread identification number within the current team.
///
static inline omp_int_t isvd_getOmpRank( void ) {
#ifdef _OPENMP
  return omp_get_thread_num();
#else  // _OPENMP
  return 0;
#endif  // _OPENMP
}

#endif  // _ISVD_UTIL_OMP_H_
