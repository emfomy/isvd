////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/la/blas/iamax.c
/// \brief      The BLAS-1 iAmax routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/la/blas/blas1.h>
#include <libisvd/def.h>

@ISVD_LA_BLAS_TYPE_DEFINE@

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

extern INT isamax_(ISVD_UNKNOWN);
extern INT idamax_(ISVD_UNKNOWN);
extern INT icamax_(ISVD_UNKNOWN);
extern INT izamax_(ISVD_UNKNOWN);

#endif  // DOXYGEN_SHOULD_SKIP_THIS

#if defined(__cplusplus)
}
#endif  // __cplusplus

INT isvd_isAmax( const INT n, const REAL4 *x, const INT incx ) { return isamax_(&n, x, &incx); }
INT isvd_idAmax( const INT n, const REAL8 *x, const INT incx ) { return idamax_(&n, x, &incx); }
INT isvd_icAmax( const INT n, const COMP4 *x, const INT incx ) { return icamax_(&n, x, &incx); }
INT isvd_izAmax( const INT n, const COMP8 *x, const INT incx ) { return izamax_(&n, x, &incx); }

REAL4 isvd_sAmax( const INT n, const REAL4 *x, const INT incx ) { INT i = isamax_(&n, x, &incx); return fabsf(x[i]); }
REAL8 isvd_dAmax( const INT n, const REAL8 *x, const INT incx ) { INT i = idamax_(&n, x, &incx); return fabs(x[i]); }
COMP4 isvd_cAmax( const INT n, const COMP4 *x, const INT incx ) { INT i = icamax_(&n, x, &incx); return cabsf(x[i]); }
COMP8 isvd_zAmax( const INT n, const COMP8 *x, const INT incx ) { INT i = izamax_(&n, x, &incx); return cabs(x[i]); }

@ISVD_LA_BLAS_TYPE_UNDEF@
