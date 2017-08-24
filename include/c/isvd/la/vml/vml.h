////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/la/vml/bml.h
/// @brief   The VML routines.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_LA_VML_SQRT_H_
#define _ISVD_LA_VML_SQRT_H_

#include <isvd/def.h>

#define CHAR1 char
#define INT   isvd_int_t
#define REAL4 float
#define REAL8 double
#define COMP4 float complex
#define COMP8 double complex

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_vml_module
/// Subtracts vector elements.
//@{
#if defined(ISVD_USE_MKL)
static inline void isvd_vssub(
    const INT n, const REAL4 *a, const REAL4 *b, REAL4 *y
) { vssub_(&n, a, b, y); }
static inline void isvd_vdsub(
    const INT n, const REAL8 *a, const REAL8 *b, REAL8 *y
) { vdsub_(&n, a, b, y); }
static inline void isvd_vcsub(
    const INT n, const COMP4 *a, const COMP4 *b, COMP4 *y
) { vcsub_(&n, a, b, y); }
static inline void isvd_vzsub(
    const INT n, const COMP8 *a, const COMP8 *b, COMP8 *y
) { vzsub_(&n, a, b, y); }
#else  // ISVD_USE_MKL
void isvd_vssub(
    const INT n, const REAL4 *a, const REAL4 *b, REAL4 *y
);
void isvd_vdsub(
    const INT n, const REAL8 *a, const REAL8 *b, REAL8 *y
);
void isvd_vcsub(
    const INT n, const COMP4 *a, const COMP4 *b, COMP4 *y
);
void isvd_vzsub(
    const INT n, const COMP8 *a, const COMP8 *b, COMP8 *y
);
#endif  // ISVD_USE_MKL
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_vml_module
/// Computes the square root of vector elements.
//@{
#if defined(ISVD_USE_MKL)
static inline void isvd_vssqrt(
    const INT n, const REAL4 *a, REAL4 *y
) { vssqrt_(&n, a, y); }
static inline void isvd_vdsqrt(
    const INT n, const REAL8 *a, REAL8 *y
) { vdsqrt_(&n, a, y); }
static inline void isvd_vcsqrt(
    const INT n, const COMP4 *a, COMP4 *y
) { vcsqrt_(&n, a, y); }
static inline void isvd_vzsqrt(
    const INT n, const COMP8 *a, COMP8 *y
) { vzsqrt_(&n, a, y); }
#else  // ISVD_USE_MKL
void isvd_vssqrt(
    const INT n, const REAL4 *a, REAL4 *y
);
void isvd_vdsqrt(
    const INT n, const REAL8 *a, REAL8 *y
);
void isvd_vcsqrt(
    const INT n, const COMP4 *a, COMP4 *y
);
void isvd_vzsqrt(
    const INT n, const COMP8 *a, COMP8 *y
);
#endif  // ISVD_USE_MKL
//@}

#undef CHAR1
#undef INT
#undef REAL4
#undef REAL8
#undef COMP4
#undef COMP8

#endif  // _ISVD_LA_VML_SQRT_H_
