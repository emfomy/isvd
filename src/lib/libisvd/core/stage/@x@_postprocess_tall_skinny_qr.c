////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/core/stage/@x@_postprocess_tall_skinny_qr.c
/// \brief      The Tall-Skinny QR Postprocessing (@xname@ precision).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/core/@x@_stage.h>
#include <libisvd/def.h>
#include <isvd/la.h>
#include <libisvd/core/stage/@x@_postprocess.h>
#include <libisvd/util/arg.h>
#include <isvd/util/memory.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_@x@_stage_module
/// \brief  Tall-Skinny QR Postprocessing (@xname@ precision).
///
/// \attention  Not implemented!
///
/// \note  If \b argc < 0, then a default argument query is assumed;
///        the routine only returns the first \b retc default arguments in \b retv.
///
/// \see isvd_Param, \ref tutorial_core_notation
///
void isvd_@x@PostprocessTallSkinnyQr(
    const isvd_Param    param,
    const @xtype_____@ *argv,
    const isvd_int_t    argc,
          @xtype_____@ *retv,
    const isvd_int_t    retc,
    const char          dista,
    const char          ordera,
    const @xtype_____@ *a,
    const isvd_int_t    lda,
    const @xtype_____@ *qt,
    const isvd_int_t    ldqt,
          @xtype_____@ *s,
          @xtype_____@ *ut,
    const isvd_int_t    ldut,
          @xtype_____@ *vt,
    const isvd_int_t    ldvt,
    const mpi_int_t     ut_root,
    const mpi_int_t     vt_root
) {

  fprintf(stderr, "Tall-Skinny QR Postprocessing is not implemented!\n");

  if ( argc > 0 ) { isvd_assert_ne(argv, nullptr); }
  if ( retc > 0 ) { isvd_assert_ne(retv, nullptr); }
  if ( argc < 0 ) return;

  ISVD_UNUSED(param);
  ISVD_UNUSED(dista);
  ISVD_UNUSED(ordera);
  ISVD_UNUSED(a);
  ISVD_UNUSED(lda);
  ISVD_UNUSED(qt);
  ISVD_UNUSED(ldqt);
  ISVD_UNUSED(s);
  ISVD_UNUSED(ut);
  ISVD_UNUSED(ldut);
  ISVD_UNUSED(vt);
  ISVD_UNUSED(ldvt);
  ISVD_UNUSED(ut_root);
  ISVD_UNUSED(vt_root);
  ISVD_UNUSED(projectBlockCol);
  ISVD_UNUSED(projectBlockRow);

}
