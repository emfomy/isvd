////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/util/memory.h
/// \brief      The memory utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef ISVD_UTIL_MEMORY_H_
#define ISVD_UTIL_MEMORY_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

isvd_int_t*   isvd_iMalloc( const size_t num );
isvd_s_val_t* isvd_sMalloc( const size_t num );
isvd_d_val_t* isvd_dMalloc( const size_t num );
isvd_c_val_t* isvd_cMalloc( const size_t num );
isvd_z_val_t* isvd_zMalloc( const size_t num );

void isvd_Free( void *ptr );

void isvd_iMemset0( isvd_int_t   *ptr, const size_t num );
void isvd_sMemset0( isvd_s_val_t *ptr, const size_t num );
void isvd_dMemset0( isvd_d_val_t *ptr, const size_t num );
void isvd_cMemset0( isvd_c_val_t *ptr, const size_t num );
void isvd_zMemset0( isvd_z_val_t *ptr, const size_t num );

void isvd_iMemcpy( isvd_int_t   *dst, const isvd_int_t   *src, const size_t num );
void isvd_sMemcpy( isvd_s_val_t *dst, const isvd_s_val_t *src, const size_t num );
void isvd_dMemcpy( isvd_d_val_t *dst, const isvd_d_val_t *src, const size_t num );
void isvd_cMemcpy( isvd_c_val_t *dst, const isvd_c_val_t *src, const size_t num );
void isvd_zMemcpy( isvd_z_val_t *dst, const isvd_z_val_t *src, const size_t num );

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_UTIL_MEMORY_H_
