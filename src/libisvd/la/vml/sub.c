////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file    src/libisvd/la/vml/sub.c
/// \brief   The VML SUB routine.
///
/// \author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/la/vml.h>

#if !defined(ISVD_USE_MKL)

#define isvd_xSub( n, a, b, y ) \
  for ( isvd_int_t i = 0; i < n; ++i ) { \
    y[i] = a[i] - b[i]; \
  }

void isvd_vsSub(
    const isvd_int_t n,
    const float *a,
    const float *b,
          float *y
) {
  isvd_xSub(n, a, b, y);
}
void isvd_vdSub(
    const isvd_int_t n,
    const double *a,
    const double *b,
          double *y
) {
  isvd_xSub(n, a, b, y);
}
void isvd_vcSub(
    const isvd_int_t n,
    const complex float *a,
    const complex float *b,
          complex float *y
) {
  isvd_xSub(n, a, b, y);
}
void isvd_vzSub(
    const isvd_int_t n,
    const complex double *a,
    const complex double *b,
          complex double *y
) {
  isvd_xSub(n, a, b, y);
}
#endif  // ISVD_USE_MKL
