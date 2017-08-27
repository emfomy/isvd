////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file    include/c/isvd/la/lapack/gesvd.h
/// \brief   The LAPACK GESVD routine.
///
/// \author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_LA_LAPACK_GESVD_H_
#define _ISVD_LA_LAPACK_GESVD_H_

#include <isvd/def.h>
#include <isvd/util/memory.h>
#include <isvd/util/function.h>

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

extern void sgesvd_(ISVD_UNKNOWN);
extern void dgesvd_(ISVD_UNKNOWN);
extern void cgesvd_(ISVD_UNKNOWN);
extern void zgesvd_(ISVD_UNKNOWN);

#endif  // ISVD_USE_MKL

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  la_lapack_module
/// Computes the singular value decomposition of a general rectangular matrix.
//\{
static inline void isvd_sgesvd(
    const CHAR1 jobu, const CHAR1 jobvt, const INT m, const INT n, REAL4 *a, const INT lda, REAL4 *s, REAL4 *u, const INT ldu,
    REAL4 *v, const INT ldvt
) {
  REAL4 qwork; INT lwork = -1, info;
  sgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  REAL4 *work = isvd_smalloc(lwork);
  sgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, work, &lwork, &info);   isvd_assert_pass(info);
}
static inline void isvd_dgesvd(
    const CHAR1 jobu, const CHAR1 jobvt, const INT m, const INT n, REAL8 *a, const INT lda, REAL8 *s, REAL8 *u, const INT ldu,
    REAL8 *v, const INT ldvt
) {
  REAL8 qwork; INT lwork = -1, info;
  dgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  REAL8 *work = isvd_dmalloc(lwork);
  dgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, work, &lwork, &info);   isvd_assert_pass(info);
}
static inline void isvd_cgesvd(
    const CHAR1 jobu, const CHAR1 jobvt, const INT m, const INT n, COMP4 *a, const INT lda, REAL4 *s, COMP4 *u, const INT ldu,
    COMP4 *v, const INT ldvt
) {
  COMP4 qwork; INT lwork = -1, info;
  cgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, &qwork, &lwork, NULL, &info); isvd_assert_pass(info);
  lwork = crealf(qwork);
  COMP4 *work  = isvd_cmalloc(lwork);
  REAL4 *rwork = isvd_smalloc(5*min(m, n));
  cgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, work, &lwork, rwork, &info);  isvd_assert_pass(info);
}
static inline void isvd_zgesvd(
    const CHAR1 jobu, const CHAR1 jobvt, const INT m, const INT n, COMP8 *a, const INT lda, REAL8 *s, COMP8 *u, const INT ldu,
    COMP8 *v, const INT ldvt
) {
  COMP8 qwork; INT lwork = -1, info;
  zgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, &qwork, &lwork, NULL, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  COMP8 *work  = isvd_zmalloc(lwork);
  REAL8 *rwork = isvd_dmalloc(5*min(m, n));
  zgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, work, &lwork, rwork, &info);  isvd_assert_pass(info);
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

#endif  // _ISVD_LA_LAPACK_GESVD_H_
