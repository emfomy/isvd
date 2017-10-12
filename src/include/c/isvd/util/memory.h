////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/util/memory.h
/// \brief      The memory utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef ISVD_UTIL_MEMORY_H_
#define ISVD_UTIL_MEMORY_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

isvd_int_t*   isvd_imalloc( const size_t num );
isvd_s_val_t* isvd_smalloc( const size_t num );
isvd_d_val_t* isvd_dmalloc( const size_t num );
isvd_c_val_t* isvd_cmalloc( const size_t num );
isvd_z_val_t* isvd_zmalloc( const size_t num );

void isvd_free( void *ptr );

void isvd_imemset0( isvd_int_t   *ptr, const size_t num );
void isvd_smemset0( isvd_s_val_t *ptr, const size_t num );
void isvd_dmemset0( isvd_d_val_t *ptr, const size_t num );
void isvd_cmemset0( isvd_c_val_t *ptr, const size_t num );
void isvd_zmemset0( isvd_z_val_t *ptr, const size_t num );

void isvd_imemcpy( isvd_int_t   *dst, const isvd_int_t   *src, const size_t num );
void isvd_smemcpy( isvd_s_val_t *dst, const isvd_s_val_t *src, const size_t num );
void isvd_dmemcpy( isvd_d_val_t *dst, const isvd_d_val_t *src, const size_t num );
void isvd_cmemcpy( isvd_c_val_t *dst, const isvd_c_val_t *src, const size_t num );
void isvd_zmemcpy( isvd_z_val_t *dst, const isvd_z_val_t *src, const size_t num );

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_UTIL_MEMORY_H_
