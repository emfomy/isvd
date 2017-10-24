////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/lapack/least_square.h
/// \brief      The LAPACK least square and eigenvalue problem header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef ISVD_LA_LAPACK_LEAST_SQUARE_H_
#define ISVD_LA_LAPACK_LEAST_SQUARE_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_ls_module
/// \brief  Computes the QR factorization of a general matrix.
//\{
void isvd_sGeqrf( const isvd_int_t m, const isvd_int_t n, isvd_s_val_t *a, const isvd_int_t lda, isvd_s_val_t *tau );
void isvd_dGeqrf( const isvd_int_t m, const isvd_int_t n, isvd_d_val_t *a, const isvd_int_t lda, isvd_d_val_t *tau );
void isvd_cGeqrf( const isvd_int_t m, const isvd_int_t n, isvd_c_val_t *a, const isvd_int_t lda, isvd_c_val_t *tau );
void isvd_zGeqrf( const isvd_int_t m, const isvd_int_t n, isvd_z_val_t *a, const isvd_int_t lda, isvd_z_val_t *tau );
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_ls_module
/// \brief  Generates the real orthogonal matrix Q of the QR factorization formed by ?geqrf.
//\{
void isvd_sOrgqr(
    const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, isvd_s_val_t *a, const isvd_int_t lda, isvd_s_val_t *tau
);
void isvd_dOrgqr(
    const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, isvd_d_val_t *a, const isvd_int_t lda, isvd_d_val_t *tau
);
void isvd_cOrgqr(
    const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, isvd_c_val_t *a, const isvd_int_t lda, isvd_c_val_t *tau
);
void isvd_zOrgqr(
    const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, isvd_z_val_t *a, const isvd_int_t lda, isvd_z_val_t *tau
);
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_ls_module
/// \brief  Computes the LQ factorization of a general matrix.
//\{
void isvd_sGelqf( const isvd_int_t m, const isvd_int_t n, isvd_s_val_t *a, const isvd_int_t lda, isvd_s_val_t *tau );
void isvd_dGelqf( const isvd_int_t m, const isvd_int_t n, isvd_d_val_t *a, const isvd_int_t lda, isvd_d_val_t *tau );
void isvd_cGelqf( const isvd_int_t m, const isvd_int_t n, isvd_c_val_t *a, const isvd_int_t lda, isvd_c_val_t *tau );
void isvd_zGelqf( const isvd_int_t m, const isvd_int_t n, isvd_z_val_t *a, const isvd_int_t lda, isvd_z_val_t *tau );
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_ls_module
/// \brief  Generates the real orthogonal matrix Q of the LQ factorization formed by ?gelqf.
//\{
void isvd_sOrglq(
    const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, isvd_s_val_t *a, const isvd_int_t lda, isvd_s_val_t *tau
);
void isvd_dOrglq(
    const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, isvd_d_val_t *a, const isvd_int_t lda, isvd_d_val_t *tau
);
void isvd_cOrglq(
    const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, isvd_c_val_t *a, const isvd_int_t lda, isvd_c_val_t *tau
);
void isvd_zOrglq(
    const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, isvd_z_val_t *a, const isvd_int_t lda, isvd_z_val_t *tau
);
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_ls_module
/// \brief  Computes all eigenvalues and, optionally, eigenvectors of a real symmetric matrix.
//\{
void isvd_sSyev( const char jobz, const char uplo, const isvd_int_t n, isvd_s_val_t *a, const isvd_int_t lda, isvd_s_val_t *w );
void isvd_dSyev( const char jobz, const char uplo, const isvd_int_t n, isvd_d_val_t *a, const isvd_int_t lda, isvd_d_val_t *w );
void isvd_cSyev( const char jobz, const char uplo, const isvd_int_t n, isvd_c_val_t *a, const isvd_int_t lda, isvd_s_val_t *w );
void isvd_zSyev( const char jobz, const char uplo, const isvd_int_t n, isvd_z_val_t *a, const isvd_int_t lda, isvd_d_val_t *w );
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_ls_module
/// \brief  Computes the singular value decomposition of a general rectangular matrix.
//\{
void isvd_sGesvd(
    const char jobu, const char jobvt, const isvd_int_t m, const isvd_int_t n, isvd_s_val_t *a, const isvd_int_t lda,
    isvd_s_val_t *s, isvd_s_val_t *u, const isvd_int_t ldu, isvd_s_val_t *v, const isvd_int_t ldvt
);
void isvd_dGesvd(
    const char jobu, const char jobvt, const isvd_int_t m, const isvd_int_t n, isvd_d_val_t *a, const isvd_int_t lda,
    isvd_d_val_t *s, isvd_d_val_t *u, const isvd_int_t ldu, isvd_d_val_t *v, const isvd_int_t ldvt
);
void isvd_cGesvd(
    const char jobu, const char jobvt, const isvd_int_t m, const isvd_int_t n, isvd_c_val_t *a, const isvd_int_t lda,
    isvd_s_val_t *s, isvd_c_val_t *u, const isvd_int_t ldu, isvd_c_val_t *v, const isvd_int_t ldvt
);
void isvd_zGesvd(
    const char jobu, const char jobvt, const isvd_int_t m, const isvd_int_t n, isvd_z_val_t *a, const isvd_int_t lda,
    isvd_d_val_t *s, isvd_z_val_t *u, const isvd_int_t ldu, isvd_z_val_t *v, const isvd_int_t ldvt
);
//\}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_LA_LAPACK_LEAST_SQUARE_H_
