////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/la/vsl/vsl.c
/// \brief      The VSL service routines.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#define _POSIX_C_SOURCE 1
#include <stdlib.h>
#include <libisvd/la/vsl/vsl.h>
#include <libisvd/util/memory.h>

#if !defined(ISVD_USE_MKL)

void isvd_vslNewStream(
    isvd_VSLStreamStatePtr *streamp, const isvd_int_t seed
) {
  *streamp = isvd_imalloc(4);
  (*streamp)[0] = (seed & 0xff) + 1;
  (*streamp)[1] = ((seed >>  8) & 0xff);
  (*streamp)[2] = ((seed >> 16) & 0xff);
  (*streamp)[3] = ((seed >> 24) & 0xff);
}

void isvd_vslDeleteStream(
    isvd_VSLStreamStatePtr *streamp
) {
  isvd_free(*streamp);
}

void isvd_vslSkipAheadStream(
    isvd_VSLStreamStatePtr stream, const isvd_int_t nskip
) {
  unsigned int seed = nskip;
  stream[0] ^= rand_r(&seed) % 2048 + 1;
  stream[1] ^= rand_r(&seed) % 4096;
  stream[2] ^= rand_r(&seed) % 4096;
  stream[3] ^= rand_r(&seed) % 4096;
}
#endif  // ISVD_USE_MKL
