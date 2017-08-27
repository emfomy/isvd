////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file    include/c/isvd/la/lapack/lsame.h
/// \brief   The LAPACK LSAME header.
///
/// \author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_LA_LAPACK_LSAME_H_
#define _ISVD_LA_LAPACK_LSAME_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#define CHAR1 char
#define INT   isvd_int_t
#define REAL4 float
#define REAL8 double
#define COMP4 complex float
#define COMP8 complex double

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

extern INT lsame_(ISVD_UNKNOWN);

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  la_lapack_module
/// Tests two characters for equality regardless of the case.
//\{
static inline INT isvd_lsame(
    const CHAR1 ca, const CHAR1 cb
) { return lsame_(&ca, &cb); }
//\}

#undef CHAR1
#undef INT
#undef REAL4
#undef REAL8
#undef COMP4
#undef COMP8

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_LA_LAPACK_LSAME_H_
