////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/la/vsl/vsl.h
/// \brief      The VSL definitions.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _LIBISVD_LA_VSL_VSL_H_
#define _LIBISVD_LA_VSL_VSL_H_

#include <libisvd/def.h>

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
typedef void* isvd_VSLStreamStatePtr;
#else  // ISVD_USE_MKL
typedef isvd_int_t* isvd_VSLStreamStatePtr;
#endif  // ISVD_USE_MKL

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  src_la_vsl_module
/// Creates and initializes a random stream.
//\{
#if defined(ISVD_USE_MKL)
static inline void isvd_vslNewStream(
    isvd_VSLStreamStatePtr *streamp, const INT seed
) { isvd_assert_pass(vslNewStream(streamp, VSL_BRNG_SFMT19937, seed)); }
#else  // ISVD_USE_MKL
void isvd_vslNewStream(
    isvd_VSLStreamStatePtr *streamp, const INT seed
);
#endif  // ISVD_USE_MKL
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  src_la_vsl_module
/// Creates and initializes a random stream.
//\{
#if defined(ISVD_USE_MKL)
static inline void isvd_vslDeleteStream(
    isvd_VSLStreamStatePtr *streamp
) { isvd_assert_pass(vslDeleteStream(streamp)); }
#else  // ISVD_USE_MKL
void isvd_vslDeleteStream(
    isvd_VSLStreamStatePtr *streamp
);
#endif  // ISVD_USE_MKL
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  src_la_vsl_module
/// Creates and initializes a random stream.
//\{
#if defined(ISVD_USE_MKL)
static inline void isvd_vslSkipAheadStream(
    isvd_VSLStreamStatePtr stream, const INT nskip
) { isvd_assert_pass(vslSkipAheadStream(stream, nskip)); }
#else  // ISVD_USE_MKL
void isvd_vslSkipAheadStream(
    isvd_VSLStreamStatePtr stream, const INT nskip
);
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

#endif  // _LIBISVD_LA_VSL_VSL_H_
