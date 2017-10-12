////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/lapack/gesvd.c
/// \brief      The LAPACK Gesvd routine.
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

extern void sgesvd_(ISVD_UNKNOWN);
extern void dgesvd_(ISVD_UNKNOWN);
extern void cgesvd_(ISVD_UNKNOWN);
extern void zgesvd_(ISVD_UNKNOWN);

#endif  // ISVD_USE_MKL

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // DOXYGEN_SHOULD_SKIP_THIS

void isvd_sGesvd(
    const char jobu, const char jobvt, const isvd_int_t m, const isvd_int_t n, isvd_s_val_t *a, const isvd_int_t lda,
    isvd_s_val_t *s, isvd_s_val_t *u, const isvd_int_t ldu, isvd_s_val_t *v, const isvd_int_t ldvt
) {
  isvd_s_val_t qwork; isvd_int_t lwork = -1, info;
  sgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  isvd_s_val_t *work = isvd_smalloc(lwork);
  sgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
void isvd_dGesvd(
    const char jobu, const char jobvt, const isvd_int_t m, const isvd_int_t n, isvd_d_val_t *a, const isvd_int_t lda,
    isvd_d_val_t *s, isvd_d_val_t *u, const isvd_int_t ldu, isvd_d_val_t *v, const isvd_int_t ldvt
) {
  isvd_d_val_t qwork; isvd_int_t lwork = -1, info;
  dgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, &qwork, &lwork, &info); isvd_assert_pass(info);
  lwork = qwork;
  isvd_d_val_t *work = isvd_dmalloc(lwork);
  dgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, work, &lwork, &info);   isvd_assert_pass(info);
  isvd_free(work);
}
void isvd_cGesvd(
    const char jobu, const char jobvt, const isvd_int_t m, const isvd_int_t n, isvd_c_val_t *a, const isvd_int_t lda,
    isvd_s_val_t *s, isvd_c_val_t *u, const isvd_int_t ldu, isvd_c_val_t *v, const isvd_int_t ldvt
) {
  isvd_c_val_t qwork; isvd_int_t lwork = -1, info;
  cgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, &qwork, &lwork, NULL, &info); isvd_assert_pass(info);
  lwork = crealf(qwork);
  isvd_c_val_t *work  = isvd_cmalloc(lwork);
  isvd_s_val_t *rwork = isvd_smalloc(5*min(m, n));
  cgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, work, &lwork, rwork, &info);  isvd_assert_pass(info);
  isvd_free(work);
  isvd_free(rwork);
}
void isvd_zGesvd(
    const char jobu, const char jobvt, const isvd_int_t m, const isvd_int_t n, isvd_z_val_t *a, const isvd_int_t lda,
    isvd_d_val_t *s, isvd_z_val_t *u, const isvd_int_t ldu, isvd_z_val_t *v, const isvd_int_t ldvt
) {
  isvd_z_val_t qwork; isvd_int_t lwork = -1, info;
  zgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, &qwork, &lwork, NULL, &info); isvd_assert_pass(info);
  lwork = creal(qwork);
  isvd_z_val_t *work  = isvd_zmalloc(lwork);
  isvd_d_val_t *rwork = isvd_dmalloc(5*min(m, n));
  zgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, v, &ldvt, work, &lwork, rwork, &info);  isvd_assert_pass(info);
  isvd_free(work);
  isvd_free(rwork);
}
//\}
