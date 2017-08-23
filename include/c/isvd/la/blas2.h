////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/la/blas2.h
/// @brief   The BLAS level 2 header.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_LA_BLAS2_H_
#define _ISVD_LA_BLAS2_H_

#include <isvd/def.h>

#define CHAR1 char
#define INT   isvd_int_t
#define REAL4 float
#define REAL8 double
#define COMP4 float complex
#define COMP8 double complex

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

#if !defined(ISVD_USE_MKL)

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_USE_MKL)

#endif  // DOXYGEN_SHOULD_SKIP_THIS

#undef CHAR1
#undef INT
#undef REAL4
#undef REAL8
#undef COMP4
#undef COMP8

#endif  // _ISVD_LA_BLAS2_H_
