////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/lapack/orglq.c
/// \brief      The LAPACK Orglq routine.
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

extern void sorglq_(ISVD_UNKNOWN);
extern void dorglq_(ISVD_UNKNOWN);
extern void cunglq_(ISVD_UNKNOWN);
extern void zunglq_(ISVD_UNKNOWN);

#endif  // ISVD_USE_MKL

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // DOXYGEN_SHOULD_SKIP_THIS

void isvd_sOrglq(
    const INT m, const INT n, const INT k, REAL4 *a, const INT lda, REAL4 *tau
) {
  REAL4 qwork; INT lwork = -1, info;
  sorglq_(&m, &n, &k, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  REAL4 *work = isvd_smalloc(lwork);
  sorglq_(&m, &n, &k, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
void isvd_dOrglq(
    const INT m, const INT n, const INT k, REAL8 *a, const INT lda, REAL8 *tau
) {
  REAL8 qwork; INT lwork = -1, info;
  dorglq_(&m, &n, &k, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  REAL8 *work = isvd_dmalloc(lwork);
  dorglq_(&m, &n, &k, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
void isvd_cOrglq(
    const INT m, const INT n, const INT k, COMP4 *a, const INT lda, COMP4 *tau
) {
  COMP4 qwork; INT lwork = -1, info;
  cunglq_(&m, &n, &k, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = crealf(qwork);
  COMP4 *work  = isvd_cmalloc(lwork);
  cunglq_(&m, &n, &k, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
void isvd_zOrglq(
    const INT m, const INT n, const INT k, COMP8 *a, const INT lda, COMP8 *tau
) {
  COMP8 qwork; INT lwork = -1, info;
  zunglq_(&m, &n, &k, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  COMP8 *work  = isvd_zmalloc(lwork);
  zunglq_(&m, &n, &k, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
//\}

@ISVD_TYPE_MACRO_UNDEF@
