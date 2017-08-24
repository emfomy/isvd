////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/util/function.h
/// @brief   Some useful functions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_UTIL_FUNCTION_H_
#define _ISVD_UTIL_FUNCTION_H_

#include <isvd/def.h>
#include <stdlib.h>

static inline int max( int a, int b ) {
  return (a > b) ? a : b;
}

static inline int min( int a, int b ) {
  return (a < b) ? a : b;
}

#endif  // _ISVD_UTIL_FUNCTION_H_
