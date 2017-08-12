////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/core/def.h
/// @brief   The core definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_CORE_DEF_H_
#define _ISVD_CORE_DEF_H_

#include <isvd/def.h>
#include <stdio.h>
#include <string.h>
#include <mkl.h>

inline isvd_int_t isvd_arg2int(
    const char *name,
    const char arg,
    const char *opts
) {
  for ( size_t i = 0; i < strlen(opts); ++i ) {
    if ( lsame(&arg, opts+i, 1, 1) ) {
      return i;
    }
  }
  fprintf(stderr, "%s (='%c') must be one of the following characters \"%s\".\n", name, arg, opts);
  return -1;
}

inline char isvd_arg2char(
    const char *name,
    const char arg,
    const char *opts,
    const char *chars
) {
  for ( size_t i = 0; i < strlen(opts); ++i ) {
    if ( lsame(&arg, opts+i, 1, 1) ) {
      return chars[i];
    }
  }
  fprintf(stderr, "%s (='%c') must be one of the following characters \"%s\".\n", name, arg, opts);
  return '\0';
}

#endif  // _ISVD_CORE_DEF_H_
