////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/lapack/orgqr.c
/// \brief      The LAPACK Orgqr routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/la/lapack/least_square.h>
#include <libisvd/la/def.h>
#include <isvd/util/memory.h>
#include <libisvd/util/function.h>

@ISVD_TYPE_MACRO_DEFINE@

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#if !defined(ISVD_USE_MKL)

extern void sorgqr_(ISVD_UNKNOWN);
extern void dorgqr_(ISVD_UNKNOWN);
extern void cungqr_(ISVD_UNKNOWN);
extern void zungqr_(ISVD_UNKNOWN);

#endif  // ISVD_USE_MKL

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // DOXYGEN_SHOULD_SKIP_THIS

void isvd_sOrgqr(
    const INT m, const INT n, const INT k, REAL4 *a, const INT lda, REAL4 *tau
) {
  REAL4 qwork; INT lwork = -1, info;
  sorgqr_(&m, &n, &k, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  REAL4 *work = isvd_smalloc(lwork);
  sorgqr_(&m, &n, &k, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
void isvd_dOrgqr(
    const INT m, const INT n, const INT k, REAL8 *a, const INT lda, REAL8 *tau
) {
  REAL8 qwork; INT lwork = -1, info;
  dorgqr_(&m, &n, &k, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  REAL8 *work = isvd_dmalloc(lwork);
  dorgqr_(&m, &n, &k, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
void isvd_cOrgqr(
    const INT m, const INT n, const INT k, COMP4 *a, const INT lda, COMP4 *tau
) {
  COMP4 qwork; INT lwork = -1, info;
  cungqr_(&m, &n, &k, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = crealf(qwork);
  COMP4 *work  = isvd_cmalloc(lwork);
  cungqr_(&m, &n, &k, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
void isvd_zOrgqr(
    const INT m, const INT n, const INT k, COMP8 *a, const INT lda, COMP8 *tau
) {
  COMP8 qwork; INT lwork = -1, info;
  zungqr_(&m, &n, &k, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  COMP8 *work  = isvd_zmalloc(lwork);
  zungqr_(&m, &n, &k, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
//\}

@ISVD_TYPE_MACRO_UNDEF@
