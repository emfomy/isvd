////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/la/lapack/syev.c
/// \brief      The LAPACK Syev routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/la/lapack/least_square.h>
#include <libisvd/def.h>
#include <libisvd/util/memory.h>

@ISVD_LA_BLAS_TYPE_DEFINE@

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#if !defined(ISVD_USE_MKL)

extern void ssyev_(ISVD_UNKNOWN);
extern void dsyev_(ISVD_UNKNOWN);
extern void cheev_(ISVD_UNKNOWN);
extern void zheev_(ISVD_UNKNOWN);

#endif  // ISVD_USE_MKL

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // DOXYGEN_SHOULD_SKIP_THIS

void isvd_sSyev(
    const CHAR1 jobz, const CHAR1 uplo, const INT n, REAL4 *a, const INT lda, REAL4 *w
) {
  REAL4 qwork; INT lwork = -1, info;
  ssyev_(&jobz, &uplo, &n, a, &lda, w, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  REAL4 *work = isvd_smalloc(lwork);
  ssyev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, &info);   isvd_assert_pass(info);
}
void isvd_dSyev(
    const CHAR1 jobz, const CHAR1 uplo, const INT n, REAL8 *a, const INT lda, REAL8 *w
) {
  REAL8 qwork; INT lwork = -1, info;
  dsyev_(&jobz, &uplo, &n, a, &lda, w, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  REAL8 *work = isvd_dmalloc(lwork);
  dsyev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, &info);   isvd_assert_pass(info);
}
void isvd_cSyev(
    const CHAR1 jobz, const CHAR1 uplo, const INT n, COMP4 *a, const INT lda, REAL4 *w
) {
  COMP4 qwork; INT lwork = -1, info;
  cheev_(&jobz, &uplo, &n, a, &lda, w, &qwork, &lwork, nullptr, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  COMP4 *work  = isvd_cmalloc(lwork);
  REAL4 *rwork = isvd_smalloc(5*n-2);
  cheev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, rwork, &info);  isvd_assert_pass(info);
}
void isvd_zSyev(
    const CHAR1 jobz, const CHAR1 uplo, const INT n, COMP8 *a, const INT lda, REAL8 *w
) {
  COMP8 qwork; INT lwork = -1, info;
  zheev_(&jobz, &uplo, &n, a, &lda, w, &qwork, &lwork, nullptr, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  COMP8 *work  = isvd_zmalloc(lwork);
  REAL8 *rwork = isvd_dmalloc(5*n-2);
  zheev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, rwork, &info);  isvd_assert_pass(info);
}

@ISVD_LA_BLAS_TYPE_UNDEF@
