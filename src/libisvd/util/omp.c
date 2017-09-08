////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/util/omp.h
/// \brief      The OpenMP utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/util/omp.h>
#include <libisvd/def.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_util_omp_module
/// \brief  Returns the number of threads in the current team.
///
/// \return  The number of threads in the current team.
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
omp_int_t isvd_getOmpRank( void ) {
#if defined(ISVD_USE_OMP)
  return omp_get_thread_num();
#else  // ISVD_USE_OMP
  return 0;
#endif  // ISVD_USE_OMP
}
