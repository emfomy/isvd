////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/def.h
/// \brief      The linear algebra definitions.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef LIBISVD_LA_DEF_H_
#define LIBISVD_LA_DEF_H_

#include <libisvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

#if defined(_OPENMP)
  #if !defined(ISVD_USE_OMP)
    #define ISVD_USE_OMP
  #endif  // ISVD_USE_OMP
#else  // _OPENMP
  #undef ISVD_USE_OMP
#endif  // _OPENMP

#if defined(ISVD_USE_OMP)
  #include <omp.h>
  #define ISVD_OMP_PARALLEL _Pragma("omp parallel")
#else
  #define ISVD_OMP_PARALLEL
#endif  // ISVD_USE_OMP

#if defined(ISVD_USE_ILP64) && !defined(MKL_ILP64)
  #define MKL_ILP64
#else  // ISVD_USE_ILP64
  #undef MKL_ILP64
#endif  // ISVD_USE_ILP64

#if defined(ISVD_USE_MKL)
  #define MKL_INT       isvd_int_t
  #define MKL_UINT      isvd_uint_t
  #define MKL_Complex8  isvd_c_val_t
  #define MKL_Complex16 isvd_z_val_t
#endif  // ISVD_USE_MKL

#endif  // DOXYGEN_SHOULD_SKIP_THIS

#if defined(ISVD_USE_MKL)
  #include <mkl.h>
#endif  // ISVD_USE_MKL

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // LIBISVD_LA_DEF_H_
