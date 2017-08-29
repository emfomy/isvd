////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/la/lapack/syev.h
/// \brief      The LAPACK SYEV routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _LIBISVD_LA_LAPACK_SYEV_H_
#define _LIBISVD_LA_LAPACK_SYEV_H_

#include <libisvd/def.h>
#include <libisvd/util/memory.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#define CHAR1 char
#define INT   isvd_int_t
#define REAL4 float
#define REAL8 double
#define COMP4 complex float
#define COMP8 complex double

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

#if !defined(ISVD_USE_MKL)

extern void ssyev_(ISVD_UNKNOWN);
extern void dsyev_(ISVD_UNKNOWN);
extern void cheev_(ISVD_UNKNOWN);
extern void zheev_(ISVD_UNKNOWN);

#endif  // ISVD_USE_MKL

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  la_lapack_module
/// Computes all eigenvalues and, optionally, eigenvectors of a real symmetric matrix.
//\{
static inline void isvd_ssyev(
    const CHAR1 jobz, const CHAR1 uplo, const INT n, REAL4 *a, const INT lda, REAL4 *w
) {
  REAL4 qwork; INT lwork = -1, info;
  ssyev_(&jobz, &uplo, &n, a, &lda, w, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  REAL4 *work = isvd_smalloc(lwork);
  ssyev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, &info);   isvd_assert_pass(info);
}
static inline void isvd_dsyev(
    const CHAR1 jobz, const CHAR1 uplo, const INT n, REAL8 *a, const INT lda, REAL8 *w
) {
  REAL8 qwork; INT lwork = -1, info;
  dsyev_(&jobz, &uplo, &n, a, &lda, w, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  REAL8 *work = isvd_dmalloc(lwork);
  dsyev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, &info);   isvd_assert_pass(info);
}
static inline void isvd_cheev(
    const CHAR1 jobz, const CHAR1 uplo, const INT n, COMP4 *a, const INT lda, REAL4 *w
) {
  COMP4 qwork; INT lwork = -1, info;
  cheev_(&jobz, &uplo, &n, a, &lda, w, &qwork, &lwork, nullptr, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  COMP4 *work  = isvd_cmalloc(lwork);
  REAL4 *rwork = isvd_smalloc(5*n-2);
  cheev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, rwork, &info);  isvd_assert_pass(info);
}
static inline void isvd_zheev(
    const CHAR1 jobz, const CHAR1 uplo, const INT n, COMP8 *a, const INT lda, REAL8 *w
) {
  COMP8 qwork; INT lwork = -1, info;
  zheev_(&jobz, &uplo, &n, a, &lda, w, &qwork, &lwork, nullptr, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  COMP8 *work  = isvd_zmalloc(lwork);
  REAL8 *rwork = isvd_dmalloc(5*n-2);
  zheev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, rwork, &info);  isvd_assert_pass(info);
}
//\}

#undef CHAR1
#undef INT
#undef REAL4
#undef REAL8
#undef COMP4
#undef COMP8

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _LIBISVD_LA_LAPACK_SYEV_H_
