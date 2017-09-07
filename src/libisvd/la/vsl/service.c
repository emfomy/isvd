////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/la/vsl/service.c
/// \brief      The VSL service routines.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///


#if !defined(ISVD_USE_MKL)
#define _POSIX_SOURCE
#endif  // ISVD_USE_MKL

#include <isvd/la/vsl/service.h>
#include <libisvd/def.h>

@ISVD_LA_BLAS_TYPE_DEFINE@

#if defined(ISVD_USE_MKL)

void isvd_vslNewStream( isvd_VSLStreamStatePtr *streamp, const INT seed ) {
  isvd_assert_pass(vslNewStream((VSLStreamStatePtr*)streamp, VSL_BRNG_SFMT19937, seed));
}

void isvd_vslDeleteStream( isvd_VSLStreamStatePtr *streamp ) {
  isvd_assert_pass(vslDeleteStream((VSLStreamStatePtr*)streamp));
}

void isvd_vslSkipAheadStream( isvd_VSLStreamStatePtr stream, const INT nskip ) {
  isvd_assert_pass(vslSkipAheadStream((VSLStreamStatePtr)stream, nskip));
}

#else  // ISVD_USE_MKL

#include <stdlib.h>
#include <isvd/util/memory.h>

void isvd_vslNewStream( isvd_VSLStreamStatePtr *streamp, const INT seed ) {
  *streamp = isvd_imalloc(4);
  (*streamp)[0] = (seed & 0xff) + 1;
  (*streamp)[1] = ((seed >>  8) & 0xff);
  (*streamp)[2] = ((seed >> 16) & 0xff);
  (*streamp)[3] = ((seed >> 24) & 0xff);
}

void isvd_vslDeleteStream( isvd_VSLStreamStatePtr *streamp ) {
  isvd_free(*streamp);
}

void isvd_vslSkipAheadStream( isvd_VSLStreamStatePtr stream, const INT nskip ) {
  unsigned int seed = nskip;
  stream[0] ^= rand_r(&seed) % 2048 + 1;
  stream[1] ^= rand_r(&seed) % 4096;
  stream[2] ^= rand_r(&seed) % 4096;
  stream[3] ^= rand_r(&seed) % 4096;
}

#endif  // ISVD_USE_MKL

@ISVD_LA_BLAS_TYPE_UNDEF@
