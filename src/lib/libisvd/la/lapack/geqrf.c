////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/lapack/geqrf.c
/// \brief      The LAPACK Geqrf routine.
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

extern void sgeqrf_(ISVD_UNKNOWN);
extern void dgeqrf_(ISVD_UNKNOWN);
extern void cgeqrf_(ISVD_UNKNOWN);
extern void zgeqrf_(ISVD_UNKNOWN);

#endif  // ISVD_USE_MKL

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // DOXYGEN_SHOULD_SKIP_THIS

void isvd_sGeqrf(
    const INT m, const INT n, REAL4 *a, const INT lda, REAL4 *tau
) {
  REAL4 qwork; INT lwork = -1, info;
  sgeqrf_(&m, &n, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  REAL4 *work = isvd_smalloc(lwork);
  sgeqrf_(&m, &n, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
void isvd_dGeqrf(
    const INT m, const INT n, REAL8 *a, const INT lda, REAL8 *tau
) {
  REAL8 qwork; INT lwork = -1, info;
  dgeqrf_(&m, &n, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  REAL8 *work = isvd_dmalloc(lwork);
  dgeqrf_(&m, &n, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
void isvd_cGeqrf(
    const INT m, const INT n, COMP4 *a, const INT lda, COMP4 *tau
) {
  COMP4 qwork; INT lwork = -1, info;
  cgeqrf_(&m, &n, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = crealf(qwork);
  COMP4 *work  = isvd_cmalloc(lwork);
  cgeqrf_(&m, &n, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
void isvd_zGeqrf(
    const INT m, const INT n, COMP8 *a, const INT lda, COMP8 *tau
) {
  COMP8 qwork; INT lwork = -1, info;
  zgeqrf_(&m, &n, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  COMP8 *work  = isvd_zmalloc(lwork);
  zgeqrf_(&m, &n, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
//\}

@ISVD_TYPE_MACRO_UNDEF@
