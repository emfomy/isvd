////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/util/memory.h
/// @brief   The memory utilities.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_UTIL_MEMORY_H_
#define _ISVD_UTIL_MEMORY_H_

#include <isvd/def.h>
#include <mkl.h>

static inline void* isvd_malloc( const size_t num ) {
  return mkl_malloc(num, 64);
}

static inline index_t* isvd_imalloc( const size_t num ) {
  return isvd_malloc(num * sizeof(index_t));
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

static inline void isvd_free( void *ptr ) {
  mkl_free(ptr);
}

#endif  // _ISVD_UTIL_MEMORY_H_
