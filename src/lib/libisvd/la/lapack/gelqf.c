////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/lapack/gelqf.c
/// \brief      The LAPACK Gelqf routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/la/lapack/least_square.h>
#include <libisvd/la/def.h>
#include <libisvd/util/function.h>
#include <isvd/util/memory.h>

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
    const isvd_int_t m, const isvd_int_t n, isvd_s_val_t *a, const isvd_int_t lda, isvd_s_val_t *tau
) {
  isvd_s_val_t qwork; isvd_int_t lwork = -1, info;
  sgelqf_(&m, &n, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  isvd_s_val_t *work = isvd_sMalloc(lwork);
  sgelqf_(&m, &n, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_Free(work);
}
void isvd_dGelqf(
    const isvd_int_t m, const isvd_int_t n, isvd_d_val_t *a, const isvd_int_t lda, isvd_d_val_t *tau
) {
  isvd_d_val_t qwork; isvd_int_t lwork = -1, info;
  dgelqf_(&m, &n, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  isvd_d_val_t *work = isvd_dMalloc(lwork);
  dgelqf_(&m, &n, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_Free(work);
}
void isvd_cGelqf(
    const isvd_int_t m, const isvd_int_t n, isvd_c_val_t *a, const isvd_int_t lda, isvd_c_val_t *tau
) {
  isvd_c_val_t qwork; isvd_int_t lwork = -1, info;
  cgelqf_(&m, &n, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = crealf(qwork);
  isvd_c_val_t *work  = isvd_cMalloc(lwork);
  cgelqf_(&m, &n, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_Free(work);
}
void isvd_zGelqf(
    const isvd_int_t m, const isvd_int_t n, isvd_z_val_t *a, const isvd_int_t lda, isvd_z_val_t *tau
) {
  isvd_z_val_t qwork; isvd_int_t lwork = -1, info;
  zgelqf_(&m, &n, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  isvd_z_val_t *work  = isvd_zMalloc(lwork);
  zgelqf_(&m, &n, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_Free(work);
}
//\}
