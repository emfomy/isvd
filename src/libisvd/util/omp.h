////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/util/omp.h
/// \brief      The OpenMP utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _LIBISVD_UTIL_OMP_H_
#define _LIBISVD_UTIL_OMP_H_

#include <libisvd/def.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  util_module
/// \brief  Returns the number of threads in the current team.
///
/// \return  The number of threads in the current team.
///
static inline omp_int_t isvd_getOmpSize( void ) {
#if defined(ISVD_USE_OMP)
  return omp_get_max_threads();
#else  // ISVD_USE_OMP
  return 1;
#endif  // ISVD_USE_OMP
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  util_module
/// \brief  Returns a unique thread identification number within the current team.
///
/// \return  The thread identification number within the current team.
///
static inline omp_int_t isvd_getOmpRank( void ) {
#if defined(ISVD_USE_OMP)
  return omp_get_thread_num();
#else  // ISVD_USE_OMP
  return 0;
#endif  // ISVD_USE_OMP
}

#endif  // _LIBISVD_UTIL_OMP_H_
