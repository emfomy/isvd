////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/util/memory.h
/// @brief   The memory utilities.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_UTIL_MEMORY_H_
#define _ISVD_UTIL_MEMORY_H_

#include <isvd/def.h>
#include <mkl.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// @brief  Allocates an array with size @a num.
///
/// @param   num  The number of objects.
///
/// @return       The pointer to the array.
///
//@{
static inline void* isvd_malloc( const size_t num ) {
  return mkl_malloc(num, 64);
}

static inline isvd_int_t* isvd_imalloc( const size_t num ) {
  return isvd_malloc(num * sizeof(isvd_int_t));
}

static inline float* isvd_smalloc( const size_t num ) {
  return isvd_malloc(num * sizeof(float));
}

static inline double* isvd_dmalloc( const size_t num ) {
  return isvd_malloc(num * sizeof(double));
}

static inline float complex* isvd_cmalloc( const size_t num ) {
  return isvd_malloc(num * sizeof(float complex));
}

static inline double complex* isvd_zmalloc( const size_t num ) {
  return isvd_malloc(num * sizeof(double complex));
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// @brief  Deallocates @a ptr.
/// @param   ptr  The pointer to the array.
///
//@{
static inline void isvd_free( void *ptr ) {
  mkl_free(ptr);
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// @brief  Sets the memory to zero.
///
/// @param  ptr  The destination pointer to the array.
/// @param  num  The number of objects.
///
static inline void isvd_memset0( void *ptr, const size_t num ) {
  memset(ptr, 0, num);
}

static inline void isvd_imemset0( isvd_int_t *ptr, const size_t num ) {
  memset(ptr, 0, num * sizeof(isvd_int_t));
}

static inline void isvd_smemset0( float *ptr, const size_t num ) {
  memset(ptr, 0, num * sizeof(float));
}

static inline void isvd_dmemset0( double *ptr, const size_t num ) {
  memset(ptr, 0, num * sizeof(double));
}

static inline void isvd_cmemset0( float complex *ptr, const size_t num ) {
  memset(ptr, 0, num * sizeof(float complex));
}

static inline void isvd_zmemset0( double complex *ptr, const size_t num ) {
  memset(ptr, 0, num * sizeof(double complex));
}
//@}

#endif  // _ISVD_UTIL_MEMORY_H_
