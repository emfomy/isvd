////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/util/memory.h
/// @brief   The memory utilities.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_UTIL_MEMORY_H_
#define _ISVD_UTIL_MEMORY_H_

#include <isvd/def.h>
#include <stdlib.h>
#include <string.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#if defined(ISVD_USE_MKL)
  #define isvd_malloc( num, type ) (type*)(mkl_malloc(num * sizeof(type), 64));
#else // ISVD_USE_MKL
  #define isvd_malloc( num, type ) (type*)(malloc(num * sizeof(type)));
#endif // ISVD_USE_MKL

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// @brief  Allocates an array with size @a num.
///
/// @param   num  The number of objects.
///
/// @return       The pointer to the array.
///
//@{
static inline isvd_int_t* isvd_imalloc( const size_t num ) {
  return isvd_malloc(num, isvd_int_t);
}

static inline float* isvd_smalloc( const size_t num ) {
  return isvd_malloc(num, float);
}

static inline double* isvd_dmalloc( const size_t num ) {
  return isvd_malloc(num, double);
}

static inline float complex* isvd_cmalloc( const size_t num ) {
  return isvd_malloc(num, float complex);
}

static inline double complex* isvd_zmalloc( const size_t num ) {
  return isvd_malloc(num, double complex);
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// @brief  Deallocates @a ptr.
/// @param   ptr  The pointer to the array.
///
//@{
static inline void isvd_free( void *ptr ) {
#if defined(ISVD_USE_MKL)
  mkl_free(ptr);
#else // ISVD_USE_MKL
  free(ptr);
#endif // ISVD_USE_MKL
}
//@}

#define isvd_memset0( ptr, num, type ) memset((void*)(ptr), 0, num * sizeof(type));

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// @brief  Sets the memory to zero.
///
/// @param  ptr  The destination pointer to the array.
/// @param  num  The number of objects.
///
//@{
static inline void isvd_imemset0( isvd_int_t *ptr, const size_t num ) {
  isvd_memset0(ptr, num, isvd_int_t);
}

static inline void isvd_smemset0( float *ptr, const size_t num ) {
  isvd_memset0(ptr, num, float);
}

static inline void isvd_dmemset0( double *ptr, const size_t num ) {
  isvd_memset0(ptr, num, double);
}

static inline void isvd_cmemset0( float complex *ptr, const size_t num ) {
  isvd_memset0(ptr, num, float complex);
}

static inline void isvd_zmemset0( double complex *ptr, const size_t num ) {
  isvd_memset0(ptr, num, double complex);
}
//@}

#define isvd_memcpy( dst, src, num, type ) memcpy((void*)(dst), (void*)(src), num * sizeof(type));

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// @brief  Copies the array.
///
/// @param   dst  The destination pointer to the array.
/// @param   src  The source pointer to the array.
/// @param   num  The number of objects.
///
//@{
static inline void isvd_imemcpy( isvd_int_t *dst, isvd_int_t *src, const size_t num ) {
  isvd_memcpy(dst, src, num, isvd_int_t);
}

static inline void isvd_smemcpy( float *dst, float *src, const size_t num ) {
  isvd_memcpy(dst, src, num, float);
}

static inline void isvd_dmemcpy( double *dst, double *src, const size_t num ) {
  isvd_memcpy(dst, src, num, double);
}

static inline void isvd_cmemcpy( float complex *dst, float complex *src, const size_t num ) {
  isvd_memcpy(dst, src, num, float complex);
}

static inline void isvd_zmemcpy( double complex *dst, double complex *src, const size_t num ) {
  isvd_memcpy(dst, src, num, double complex);
}
//@}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_UTIL_MEMORY_H_
