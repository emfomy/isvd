////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/lapack/geinv.h
/// \brief      The LAPACK GETRF+GETRI routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _ISVD_LA_LAPACK_GEINV_H_
#define _ISVD_LA_LAPACK_GEINV_H_

#include <isvd/def.h>
#include <isvd/util/memory.h>

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

extern void sgetrf_(ISVD_UNKNOWN);
extern void dgetrf_(ISVD_UNKNOWN);
extern void cgetrf_(ISVD_UNKNOWN);
extern void zgetrf_(ISVD_UNKNOWN);

extern void sgetri_(ISVD_UNKNOWN);
extern void dgetri_(ISVD_UNKNOWN);
extern void cgetri_(ISVD_UNKNOWN);
extern void zgetri_(ISVD_UNKNOWN);

#endif  // ISVD_USE_MKL

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  la_lapack_module
/// Computes the inverse of a square matrix using LU factorization.
//\{
static inline void isvd_sgeinv(
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
static inline void isvd_dgeinv(
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
static inline void isvd_cgeinv(
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
static inline void isvd_zgeinv(
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

#endif  // _ISVD_LA_LAPACK_GEINV_H_
