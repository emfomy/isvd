////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/lapack/least_square.h
/// \brief      The LAPACK least square and eigenvalue problem header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _ISVD_LA_LAPACK_LEAST_SQUARE_H_
#define _ISVD_LA_LAPACK_LEAST_SQUARE_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

@ISVD_LA_BLAS_TYPE_DEFINE@

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_ls_module
/// Computes all eigenvalues and, optionally, eigenvectors of a real symmetric matrix.
//\{
void isvd_sSyev( const CHAR1 jobz, const CHAR1 uplo, const INT n, REAL4 *a, const INT lda, REAL4 *w );
void isvd_dSyev( const CHAR1 jobz, const CHAR1 uplo, const INT n, REAL8 *a, const INT lda, REAL8 *w );
void isvd_cSyev( const CHAR1 jobz, const CHAR1 uplo, const INT n, COMP4 *a, const INT lda, REAL4 *w );
void isvd_zSyev( const CHAR1 jobz, const CHAR1 uplo, const INT n, COMP8 *a, const INT lda, REAL8 *w );
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_ls_module
/// Computes the singular value decomposition of a general rectangular matrix.
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

@ISVD_LA_BLAS_TYPE_UNDEF@

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_LA_LAPACK_LEAST_SQUARE_H_
