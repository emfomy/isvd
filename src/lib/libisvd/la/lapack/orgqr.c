////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/lapack/orgqr.c
/// \brief      The LAPACK Orgqr routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/la/lapack/least_square.h>
#include <libisvd/la/def.h>
#include <isvd/util/memory.h>
#include <libisvd/util/function.h>

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#if !defined(ISVD_USE_MKL)

extern void sorgqr_(ISVD_UNKNOWN);
extern void dorgqr_(ISVD_UNKNOWN);
extern void cungqr_(ISVD_UNKNOWN);
extern void zungqr_(ISVD_UNKNOWN);

#endif  // ISVD_USE_MKL

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // DOXYGEN_SHOULD_SKIP_THIS

void isvd_sOrgqr(
    const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, isvd_s_val_t *a, const isvd_int_t lda, isvd_s_val_t *tau
) {
  isvd_s_val_t qwork; isvd_int_t lwork = -1, info;
  sorgqr_(&m, &n, &k, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  isvd_s_val_t *work = isvd_smalloc(lwork);
  sorgqr_(&m, &n, &k, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
void isvd_dOrgqr(
    const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, isvd_d_val_t *a, const isvd_int_t lda, isvd_d_val_t *tau
) {
  isvd_d_val_t qwork; isvd_int_t lwork = -1, info;
  dorgqr_(&m, &n, &k, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  isvd_d_val_t *work = isvd_dmalloc(lwork);
  dorgqr_(&m, &n, &k, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
void isvd_cOrgqr(
    const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, isvd_c_val_t *a, const isvd_int_t lda, isvd_c_val_t *tau
) {
  isvd_c_val_t qwork; isvd_int_t lwork = -1, info;
  cungqr_(&m, &n, &k, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = crealf(qwork);
  isvd_c_val_t *work  = isvd_cmalloc(lwork);
  cungqr_(&m, &n, &k, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
void isvd_zOrgqr(
    const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, isvd_z_val_t *a, const isvd_int_t lda, isvd_z_val_t *tau
) {
  isvd_z_val_t qwork; isvd_int_t lwork = -1, info;
  zungqr_(&m, &n, &k, a, &lda, tau, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  isvd_z_val_t *work  = isvd_zmalloc(lwork);
  zungqr_(&m, &n, &k, a, &lda, tau, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
//\}
