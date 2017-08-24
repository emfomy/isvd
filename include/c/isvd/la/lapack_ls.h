////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/la/lapack_ls.h
/// @brief   The LAPACK least squares header.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_LA_LAPACK_LS_H_
#define _ISVD_LA_LAPACK_LS_H_

#include <isvd/def.h>
#include <isvd/util/memory.h>
#include <isvd/util/function.h>

#define CHAR1 char
#define INT   isvd_int_t
#define REAL4 float
#define REAL8 double
#define COMP4 float complex
#define COMP8 double complex

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#if !defined(ISVD_USE_MKL)

extern void ssyev();
extern void dsyev();
extern void cheev();
extern void zheev();

extern void sgesvd();
extern void dgesvd();
extern void cgesvd();
extern void zgesvd();

#endif  // ISVD_USE_MKL

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_lapack_module
/// Computes all eigenvalues and, optionally, eigenvectors of a real symmetric matrix.
//@{
static inline void isvd_ssyev(
    const CHAR1 jobz, const CHAR1 uplo, const INT n, REAL4 *a, const INT lda, REAL4 *w
) {
  REAL4 qwork; INT lwork = -1, info;
  ssyev(&jobz, &uplo, &n, a, &lda, w, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  REAL4 *work = isvd_smalloc(lwork);
  ssyev(&jobz, &uplo, &n, a, &lda, w, work, &lwork, &info);   isvd_assert_pass(info);
}
static inline void isvd_dsyev(
    const CHAR1 jobz, const CHAR1 uplo, const INT n, REAL8 *a, const INT lda, REAL8 *w
) {
  REAL8 qwork; INT lwork = -1, info;
  dsyev(&jobz, &uplo, &n, a, &lda, w, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  REAL8 *work = isvd_dmalloc(lwork);
  dsyev(&jobz, &uplo, &n, a, &lda, w, work, &lwork, &info);   isvd_assert_pass(info);
}
static inline void isvd_cheev(
    const CHAR1 jobz, const CHAR1 uplo, const INT n, COMP4 *a, const INT lda, REAL4 *w
) {
  COMP4 qwork; INT lwork = -1, info;
  cheev(&jobz, &uplo, &n, a, &lda, w, &qwork, &lwork, NULL, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  COMP4 *work  = isvd_cmalloc(lwork);
  REAL4 *rwork = isvd_smalloc(5*n-2);
  cheev(&jobz, &uplo, &n, a, &lda, w, work, &lwork, rwork, &info);  isvd_assert_pass(info);
}
static inline void isvd_zheev(
    const CHAR1 jobz, const CHAR1 uplo, const INT n, COMP8 *a, const INT lda, REAL8 *w
) {
  COMP8 qwork; INT lwork = -1, info;
  zheev(&jobz, &uplo, &n, a, &lda, w, &qwork, &lwork, NULL, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  COMP8 *work  = isvd_zmalloc(lwork);
  REAL8 *rwork = isvd_dmalloc(5*n-2);
  zheev(&jobz, &uplo, &n, a, &lda, w, work, &lwork, rwork, &info);  isvd_assert_pass(info);
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_lapack_module
/// Computes the singular value decomposition of a general rectangular matrix.
//@{
static inline void isvd_sgesvd(
    const CHAR1 jobu, const CHAR1 jobvt, const INT m, const INT n, REAL4 *a, const INT lda, REAL4 *s, REAL4 *u, const INT ldu,
    REAL4 *v, const INT ldvt
) {
  REAL4 qwork; INT lwork = -1, info;
  sgesvd(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  REAL4 *work = isvd_smalloc(lwork);
  sgesvd(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, work, &lwork, &info);   isvd_assert_pass(info);
}
static inline void isvd_dgesvd(
    const CHAR1 jobu, const CHAR1 jobvt, const INT m, const INT n, REAL8 *a, const INT lda, REAL8 *s, REAL8 *u, const INT ldu,
    REAL8 *v, const INT ldvt
) {
  REAL8 qwork; INT lwork = -1, info;
  dgesvd(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  REAL8 *work = isvd_dmalloc(lwork);
  dgesvd(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, work, &lwork, &info);   isvd_assert_pass(info);
}
static inline void isvd_cgesvd(
    const CHAR1 jobu, const CHAR1 jobvt, const INT m, const INT n, COMP4 *a, const INT lda, REAL4 *s, COMP4 *u, const INT ldu,
    COMP4 *v, const INT ldvt
) {
  COMP4 qwork; INT lwork = -1, info;
  cgesvd(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, &qwork, &lwork, NULL, &info); isvd_assert_pass(info);
  lwork = crealf(qwork);
  COMP4 *work  = isvd_cmalloc(lwork);
  REAL4 *rwork = isvd_smalloc(5*min(m, n));
  cgesvd(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, work, &lwork, rwork, &info);  isvd_assert_pass(info);
}
static inline void isvd_zgesvd(
    const CHAR1 jobu, const CHAR1 jobvt, const INT m, const INT n, COMP8 *a, const INT lda, REAL8 *s, COMP8 *u, const INT ldu,
    COMP8 *v, const INT ldvt
) {
  COMP8 qwork; INT lwork = -1, info;
  zgesvd(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, &qwork, &lwork, NULL, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  COMP8 *work  = isvd_zmalloc(lwork);
  REAL8 *rwork = isvd_dmalloc(5*min(m, n));
  zgesvd(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, work, &lwork, rwork, &info);  isvd_assert_pass(info);
}
//@}

#undef CHAR1
#undef INT
#undef REAL4
#undef REAL8
#undef COMP4
#undef COMP8

#endif  // _ISVD_LA_LAPACK_LS_H_
