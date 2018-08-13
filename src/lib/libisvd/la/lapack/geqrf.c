////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/lapack/geqrf.c
/// \brief      The LAPACK Geqrf routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2018 Mu Yang. All rights reserved.
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

extern void sgeqrf_(ISVD_UNKNOWN);
extern void dgeqrf_(ISVD_UNKNOWN);
extern void cgeqrf_(ISVD_UNKNOWN);
extern void zgeqrf_(ISVD_UNKNOWN);

#endif  // ISVD_USE_MKL

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // DOXYGEN_SHOULD_SKIP_THIS

void isvd_sGeqrf(
    const isvd_int_t m, const isvd_int_t n, isvd_s_val_t *a, const isvd_int_t lda, isvd_s_val_t *tau
) {
  isvd_s_val_t qwork; isvd_int_t lwork = -1, info;
  sgeqrf_(&m, &n, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  isvd_s_val_t *work = isvd_sMalloc(lwork);
  sgeqrf_(&m, &n, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_Free(work);
}
void isvd_dGeqrf(
    const isvd_int_t m, const isvd_int_t n, isvd_d_val_t *a, const isvd_int_t lda, isvd_d_val_t *tau
) {
  isvd_d_val_t qwork; isvd_int_t lwork = -1, info;
  dgeqrf_(&m, &n, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  isvd_d_val_t *work = isvd_dMalloc(lwork);
  dgeqrf_(&m, &n, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_Free(work);
}
void isvd_cGeqrf(
    const isvd_int_t m, const isvd_int_t n, isvd_c_val_t *a, const isvd_int_t lda, isvd_c_val_t *tau
) {
  isvd_c_val_t qwork; isvd_int_t lwork = -1, info;
  cgeqrf_(&m, &n, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = crealf(qwork);
  isvd_c_val_t *work  = isvd_cMalloc(lwork);
  cgeqrf_(&m, &n, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_Free(work);
}
void isvd_zGeqrf(
    const isvd_int_t m, const isvd_int_t n, isvd_z_val_t *a, const isvd_int_t lda, isvd_z_val_t *tau
) {
  isvd_z_val_t qwork; isvd_int_t lwork = -1, info;
  zgeqrf_(&m, &n, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  isvd_z_val_t *work  = isvd_zMalloc(lwork);
  zgeqrf_(&m, &n, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_Free(work);
}
//\}
