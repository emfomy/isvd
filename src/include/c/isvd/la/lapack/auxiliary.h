////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/lapack/auxiliary.h
/// \brief      The LAPACK auxiliary header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef ISVD_LA_LAPACK_AUXILIARY_H_
#define ISVD_LA_LAPACK_AUXILIARY_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

extern void slacpy_( const char *uplo, const isvd_int_t *m, const isvd_int_t *n, const isvd_s_val_t *a, const isvd_int_t *lda,
                     isvd_s_val_t *b, const isvd_int_t *ldb );
extern void dlacpy_( const char *uplo, const isvd_int_t *m, const isvd_int_t *n, const isvd_d_val_t *a, const isvd_int_t *lda,
                     isvd_d_val_t *b, const isvd_int_t *ldb );
extern void clacpy_( const char *uplo, const isvd_int_t *m, const isvd_int_t *n, const isvd_c_val_t *a, const isvd_int_t *lda,
                     isvd_c_val_t *b, const isvd_int_t *ldb );
extern void zlacpy_( const char *uplo, const isvd_int_t *m, const isvd_int_t *n, const isvd_z_val_t *a, const isvd_int_t *lda,
                     isvd_z_val_t *b, const isvd_int_t *ldb );

extern void slarnv_( const isvd_int_t *idist, isvd_int_t *iseed, const isvd_int_t *n, isvd_s_val_t *x );
extern void dlarnv_( const isvd_int_t *idist, isvd_int_t *iseed, const isvd_int_t *n, isvd_d_val_t *x );
extern void clarnv_( const isvd_int_t *idist, isvd_int_t *iseed, const isvd_int_t *n, isvd_c_val_t *x );
extern void zlarnv_( const isvd_int_t *idist, isvd_int_t *iseed, const isvd_int_t *n, isvd_z_val_t *x );

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_aux_module
/// \brief  Copies all or part of one two-dimensional array to another.
//\{
static inline void isvd_sLacpy(
    const char uplo, const isvd_int_t m, const isvd_int_t n, const isvd_s_val_t *a, const isvd_int_t lda, isvd_s_val_t *b,
    const isvd_int_t ldb
) { slacpy_(&uplo, &m, &n, a, &lda, b, &ldb); }
static inline void isvd_dLacpy(
    const char uplo, const isvd_int_t m, const isvd_int_t n, const isvd_d_val_t *a, const isvd_int_t lda, isvd_d_val_t *b,
    const isvd_int_t ldb
) { dlacpy_(&uplo, &m, &n, a, &lda, b, &ldb); }
static inline void isvd_cLacpy(
    const char uplo, const isvd_int_t m, const isvd_int_t n, const isvd_c_val_t *a, const isvd_int_t lda, isvd_c_val_t *b,
    const isvd_int_t ldb
) { clacpy_(&uplo, &m, &n, a, &lda, b, &ldb); }
static inline void isvd_zLacpy(
    const char uplo, const isvd_int_t m, const isvd_int_t n, const isvd_z_val_t *a, const isvd_int_t lda, isvd_z_val_t *b,
    const isvd_int_t ldb
) { zlacpy_(&uplo, &m, &n, a, &lda, b, &ldb); }
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_aux_module
/// \brief  Returns a vector of random numbers from a uniform or normal distribution.
//\{
static inline void isvd_sLarnv(
    const isvd_int_t idist, isvd_int_t *iseed, const isvd_int_t n, isvd_s_val_t *x
) { slarnv_(&idist, iseed, &n, x); }
static inline void isvd_dLarnv(
    const isvd_int_t idist, isvd_int_t *iseed, const isvd_int_t n, isvd_d_val_t *x
) { dlarnv_(&idist, iseed, &n, x); }
static inline void isvd_cLarnv(
    const isvd_int_t idist, isvd_int_t *iseed, const isvd_int_t n, isvd_c_val_t *x
) { clarnv_(&idist, iseed, &n, x); }
static inline void isvd_zLarnv(
    const isvd_int_t idist, isvd_int_t *iseed, const isvd_int_t n, isvd_z_val_t *x
) { zlarnv_(&idist, iseed, &n, x); }
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_aux_module
/// \brief  Tests two characters for equality regardless of the case.
bool isvd_Lsame( const char ca, const char cb );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_aux_module
/// \brief  Tests two character strings for equality regardless of the case.
bool isvd_Lsamen( const isvd_int_t n, const char *sa, const char *sb );

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_LA_LAPACK_AUXILIARY_H_
