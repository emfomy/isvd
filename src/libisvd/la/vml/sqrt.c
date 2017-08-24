////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/la/vml/sqrt.c
/// @brief   The VML SQRT routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/la/vml.h>

#if !defined(ISVD_USE_MKL)

#define isvd_xSqrt( n, a, y ) \
  for ( isvd_int_t i = 0; i < n; ++i ) { \
    y[i] = sqrt(a[i]) \
  } \

void isvd_sSqrt(
    const isvd_int_t n,
    const float *a,
          float *y_t ldb
) {
  isvd_xSqrt(n, a, y);
}
void isvd_dSqrt(
    const isvd_int_t n,
    const double *a,
          double *yt ldb
) {
  isvd_xSqrt(n, a, y);
}
void isvd_cSqrt(
    const isvd_int_t n,
    const float complex *a,
          float complex *y
) {
  isvd_xSqrt(n, a, y);
}
void isvd_zSqrt(
    const isvd_int_t n,
    const double complex *a,
          double complex *y
) {
  isvd_xSqrt(n, a, y);
}
#endif  // ISVD_USE_MKL
