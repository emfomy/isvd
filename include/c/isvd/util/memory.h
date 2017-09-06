////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/util/memory.h
/// \brief      The memory utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _ISVD_UTIL_MEMORY_H_
#define _ISVD_UTIL_MEMORY_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

isvd_int_t* isvd_imalloc( const size_t num );
float* isvd_smalloc( const size_t num );
double* isvd_dmalloc( const size_t num );
_Complex float* isvd_cmalloc( const size_t num );
_Complex double* isvd_zmalloc( const size_t num );

void isvd_free( void *ptr );

void isvd_imemset0( isvd_int_t *ptr, const size_t num );
void isvd_smemset0( float *ptr, const size_t num );
void isvd_dmemset0( double *ptr, const size_t num );
void isvd_cmemset0( _Complex float *ptr, const size_t num );
void isvd_zmemset0( _Complex double *ptr, const size_t num );

void isvd_imemcpy( isvd_int_t *dst, const isvd_int_t *src, const size_t num );
void isvd_smemcpy( float *dst, const float *src, const size_t num );
void isvd_dmemcpy( double *dst, const double *src, const size_t num );
void isvd_cmemcpy( _Complex float *dst, const _Complex float *src, const size_t num );
void isvd_zmemcpy( _Complex double *dst, const _Complex double *src, const size_t num );

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_UTIL_MEMORY_H_
