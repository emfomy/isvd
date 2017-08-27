////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file    include/c/isvd/la/vsl/vsl.h
/// \brief   The VSL definitions.
///
/// \author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_LA_VSL_VSL_H_
#define _ISVD_LA_VSL_VSL_H_

#include <isvd/def.h>
#include <stdlib.h>
#include <isvd/la/lapack/larnv.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#define CHAR1 char
#define INT   isvd_int_t
#define REAL4 float
#define REAL8 double
#define COMP4 complex float
#define COMP8 complex double

#if defined(ISVD_USE_MKL)
typedef VSLStreamStatePtr isvd_VSLStreamStatePtr;
#else  // ISVD_USE_MKL
typedef isvd_int_t* isvd_VSLStreamStatePtr;
#endif  // ISVD_USE_MKL

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  la_vsl_module
/// Creates and initializes a random stream.
//\{
#if defined(ISVD_USE_MKL)
static inline void isvd_vslNewStream(
    isvd_VSLStreamStatePtr *streamp, const INT seed
) { isvd_assert_pass(vslNewStream(streamp, VSL_BRNG_SFMT19937, seed)); }
#else  // ISVD_USE_MKL
static inline void isvd_vslNewStream(
    isvd_VSLStreamStatePtr *streamp, const INT seed
) {
  *streamp = isvd_imalloc(4);
  (*streamp)[0] = (seed & 0xff) + 1;
  (*streamp)[1] = ((seed >>  8) & 0xff);
  (*streamp)[2] = ((seed >> 16) & 0xff);
  (*streamp)[3] = ((seed >> 24) & 0xff);
}
#endif  // ISVD_USE_MKL
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  la_vsl_module
/// Creates and initializes a random stream.
//\{
#if defined(ISVD_USE_MKL)
static inline void isvd_vslDeleteStream(
    isvd_VSLStreamStatePtr *streamp
) { isvd_assert_pass(vslDeleteStream(streamp)); }
#else  // ISVD_USE_MKL
static inline void isvd_vslDeleteStream(
    isvd_VSLStreamStatePtr *streamp
) {
  isvd_free(*streamp); }
#endif  // ISVD_USE_MKL
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  la_vsl_module
/// Creates and initializes a random stream.
//\{
#if defined(ISVD_USE_MKL)
static inline void isvd_vslSkipAheadStream(
    isvd_VSLStreamStatePtr stream, const INT nskip
) { isvd_assert_pass(vslSkipAheadStream(stream, nskip)); }
#else  // ISVD_USE_MKL
static inline void isvd_vslSkipAheadStream(
    isvd_VSLStreamStatePtr stream, const INT nskip
) {
  unsigned int seed = nskip;
  stream[0] ^= rand_r(&seed) % 2048 + 1;
  stream[1] ^= rand_r(&seed) % 4096;
  stream[2] ^= rand_r(&seed) % 4096;
  stream[3] ^= rand_r(&seed) % 4096;
}
#endif  // ISVD_USE_MKL
//\}

#undef CHAR1
#undef INT
#undef REAL4
#undef REAL8
#undef COMP4
#undef COMP8

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_LA_VSL_VSL_H_
