////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/lapack/lsame.c
/// \brief      The LAPACK Lsame routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/la/lapack/auxiliary.h>
#include <libisvd/la/def.h>

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

extern isvd_int_t lsame_(ISVD_UNKNOWN);

#if !defined(ISVD_USE_MKL)

extern isvd_int_t lsamen_(ISVD_UNKNOWN);

#endif  // ISVD_USE_MKL

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // DOXYGEN_SHOULD_SKIP_THIS

bool isvd_Lsame(
    const char ca, const char cb
) {
  return lsame_(&ca, &cb);
}

bool isvd_Lsamen(
    const isvd_int_t n, const char *sa, const char *sb
) {
  // return lsamen_(&n, sa, sb);
  for ( isvd_int_t i = 0; i < n; ++i ) {
    if ( !lsame_(sa+i, sb+i) ) {
      return false;
    }
  }
  return true;
}
