////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file    src/libisvd/la/vml/sqrt.c
/// \brief   The VML SQRT routine.
///
/// \author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/la/vml.h>

#if !defined(ISVD_USE_MKL)

#define isvd_xSqrt( n, a, y, sqrt ) \
  for ( isvd_int_t i = 0; i < n; ++i ) { \
    y[i] = sqrt(a[i]); \
  }

void isvd_vsSqrt(
    const isvd_int_t n,
    const float *a,
          float *y
) {
  isvd_xSqrt(n, a, y, sqrtf);
}
void isvd_vdSqrt(
    const isvd_int_t n,
    const double *a,
          double *y
) {
  isvd_xSqrt(n, a, y, sqrt);
}
void isvd_vcSqrt(
    const isvd_int_t n,
    const complex float *a,
          complex float *y
) {
  isvd_xSqrt(n, a, y, csqrtf);
}
void isvd_vzSqrt(
    const isvd_int_t n,
    const complex double *a,
          complex double *y
) {
  isvd_xSqrt(n, a, y, csqrt);
}
#endif  // ISVD_USE_MKL
