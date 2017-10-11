////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/lapack/least_square.h
/// \brief      The LAPACK least square and eigenvalue problem header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef ISVD_LA_LAPACK_LEAST_SQUARE_H_
#define ISVD_LA_LAPACK_LEAST_SQUARE_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

@ISVD_TYPE_MACRO_DEFINE@

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_ls_module
/// \brief  Computes the QR factorization of a general matrix.
//\{
void isvd_sGeqrf( const INT m, const INT n, REAL4 *a, const INT lda, REAL4 *tau );
void isvd_dGeqrf( const INT m, const INT n, REAL8 *a, const INT lda, REAL8 *tau );
void isvd_cGeqrf( const INT m, const INT n, COMP4 *a, const INT lda, COMP4 *tau );
void isvd_zGeqrf( const INT m, const INT n, COMP8 *a, const INT lda, COMP8 *tau );
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_ls_module
/// \brief  Generates the real orthogonal matrix Q of the QR factorization formed by ?geqrf.
//\{
void isvd_sOrgqr( const INT m, const INT n, const INT k, REAL4 *a, const INT lda, REAL4 *tau );
void isvd_dOrgqr( const INT m, const INT n, const INT k, REAL8 *a, const INT lda, REAL8 *tau );
void isvd_cOrgqr( const INT m, const INT n, const INT k, COMP4 *a, const INT lda, COMP4 *tau );
void isvd_zOrgqr( const INT m, const INT n, const INT k, COMP8 *a, const INT lda, COMP8 *tau );
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_ls_module
/// \brief  Computes the LQ factorization of a general matrix.
//\{
void isvd_sGelqf( const INT m, const INT n, REAL4 *a, const INT lda, REAL4 *tau );
void isvd_dGelqf( const INT m, const INT n, REAL8 *a, const INT lda, REAL8 *tau );
void isvd_cGelqf( const INT m, const INT n, COMP4 *a, const INT lda, COMP4 *tau );
void isvd_zGelqf( const INT m, const INT n, COMP8 *a, const INT lda, COMP8 *tau );
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_ls_module
/// \brief  Generates the real orthogonal matrix Q of the LQ factorization formed by ?gelqf.
//\{
void isvd_sOrglq( const INT m, const INT n, const INT k, REAL4 *a, const INT lda, REAL4 *tau );
void isvd_dOrglq( const INT m, const INT n, const INT k, REAL8 *a, const INT lda, REAL8 *tau );
void isvd_cOrglq( const INT m, const INT n, const INT k, COMP4 *a, const INT lda, COMP4 *tau );
void isvd_zOrglq( const INT m, const INT n, const INT k, COMP8 *a, const INT lda, COMP8 *tau );
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_ls_module
/// \brief  Computes all eigenvalues and, optionally, eigenvectors of a real symmetric matrix.
//\{
void isvd_sSyev( const CHAR1 jobz, const CHAR1 uplo, const INT n, REAL4 *a, const INT lda, REAL4 *w );
void isvd_dSyev( const CHAR1 jobz, const CHAR1 uplo, const INT n, REAL8 *a, const INT lda, REAL8 *w );
void isvd_cSyev( const CHAR1 jobz, const CHAR1 uplo, const INT n, COMP4 *a, const INT lda, REAL4 *w );
void isvd_zSyev( const CHAR1 jobz, const CHAR1 uplo, const INT n, COMP8 *a, const INT lda, REAL8 *w );
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_ls_module
/// \brief  Computes the singular value decomposition of a general rectangular matrix.
//\{
void isvd_sGesvd( const CHAR1 jobu, const CHAR1 jobvt, const INT m, const INT n, REAL4 *a, const INT lda, REAL4 *s, REAL4 *u,
                  const INT ldu, REAL4 *v, const INT ldvt );
void isvd_dGesvd( const CHAR1 jobu, const CHAR1 jobvt, const INT m, const INT n, REAL8 *a, const INT lda, REAL8 *s, REAL8 *u,
                  const INT ldu, REAL8 *v, const INT ldvt );
void isvd_cGesvd( const CHAR1 jobu, const CHAR1 jobvt, const INT m, const INT n, COMP4 *a, const INT lda, REAL4 *s, COMP4 *u,
                  const INT ldu, COMP4 *v, const INT ldvt );
void isvd_zGesvd( const CHAR1 jobu, const CHAR1 jobvt, const INT m, const INT n, COMP8 *a, const INT lda, REAL8 *s, COMP8 *u,
                  const INT ldu, COMP8 *v, const INT ldvt );
//\}

@ISVD_TYPE_MACRO_UNDEF@

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_LA_LAPACK_LEAST_SQUARE_H_
