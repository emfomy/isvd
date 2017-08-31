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

static inline int max( int a, int b ) {
  return (a > b) ? a : b;
}

static inline int min( int a, int b ) {
  return (a < b) ? a : b;
}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _LIBISVD_UTIL_FUNCTION_H_
