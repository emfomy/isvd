////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/util/omp.h
/// \brief      The OpenMP utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef ISVD_UTIL_OMP_H_
#define ISVD_UTIL_OMP_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

omp_int_t isvd_getOmpMaxSize( void );
omp_int_t isvd_getOmpSize( void );
omp_int_t isvd_getOmpRank( void );

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_UTIL_OMP_H_
