#include <mcnla/core/la/raw/plugin/blas_plugin_begin.h>

#define REAL4_SELECT2(name) CPP_INT (*arg)( const FORTRAN_REAL4, const FORTRAN_REAL4 )
#define REAL8_SELECT2(name) CPP_INT (*arg)( const FORTRAN_REAL8, const FORTRAN_REAL8 )
#define COMP4_SELECT1(name) CPP_INT (*arg)( const FORTRAN_COMP4 )
#define COMP8_SELECT1(name) CPP_INT (*arg)( const FORTRAN_COMP8 )
