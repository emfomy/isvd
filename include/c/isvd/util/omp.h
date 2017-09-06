////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/util/omp.h
/// \brief      The OpenMP utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _ISVD_UTIL_OMP_H_
#define _ISVD_UTIL_OMP_H_

#include <libisvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

omp_int_t isvd_getOmpSize( void );
omp_int_t isvd_getOmpRank( void );

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_UTIL_OMP_H_
