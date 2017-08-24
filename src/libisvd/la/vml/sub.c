////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/la/vml/sub.c
/// @brief   The VML SUB routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/la/vml.h>

#if !defined(ISVD_USE_MKL)

#define isvd_xSub( n, a, y ) \
  for ( isvd_int_t i = 0; i < n; ++i ) { \
    y[i] = a[i] - b[i] \
  } \

void isvd_sSub(
    const isvd_int_t n,
    const float *a,
    const float *b,
          float *y_t ldb
) {
  isvd_xSub(n, a, y);
}
void isvd_dSub(
    const isvd_int_t n,
    const double *a,
    const double *b,
          double *yt ldb
) {
  isvd_xSub(n, a, y);
}
void isvd_cSub(
    const isvd_int_t n,
    const float complex *a,
    const float complex *b,
          float complex *y
) {
  isvd_xSub(n, a, y);
}
void isvd_zSub(
    const isvd_int_t n,
    const double complex *a,
    const double complex *b,
          double complex *y
) {
  isvd_xSub(n, a, y);
}
#endif  // ISVD_USE_MKL
