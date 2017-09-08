////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/util/function.h
/// \brief      Some useful functions.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _LIBISVD_UTIL_FUNCTION_H_
#define _LIBISVD_UTIL_FUNCTION_H_

#include <libisvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#define lenof( Array ) sizeof(Array) / sizeof(Array[0])

static inline isvd_int_t max( isvd_int_t a, isvd_int_t b ) {
  return (a > b) ? a : b;
}

static inline isvd_int_t min( isvd_int_t a, isvd_int_t b ) {
  return (a < b) ? a : b;
}

static inline size_t maxl( size_t a, size_t b ) {
  return (a > b) ? a : b;
}

static inline size_t minl( size_t a, size_t b ) {
  return (a < b) ? a : b;
}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _LIBISVD_UTIL_FUNCTION_H_
