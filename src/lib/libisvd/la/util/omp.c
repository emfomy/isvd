////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/util/omp.c
/// \brief      The OpenMP utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/util/omp.h>
#include <libisvd/la/def.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_util_omp_module
/// \brief  Returns the maximum number of threads
///
/// \return  The maximum number of threads.
///
/// \attention    This routine should be called outside of an OpenMP scope.
///
omp_int_t isvd_getOmpMaxSize( void ) {
  omp_int_t omp_size = 1;

  ISVD_OMP_PARALLEL
  {
    if ( isvd_getOmpRank() == 0 ) {
      omp_size = isvd_getOmpSize();
    }
  }

  return omp_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_util_omp_module
/// \brief  Returns the number of threads in the current team.
///
/// \return  The number of threads in the current team.
///
/// \attention    This routine should be called within an OpenMP scope.
///
omp_int_t isvd_getOmpSize( void ) {
#if defined(ISVD_USE_OMP)
  return omp_get_num_threads();
#else  // ISVD_USE_OMP
  return 1;
#endif  // ISVD_USE_OMP
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_util_omp_module
/// \brief  Returns a unique thread identification number within the current team.
///
/// \return  The thread identification number within the current team.
///
/// \attention    This routine should be called within an OpenMP scope.
///
omp_int_t isvd_getOmpRank( void ) {
#if defined(ISVD_USE_OMP)
  return omp_get_thread_num();
#else  // ISVD_USE_OMP
  return 0;
#endif  // ISVD_USE_OMP
}
