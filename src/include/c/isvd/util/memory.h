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

@ISVD_TYPE_MACRO_DEFINE@

INT*   isvd_imalloc( const size_t num );
REAL4* isvd_smalloc( const size_t num );
REAL8* isvd_dmalloc( const size_t num );
COMP4* isvd_cmalloc( const size_t num );
COMP8* isvd_zmalloc( const size_t num );

void isvd_free( void *ptr );

void isvd_imemset0( INT   *ptr, const size_t num );
void isvd_smemset0( REAL4 *ptr, const size_t num );
void isvd_dmemset0( REAL8 *ptr, const size_t num );
void isvd_cmemset0( COMP4 *ptr, const size_t num );
void isvd_zmemset0( COMP8 *ptr, const size_t num );

void isvd_imemcpy( INT   *dst, const INT   *src, const size_t num );
void isvd_smemcpy( REAL4 *dst, const REAL4 *src, const size_t num );
void isvd_dmemcpy( REAL8 *dst, const REAL8 *src, const size_t num );
void isvd_cmemcpy( COMP4 *dst, const COMP4 *src, const size_t num );
void isvd_zmemcpy( COMP8 *dst, const COMP8 *src, const size_t num );

@ISVD_TYPE_MACRO_UNDEF@

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_UTIL_MEMORY_H_
