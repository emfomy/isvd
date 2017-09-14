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

@ISVD_TYPE_MACRO_DEFINE@

#if defined(ISVD_USE_MKL)

void isvd_vsRngGaussian( isvd_VSLStreamStatePtr stream, const INT n, REAL4 *r, const REAL4 a, const REAL4 sigma ) {
  isvd_assert_pass(vsRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER, (VSLStreamStatePtr)stream, n, r, a, sigma));
}
void isvd_vdRngGaussian( isvd_VSLStreamStatePtr stream, const INT n, REAL8 *r, const REAL8 a, const REAL8 sigma ) {
  isvd_assert_pass(vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER, (VSLStreamStatePtr)stream, n, r, a, sigma));
}

#else  // ISVD_USE_MKL

void isvd_vsRngGaussian( isvd_VSLStreamStatePtr stream, const INT n, REAL4 *r, const REAL4 a, const REAL4 sigma ) {
  isvd_sLarnv(3, stream, n, r);
  for ( INT i = 0; i < n; ++i ) r[i] = sigma * r[i] + a;
}
void isvd_vdRngGaussian( isvd_VSLStreamStatePtr stream, const INT n, REAL8 *r, const REAL8 a, const REAL8 sigma ) {
  isvd_dLarnv(3, stream, n, r);
  for ( INT i = 0; i < n; ++i ) r[i] = sigma * r[i] + a;
}

#endif  // ISVD_USE_MKL

@ISVD_TYPE_MACRO_UNDEF@
