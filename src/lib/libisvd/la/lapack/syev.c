////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/lapack/syev.c
/// \brief      The LAPACK Syev routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/la/lapack/least_square.h>
#include <libisvd/la/def.h>
#include <isvd/util/memory.h>

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#if !defined(ISVD_USE_MKL)

extern void ssyev_(ISVD_UNKNOWN);
extern void dsyev_(ISVD_UNKNOWN);
extern void cheev_(ISVD_UNKNOWN);
extern void zheev_(ISVD_UNKNOWN);

#endif  // ISVD_USE_MKL

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // DOXYGEN_SHOULD_SKIP_THIS

void isvd_sSyev(
    const char jobz, const char uplo, const isvd_int_t n, isvd_s_val_t *a, const isvd_int_t lda, isvd_s_val_t *w
) {
  isvd_s_val_t qwork; isvd_int_t lwork = -1, info;
  ssyev_(&jobz, &uplo, &n, a, &lda, w, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  isvd_s_val_t *work = isvd_sMalloc(lwork);
  ssyev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_Free(work);
}
void isvd_dSyev(
    const char jobz, const char uplo, const isvd_int_t n, isvd_d_val_t *a, const isvd_int_t lda, isvd_d_val_t *w
) {
  isvd_d_val_t qwork; isvd_int_t lwork = -1, info;
  dsyev_(&jobz, &uplo, &n, a, &lda, w, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  isvd_d_val_t *work = isvd_dMalloc(lwork);
  dsyev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_Free(work);
}
void isvd_cSyev(
    const char jobz, const char uplo, const isvd_int_t n, isvd_c_val_t *a, const isvd_int_t lda, isvd_s_val_t *w
) {
  isvd_c_val_t qwork; isvd_int_t lwork = -1, info;
  cheev_(&jobz, &uplo, &n, a, &lda, w, &qwork, &lwork, NULL, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  isvd_c_val_t *work  = isvd_cMalloc(lwork);
  isvd_s_val_t *rwork = isvd_sMalloc(5*n-2);
  cheev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, rwork, &info);  isvd_assert_pass(info);
  isvd_Free(work);
  isvd_Free(rwork);
}
void isvd_zSyev(
    const char jobz, const char uplo, const isvd_int_t n, isvd_z_val_t *a, const isvd_int_t lda, isvd_d_val_t *w
) {
  isvd_z_val_t qwork; isvd_int_t lwork = -1, info;
  zheev_(&jobz, &uplo, &n, a, &lda, w, &qwork, &lwork, NULL, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  isvd_z_val_t *work  = isvd_zMalloc(lwork);
  isvd_d_val_t *rwork = isvd_dMalloc(5*n-2);
  zheev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, rwork, &info);  isvd_assert_pass(info);
  isvd_Free(work);
  isvd_Free(rwork);
}
