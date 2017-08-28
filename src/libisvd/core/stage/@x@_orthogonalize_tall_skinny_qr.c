////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file    src/libisvd/core/stage/@x@_orthogonalize_tall_skinny_qr.c
/// \brief   The Tall-Skinny QR Orthogonalization (@xname@ precision)
///
/// \author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/core/@x@_stage.h>
#include <isvd/la.h>
#include <isvd/util/memory.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  core_@x@_stage_module
/// Tall-Skinny QR Orthogonalization (@xname@ precision)
///
/// \attention  Not implemented!
///
void isvd_@x@OrthogonalizeTallSkinnyQr(
    const isvd_Param  param,
    const @xtype@    *argv,
    const isvd_int_t  argc,
          @xtype@    *retv,
    const isvd_int_t  retc,
          @xtype@    *yst,
    const isvd_int_t  ldyst
) {

  fprintf(stderr, "Tall-Skinny QR Orthogonalization is not implemented!\n");

  ISVD_UNUSED(param);
  ISVD_UNUSED(argv);
  ISVD_UNUSED(argc);
  ISVD_UNUSED(retv);
  ISVD_UNUSED(retc);
  ISVD_UNUSED(yst);
  ISVD_UNUSED(ldyst);

}
