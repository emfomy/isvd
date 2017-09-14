////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/util/io.c
/// \brief      The I/O utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/util/io.h>
#include <libisvd/def.h>

@ISVD_TYPE_MACRO_DEFINE@

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_util_io_module
/// \brief  Get a variable from stream.
///
/// \param  stream  Pointer to a FILE object that identifies an input stream.
/// \param  varp    Pointer to the variable.
///
//\{
void isvd_ifget( FILE *stream, INT *varp ) {
#if !defined(ISVD_USE_ILP64)
  INT info = fscanf(stream, "%" PRId32, varp);
#else  // ISVD_USE_ILP64
  INT info = fscanf(stream, "%" PRId64, varp);
#endif  // ISVD_USE_ILP64
  ISVD_UNUSED(info);
  isvd_assert_eq(info, 1);
}

void isvd_sfget( FILE *stream, REAL4 *varp ) {
  INT info = fscanf(stream, "%f",  varp);
  ISVD_UNUSED(info);
  isvd_assert_eq(info, 1);
}

void isvd_dfget( FILE *stream, REAL8 *varp ) {
  INT info = fscanf(stream, "%lf", varp);
  ISVD_UNUSED(info);
  isvd_assert_eq(info, 1);
}
//\}

@ISVD_TYPE_MACRO_UNDEF@
