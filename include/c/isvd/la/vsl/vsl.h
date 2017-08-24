////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/la/vsl/vsl.h
/// @brief   The VSL definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_LA_VSL_VSL_H_
#define _ISVD_LA_VSL_VSL_H_

#include <isvd/def.h>
#include <stdlib.h>
#include <isvd/la/lapack/larnv.h>

#define CHAR1 char
#define INT   isvd_int_t
#define REAL4 float
#define REAL8 double
#define COMP4 float complex
#define COMP8 double complex

#if defined(ISVD_USE_MKL)
typedef VSLStreamStatePtr isvd_VSLStreamStatePtr;
#else  // ISVD_USE_MKL
typedef isvd_int_t[4] isvd_VSLStreamStatePtr;
#endif  // ISVD_USE_MKL

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_vsl_module
/// Creates and initializes a random stream.
//@{
#if defined(ISVD_USE_MKL)
static inline void isvd_vslNewStream(
    isvd_VSLStreamStatePtr *stream, const INT seed
) { isvd_assert_pass(vslNewStream(stream, VSL_BRNG_SFMT19937, seed)); }
#else  // ISVD_USE_MKL
static inline void isvd_vslNewStream(
    isvd_VSLStreamStatePtr *stream, const INT seed
) {
  *stream[0] = (seed % 256) + 1;
  *stream[1] = ((seed >>  8) % 256);
  *stream[2] = ((seed >> 16) % 256);
  *stream[3] = ((seed >> 24) % 256);
}
#endif  // ISVD_USE_MKL
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_vsl_module
/// Creates and initializes a random stream.
//@{
#if defined(ISVD_USE_MKL)
static inline void isvd_vslDeleteStream(
    isvd_VSLStreamStatePtr *stream
) { isvd_assert_pass(vslDeleteStream(stream)); }
#else  // ISVD_USE_MKL
static inline void isvd_vslDeleteStream(
    isvd_VSLStreamStatePtr *stream
) { ISVD_UNUSED(stream); }
#endif  // ISVD_USE_MKL
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_vsl_module
/// Creates and initializes a random stream.
//@{
#if defined(ISVD_USE_MKL)
static inline void isvd_vslSkipAheadStream(
    isvd_VSLStreamStatePtr stream, const INT nskip
) { isvd_assert_pass(vslSkipAheadStream(stream, nskip)); }
#else  // ISVD_USE_MKL
static inline void isvd_vslSkipAheadStream(
    isvd_VSLStreamStatePtr stream, const INT nskip
) {
  INT seed = nskip;
  stream[0] ^= rand_r(&seed) % 2048 + 1;
  stream[1] ^= rand_r(&seed) % 4096;
  stream[2] ^= rand_r(&seed) % 4096;
  stream[3] ^= rand_r(&seed) % 4096;
}
#endif  // ISVD_USE_MKL
//@}

#undef CHAR1
#undef INT
#undef REAL4
#undef REAL8
#undef COMP4
#undef COMP8

#endif  // _ISVD_LA_VSL_VSL_H_
