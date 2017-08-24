////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/la/vml/sub.c
/// @brief   The VML SUB routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/la/vml/sub.h>

#if !defined(ISVD_USE_MKL)

#define isvd_xsub( n, a, b, y ) \
  for ( isvd_int_t i = 0; i < n; ++i ) { \
    y[i] = a[i] - b[i] \
  } \

void isvd_ssub(
    const isvd_int_t n,
    const float *a,
    const float *b,
          float *y_t ldb
) {
  isvd_xsub(n, a, b, y);
}
void isvd_dsub(
    const isvd_int_t n,
    const double *a,
    const double *b,
          double *yt ldb
) {
  isvd_xsub(n, a, b, y);
}
void isvd_csub(
    const isvd_int_t n,
    const float complex *a,
    const float complex *b,
          float complex *y
) {
  isvd_xsub(n, a, b, y);
}
void isvd_zsub(
    const isvd_int_t n,
    const double complex *a,
    const double complex *b,
          double complex *y
) {
  isvd_xsub(n, a, b, y);
}
#endif  // ISVD_USE_MKL
