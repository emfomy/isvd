////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/blas/blas1.h
/// \brief      The BLAS level 1 header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef ISVD_LA_BLAS_BLAS1_H_
#define ISVD_LA_BLAS_BLAS1_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

extern isvd_s_val_t sdot_(ISVD_UNKNOWN);
extern isvd_d_val_t ddot_(ISVD_UNKNOWN);
extern isvd_c_val_t cdotc_(ISVD_UNKNOWN);
extern isvd_z_val_t zdotc_(ISVD_UNKNOWN);
extern isvd_c_val_t cdotu_(ISVD_UNKNOWN);
extern isvd_z_val_t zdotu_(ISVD_UNKNOWN);

extern isvd_s_val_t snrm2_(ISVD_UNKNOWN);
extern isvd_d_val_t dnrm2_(ISVD_UNKNOWN);
extern isvd_s_val_t scnrm2_(ISVD_UNKNOWN);
extern isvd_d_val_t dznrm2_(ISVD_UNKNOWN);

extern isvd_s_val_t sasum_(ISVD_UNKNOWN);
extern isvd_d_val_t dasum_(ISVD_UNKNOWN);
extern isvd_s_val_t scasum_(ISVD_UNKNOWN);
extern isvd_d_val_t dzasum_(ISVD_UNKNOWN);

extern void sscal_(ISVD_UNKNOWN);
extern void dscal_(ISVD_UNKNOWN);
extern void cscal_(ISVD_UNKNOWN);
extern void zscal_(ISVD_UNKNOWN);
extern void csscal_(ISVD_UNKNOWN);
extern void zdscal_(ISVD_UNKNOWN);

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_1_module
/// \brief  Computes a vector-vector dot product.
//\{
static inline isvd_s_val_t isvd_sDot(
    const isvd_int_t n, const isvd_s_val_t *x, const isvd_int_t incx, isvd_s_val_t *y, const isvd_int_t incy
) { return sdot_(&n, x, &incx, y, &incy); }
static inline isvd_d_val_t isvd_dDot(
    const isvd_int_t n, const isvd_d_val_t *x, const isvd_int_t incx, isvd_d_val_t *y, const isvd_int_t incy
) { return ddot_(&n, x, &incx, y, &incy); }
static inline isvd_c_val_t isvd_cDotc(
    const isvd_int_t n, const isvd_c_val_t *x, const isvd_int_t incx, isvd_c_val_t *y, const isvd_int_t incy
) { return cdotc_(&n, x, &incx, y, &incy); }
static inline isvd_z_val_t isvd_zDotc(
    const isvd_int_t n, const isvd_z_val_t *x, const isvd_int_t incx, isvd_z_val_t *y, const isvd_int_t incy
) { return zdotc_(&n, x, &incx, y, &incy); }
static inline isvd_c_val_t isvd_cDotu(
    const isvd_int_t n, const isvd_c_val_t *x, const isvd_int_t incx, isvd_c_val_t *y, const isvd_int_t incy
) { return cdotu_(&n, x, &incx, y, &incy); }
static inline isvd_z_val_t isvd_zDotu(
    const isvd_int_t n, const isvd_z_val_t *x, const isvd_int_t incx, isvd_z_val_t *y, const isvd_int_t incy
) { return zdotu_(&n, x, &incx, y, &incy); }
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_1_module
/// \brief  Computes the Euclidean norm of a vector.
//\{
static inline isvd_s_val_t isvd_sNrm2(
    const isvd_int_t n, const isvd_s_val_t *x, const isvd_int_t incx
) { return snrm2_(&n, x, &incx); }
static inline isvd_d_val_t isvd_dNrm2(
    const isvd_int_t n, const isvd_d_val_t *x, const isvd_int_t incx
) { return dnrm2_(&n, x, &incx); }
static inline isvd_s_val_t isvd_scNrm2(
    const isvd_int_t n, const isvd_c_val_t *x, const isvd_int_t incx
) { return scnrm2_(&n, x, &incx); }
static inline isvd_d_val_t isvd_dzNrm2(
    const isvd_int_t n, const isvd_z_val_t *x, const isvd_int_t incx
) { return dznrm2_(&n, x, &incx); }
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_1_module
/// \brief  Computes the sum of magnitudes of the vector elements.
//\{
static inline isvd_s_val_t isvd_sAsum(
    const isvd_int_t n, const isvd_s_val_t *x, const isvd_int_t incx
) { return  sasum_(&n, x, &incx); }
static inline isvd_d_val_t isvd_dAsum(
    const isvd_int_t n, const isvd_d_val_t *x, const isvd_int_t incx
) { return  dasum_(&n, x, &incx); }
static inline isvd_s_val_t isvd_scAsum(
    const isvd_int_t n, const isvd_c_val_t *x, const isvd_int_t incx
) { return scasum_(&n, x, &incx); }
static inline isvd_d_val_t isvd_dzAsum(
    const isvd_int_t n, const isvd_z_val_t *x, const isvd_int_t incx
) { return dzasum_(&n, x, &incx); }
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_1_module
/// \brief  Finds the index of the element with maximum absolute value.
//\{
isvd_int_t isvd_isAmax( const isvd_int_t n, const isvd_s_val_t *x, const isvd_int_t incx );
isvd_int_t isvd_idAmax( const isvd_int_t n, const isvd_d_val_t *x, const isvd_int_t incx );
isvd_int_t isvd_icAmax( const isvd_int_t n, const isvd_c_val_t *x, const isvd_int_t incx );
isvd_int_t isvd_izAmax( const isvd_int_t n, const isvd_z_val_t *x, const isvd_int_t incx );
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_1_module
/// \brief  Finds the index of the element with minimum absolute value.
//\{
isvd_int_t isvd_isAmin( const isvd_int_t n, const isvd_s_val_t *x, const isvd_int_t incx );
isvd_int_t isvd_idAmin( const isvd_int_t n, const isvd_d_val_t *x, const isvd_int_t incx );
isvd_int_t isvd_icAmin( const isvd_int_t n, const isvd_c_val_t *x, const isvd_int_t incx );
isvd_int_t isvd_izAmin( const isvd_int_t n, const isvd_z_val_t *x, const isvd_int_t incx );
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_1_module
/// \brief  Finds the the element with maximum absolute value.
//\{
isvd_s_val_t isvd_sAmax( const isvd_int_t n, const isvd_s_val_t *x, const isvd_int_t incx );
isvd_d_val_t isvd_dAmax( const isvd_int_t n, const isvd_d_val_t *x, const isvd_int_t incx );
isvd_c_val_t isvd_cAmax( const isvd_int_t n, const isvd_c_val_t *x, const isvd_int_t incx );
isvd_z_val_t isvd_zAmax( const isvd_int_t n, const isvd_z_val_t *x, const isvd_int_t incx );
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_1_module
/// \brief  Finds the the element with minimum absolute value.
//\{
isvd_s_val_t isvd_sAmin( const isvd_int_t n, const isvd_s_val_t *x, const isvd_int_t incx );
isvd_d_val_t isvd_dAmin( const isvd_int_t n, const isvd_d_val_t *x, const isvd_int_t incx );
isvd_c_val_t isvd_cAmin( const isvd_int_t n, const isvd_c_val_t *x, const isvd_int_t incx );
isvd_z_val_t isvd_zAmin( const isvd_int_t n, const isvd_z_val_t *x, const isvd_int_t incx );
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_1_module
/// \brief  Computes the product of a vector by a scalar.
//\{
static inline void isvd_sScal(
    const isvd_int_t n, const isvd_s_val_t alpha, isvd_s_val_t *x, const isvd_int_t incx
) { sscal_(&n, &alpha, x, &incx); }
static inline void isvd_dScal(
    const isvd_int_t n, const isvd_d_val_t alpha, isvd_d_val_t *x, const isvd_int_t incx
) { dscal_(&n, &alpha, x, &incx); }
static inline void isvd_cScal(
    const isvd_int_t n, const isvd_c_val_t alpha, isvd_c_val_t *x, const isvd_int_t incx
) { cscal_(&n, &alpha, x, &incx); }
static inline void isvd_zScal(
    const isvd_int_t n, const isvd_z_val_t alpha, isvd_z_val_t *x, const isvd_int_t incx
) { zscal_(&n, &alpha, x, &incx); }
static inline void isvd_csScal(
    const isvd_int_t n, const isvd_s_val_t alpha, isvd_c_val_t *x, const isvd_int_t incx
) { csscal_(&n, &alpha, x, &incx); }
static inline void isvd_zdScal(
    const isvd_int_t n, const isvd_d_val_t alpha, isvd_z_val_t *x, const isvd_int_t incx
) { zdscal_(&n, &alpha, x, &incx); }
//\}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_LA_BLAS_BLAS1_H_
