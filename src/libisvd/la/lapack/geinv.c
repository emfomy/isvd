////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/la/lapack/geinv.c
/// \brief      The LAPACK GETRF+GETRI routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/la/lapack/linear_equation.h>
#include <libisvd/def.h>
#include <libisvd/util/memory.h>

@ISVD_LA_BLAS_TYPE_DEFINE@

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#if !defined(ISVD_USE_MKL)

extern void sgetrf_(ISVD_UNKNOWN);
extern void dgetrf_(ISVD_UNKNOWN);
extern void cgetrf_(ISVD_UNKNOWN);
extern void zgetrf_(ISVD_UNKNOWN);

extern void sgetri_(ISVD_UNKNOWN);
extern void dgetri_(ISVD_UNKNOWN);
extern void cgetri_(ISVD_UNKNOWN);
extern void zgetri_(ISVD_UNKNOWN);

#endif  // ISVD_USE_MKL

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // DOXYGEN_SHOULD_SKIP_THIS

void isvd_sGeinv(
    const INT n, REAL4 *a, const INT lda
) {
  REAL4 qwork; INT lwork = -1, info;
  sgetri_(&n, a, &lda, nullptr, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  INT *ipiv = isvd_imalloc(n);
  REAL4 *work = isvd_smalloc(lwork);
  sgetrf_(&n, &n, a, &lda, ipiv, &info);            isvd_assert_pass(info);
  sgetri_(&n, a, &lda, ipiv, work, &lwork, &info);  isvd_assert_pass(info);
}
void isvd_dGeinv(
    const INT n, REAL8 *a, const INT lda
) {
  REAL8 qwork; INT lwork = -1, info;
  dgetri_(&n, a, &lda, nullptr, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  INT *ipiv = isvd_imalloc(n);
  REAL8 *work = isvd_dmalloc(lwork);
  dgetrf_(&n, &n, a, &lda, ipiv, &info);            isvd_assert_pass(info);
  dgetri_(&n, a, &lda, ipiv, work, &lwork, &info);  isvd_assert_pass(info);
}
void isvd_cGeinv(
    const INT n, COMP4 *a, const INT lda
) {
  COMP4 qwork; INT lwork = -1, info;
  cgetri_(&n, a, &lda, nullptr, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  INT *ipiv = isvd_imalloc(n);
  COMP4 *work  = isvd_cmalloc(lwork);
  cgetrf_(&n, &n, a, &lda, ipiv, &info);            isvd_assert_pass(info);
  cgetri_(&n, a, &lda, ipiv, work, &lwork, &info);  isvd_assert_pass(info);
}
void isvd_zGeinv(
    const INT n, COMP8 *a, const INT lda
) {
  COMP8 qwork; INT lwork = -1, info;
  zgetri_(&n, a, &lda, nullptr, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  INT *ipiv = isvd_imalloc(n);
  COMP8 *work  = isvd_zmalloc(lwork);
  zgetrf_(&n, &n, a, &lda, ipiv, &info);            isvd_assert_pass(info);
  zgetri_(&n, a, &lda, ipiv, work, &lwork, &info);  isvd_assert_pass(info);
}

@ISVD_LA_BLAS_TYPE_UNDEF@
