////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    src/libisvd/core/stage_d/d_orthogonalize_tall_skinny_qr.c
/// @brief   The Tall-Skinny QR Orthogonalization (double precision)
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/core/stage_d.h>
#include <isvd/la.h>
#include <isvd/util/memory.h>

typedef double isvd_val_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  core_stage_d_module
/// Tall-Skinny QR Orthogonalization (double precision)
///
/// @attention  Not implemented!
///
void isvd_dOrthogonalizeTallSkinnyQr(
    const isvd_Param param,
    const isvd_val_t *argv,
    const isvd_int_t argc,
          isvd_val_t *retv,
    const isvd_int_t retc,
          isvd_val_t *yst,
    const isvd_int_t ldyst
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
