////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/vsl/rng_gaussian.c
/// \brief      The VSL RngGaussian routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/la/vsl/distribution.h>
#include <libisvd/la/def.h>
#include <isvd/la/lapack/auxiliary.h>

#if defined(ISVD_USE_MKL)

void isvd_vsRngGaussian(
    isvd_VSLStreamStatePtr stream, const isvd_int_t n, isvd_s_val_t *r, const isvd_s_val_t a, const isvd_s_val_t sigma
) {
  isvd_assert_pass(vsRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER, (VSLStreamStatePtr)stream, n, r, a, sigma));
}
void isvd_vdRngGaussian(
    isvd_VSLStreamStatePtr stream, const isvd_int_t n, isvd_d_val_t *r, const isvd_d_val_t a, const isvd_d_val_t sigma
) {
  isvd_assert_pass(vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER, (VSLStreamStatePtr)stream, n, r, a, sigma));
}

#else  // ISVD_USE_MKL

void isvd_vsRngGaussian(
    isvd_VSLStreamStatePtr stream, const isvd_int_t n, isvd_s_val_t *r, const isvd_s_val_t a, const isvd_s_val_t sigma
) {
  isvd_sLarnv(3, stream, n, r);
  for ( isvd_int_t i = 0; i < n; ++i ) r[i] = sigma * r[i] + a;
}
void isvd_vdRngGaussian(
    isvd_VSLStreamStatePtr stream, const isvd_int_t n, isvd_d_val_t *r, const isvd_d_val_t a, const isvd_d_val_t sigma
) {
  isvd_dLarnv(3, stream, n, r);
  for ( isvd_int_t i = 0; i < n; ++i ) r[i] = sigma * r[i] + a;
}

#endif  // ISVD_USE_MKL
