////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/lapack/geinv.c
/// \brief      The LAPACK Getrf+Getri routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/la/lapack/linear_equation.h>
#include <libisvd/la/def.h>
#include <isvd/util/memory.h>

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
    const isvd_int_t n, isvd_s_val_t *a, const isvd_int_t lda
) {
  isvd_s_val_t qwork; isvd_int_t lwork = -1, info;
  sgetri_(&n, a, &lda, NULL, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  isvd_int_t *ipiv = isvd_imalloc(n);
  isvd_s_val_t *work = isvd_smalloc(lwork);
  sgetrf_(&n, &n, a, &lda, ipiv, &info);             isvd_assert_pass(info);
  sgetri_(&n, a, &lda, ipiv, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(ipiv);
  isvd_free(work);
}
void isvd_dGeinv(
    const isvd_int_t n, isvd_d_val_t *a, const isvd_int_t lda
) {
  isvd_d_val_t qwork; isvd_int_t lwork = -1, info;
  dgetri_(&n, a, &lda, NULL, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  isvd_int_t *ipiv = isvd_imalloc(n);
  isvd_d_val_t *work = isvd_dmalloc(lwork);
  dgetrf_(&n, &n, a, &lda, ipiv, &info);             isvd_assert_pass(info);
  dgetri_(&n, a, &lda, ipiv, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(ipiv);
  isvd_free(work);
}
void isvd_cGeinv(
    const isvd_int_t n, isvd_c_val_t *a, const isvd_int_t lda
) {
  isvd_c_val_t qwork; isvd_int_t lwork = -1, info;
  cgetri_(&n, a, &lda, NULL, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  isvd_int_t *ipiv = isvd_imalloc(n);
  isvd_c_val_t *work  = isvd_cmalloc(lwork);
  cgetrf_(&n, &n, a, &lda, ipiv, &info);             isvd_assert_pass(info);
  cgetri_(&n, a, &lda, ipiv, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(ipiv);
  isvd_free(work);
}
void isvd_zGeinv(
    const isvd_int_t n, isvd_z_val_t *a, const isvd_int_t lda
) {
  isvd_z_val_t qwork; isvd_int_t lwork = -1, info;
  zgetri_(&n, a, &lda, NULL, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  isvd_int_t *ipiv = isvd_imalloc(n);
  isvd_z_val_t *work  = isvd_zmalloc(lwork);
  zgetrf_(&n, &n, a, &lda, ipiv, &info);             isvd_assert_pass(info);
  zgetri_(&n, a, &lda, ipiv, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(ipiv);
  isvd_free(work);
}
