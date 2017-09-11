////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/la/lapack/lsame.c
/// \brief      The LAPACK Lsame routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/la/lapack/auxiliary.h>
#include <libisvd/la/def.h>

@ISVD_LA_BLAS_TYPE_DEFINE@

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

extern INT lsame_(ISVD_UNKNOWN);

#if !defined(ISVD_USE_MKL)

extern INT lsamen_(ISVD_UNKNOWN);

#endif  // ISVD_USE_MKL

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // DOXYGEN_SHOULD_SKIP_THIS

bool isvd_Lsame(
    const CHAR1 ca, const CHAR1 cb
) {
  return lsame_(&ca, &cb);
}

bool isvd_Lsamen(
    const INT n, const CHAR1 *sa, const CHAR1 *sb
) {
  // return lsamen_(&n, sa, sb);
  for ( INT i = 0; i < n; ++i ) {
    if ( !lsame_(sa+i, sb+i) ) {
      return false;
    }
  }
  return true;
}

@ISVD_LA_BLAS_TYPE_UNDEF@
