////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/la/ksame.h
/// @brief   The LAPACK auxiliary header.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_LA_LAPACK_LSAME_H_
#define _ISVD_LA_LAPACK_LSAME_H_

#include <isvd/def.h>

#define CHAR1 char
#define INT   isvd_int_t
#define REAL4 float
#define REAL8 double
#define COMP4 float complex
#define COMP8 double complex

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

extern INT lsame_();

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_lapack_module
/// Tests two characters for equality regardless of the case.
//@{
static inline INT isvd_lsame(
    const CHAR1 ca, const CHAR1 cb
) { return lsame_(&ca, &cb); }
//@}

#undef CHAR1
#undef INT
#undef REAL4
#undef REAL8
#undef COMP4
#undef COMP8

#endif  // _ISVD_LA_LAPACK_LSAME_H_
