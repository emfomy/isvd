////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/util/arg.h
/// \brief      The argument utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _LIBISVD_UTIL_ARG_H_
#define _LIBISVD_UTIL_ARG_H_

#include <libisvd/def.h>
#include <stdio.h>
#include <string.h>
#include <isvd/la.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

static inline isvd_int_t isvd_arg2char(
    const char *name,
    const char arg,
    const char *opts,
    const char *rets
) {
  if ( rets == nullptr ) {
    rets = opts;
  }

  const size_t nopts = strlen(opts);

  for ( size_t i = 0; i < nopts; ++i ) {
    if ( isvd_Lsame(arg, opts[i]) ) {
      return rets[i];
    }
  }

  fprintf(stderr, "%s ('%c') must be one of the following characters: ", name, arg);
  if ( nopts > 0 ) {
    fprintf(stderr, "'%c'", opts[0]);
  }
  for ( size_t i = 1; i < nopts; ++i ) {
    fprintf(stderr, ", '%c'", opts[i]);
  }
  fprintf(stderr, ".\n");
  return 0;
}

#define isvd_char2( str0, str1 ) (str0 + (str1 << 8))

static inline const char* isvd_arg2str(
    const char *name,
    const char *arg,
    const char *opts[],
    const char *rets[],
    const size_t nopts
) {
  if ( rets == nullptr ) {
    rets = opts;
  }

  const size_t larg = strlen(arg);

  for ( size_t i = 0; i < nopts; ++i ) {
    if ( larg == strlen(opts[i]) && isvd_Lsamen(larg, arg, opts[i]) ) {
      return opts[i];
    }
  }

  fprintf(stderr, "%s ('%s') must be one of the following strings: ", name, arg);
  if ( nopts > 0 ) {
    fprintf(stderr, "\"%.2s\"", opts[0]);
  }
  for ( size_t i = 1; i < nopts; ++i ) {
    fprintf(stderr, ", \"%.2s\"", opts[i]);
  }
  fprintf(stderr, ".\n");
  return 0;
}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _LIBISVD_UTIL_ARG_H_
