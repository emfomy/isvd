////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/lapack/gelqf.c
/// \brief      The LAPACK Gelqf routine.
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

extern void sgelqf_(ISVD_UNKNOWN);
extern void dgelqf_(ISVD_UNKNOWN);
extern void cgelqf_(ISVD_UNKNOWN);
extern void zgelqf_(ISVD_UNKNOWN);

#endif  // ISVD_USE_MKL

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // DOXYGEN_SHOULD_SKIP_THIS

void isvd_sGelqf(
    const INT m, const INT n, REAL4 *a, const INT lda, REAL4 *tau
) {
  REAL4 qwork; INT lwork = -1, info;
  sgelqf_(&m, &n, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  REAL4 *work = isvd_smalloc(lwork);
  sgelqf_(&m, &n, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
void isvd_dGelqf(
    const INT m, const INT n, REAL8 *a, const INT lda, REAL8 *tau
) {
  REAL8 qwork; INT lwork = -1, info;
  dgelqf_(&m, &n, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  REAL8 *work = isvd_dmalloc(lwork);
  dgelqf_(&m, &n, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
void isvd_cGelqf(
    const INT m, const INT n, COMP4 *a, const INT lda, COMP4 *tau
) {
  COMP4 qwork; INT lwork = -1, info;
  cgelqf_(&m, &n, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = crealf(qwork);
  COMP4 *work  = isvd_cmalloc(lwork);
  cgelqf_(&m, &n, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
void isvd_zGelqf(
    const INT m, const INT n, COMP8 *a, const INT lda, COMP8 *tau
) {
  COMP8 qwork; INT lwork = -1, info;
  zgelqf_(&m, &n, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  COMP8 *work  = isvd_zmalloc(lwork);
  zgelqf_(&m, &n, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
//\}

@ISVD_TYPE_MACRO_UNDEF@
