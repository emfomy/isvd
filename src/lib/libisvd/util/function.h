////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/util/function.h
/// \brief      Some useful functions.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef LIBISVD_UTIL_FUNCTION_H_
#define LIBISVD_UTIL_FUNCTION_H_

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

static inline bool isPowerOf2( isvd_int_t x ) {
  return x && !(x & (x - 1));
}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // LIBISVD_UTIL_FUNCTION_H_
