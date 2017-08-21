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
#include <stdarg.h>
#include <string.h>

static inline isvd_int_t isvd_arg2char(
    const char *name,
    const char arg,
    const char *opts
) {
  for ( size_t i = 0; i < strlen(opts); ++i ) {
    if ( lsame(&arg, opts+i, 1, 1) ) {
      return opts[i];
    }
  }
  fprintf(stderr, "%s ('%c') must be one of the following characters: ", name, arg);
  if ( strlen(opts) > 0 ) {
    fprintf(stderr, "'%c'", opts[0]);
  }
  for ( size_t i = 1; i < strlen(opts); ++i ) {
    fprintf(stderr, ", '%c'", opts[i]);
  }
  fprintf(stderr, ".\n");
  return 0;
}

#define isvd_char2( str0, str1 ) (str0 + (str1 << 8))

static inline int16_t isvd_arg2char2(
    const char *name,
    const char *arg,
    const char *opts
) {
  for ( size_t i = 0; i < strlen(opts); i += 2 ) {
    if ( lsame(arg, opts+i, 1, 1) && lsame(arg+1, opts+i+1, 1, 1) ) {
      return isvd_char2(opts[i], opts[i+1]);
    }
  }
  fprintf(stderr, "%s ('%s') must be one of the following strings: ", name, arg);
  if ( strlen(opts) > 0 ) {
    fprintf(stderr, "\"%.2s\"", opts);
  }
  for ( size_t i = 2; i < strlen(opts); i += 2 ) {
    fprintf(stderr, ", \"%.2s\"", opts+i);
  }
  fprintf(stderr, ".\n");
  return 0;
}

#endif  // _ISVD_CORE_DEF_H_
