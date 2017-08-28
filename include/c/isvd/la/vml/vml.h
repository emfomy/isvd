////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/vml/vml.h
/// \brief      The VML routines.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _ISVD_LA_VML_VML_H_
#define _ISVD_LA_VML_VML_H_

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  la_vml_module
/// Subtracts vector elements.
//\{
#if defined(ISVD_USE_MKL)
static inline void isvd_vsSub(
    const INT n, const REAL4 *a, const REAL4 *b, REAL4 *y
) { vsSub(n, a, b, y); }
static inline void isvd_vdSub(
    const INT n, const REAL8 *a, const REAL8 *b, REAL8 *y
) { vdSub(n, a, b, y); }
static inline void isvd_vcSub(
    const INT n, const COMP4 *a, const COMP4 *b, COMP4 *y
) { vcSub(n, a, b, y); }
static inline void isvd_vzSub(
    const INT n, const COMP8 *a, const COMP8 *b, COMP8 *y
) { vzSub(n, a, b, y); }
#else  // ISVD_USE_MKL
void isvd_vsSub(
    const INT n, const REAL4 *a, const REAL4 *b, REAL4 *y
);
void isvd_vdSub(
    const INT n, const REAL8 *a, const REAL8 *b, REAL8 *y
);
void isvd_vcSub(
    const INT n, const COMP4 *a, const COMP4 *b, COMP4 *y
);
void isvd_vzSub(
    const INT n, const COMP8 *a, const COMP8 *b, COMP8 *y
);
#endif  // ISVD_USE_MKL
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  la_vml_module
/// Computes the square root of vector elements.
//\{
#if defined(ISVD_USE_MKL)
static inline void isvd_vsSqrt(
    const INT n, const REAL4 *a, REAL4 *y
) { vsSqrt(n, a, y); }
static inline void isvd_vdSqrt(
    const INT n, const REAL8 *a, REAL8 *y
) { vdSqrt(n, a, y); }
static inline void isvd_vcSqrt(
    const INT n, const COMP4 *a, COMP4 *y
) { vcSqrt(n, a, y); }
static inline void isvd_vzSqrt(
    const INT n, const COMP8 *a, COMP8 *y
) { vzSqrt(n, a, y); }
#else  // ISVD_USE_MKL
void isvd_vsSqrt(
    const INT n, const REAL4 *a, REAL4 *y
);
void isvd_vdSqrt(
    const INT n, const REAL8 *a, REAL8 *y
);
void isvd_vcSqrt(
    const INT n, const COMP4 *a, COMP4 *y
);
void isvd_vzSqrt(
    const INT n, const COMP8 *a, COMP8 *y
);
#endif  // ISVD_USE_MKL
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

#endif  // _ISVD_LA_VML_VML_H_
