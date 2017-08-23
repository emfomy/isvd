////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    src/libisvd/core/stage_d/isvd_d_postprocess_tall_skinny_qr.c
/// @brief   The Tall-Skinny QR Postprocessing (double precision)
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/core/stage_d.h>
#include <isvd/la.h>
#include <isvd/util/memory.h>

typedef double isvd_val_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  core_stage_d_module
/// Tall-Skinny QR Postprocessing (double precision)
///
/// @attention  Not implemented!
///
void isvd_dPostprocessTallSkinnyQr(
    const isvd_Param param,
    const isvd_val_t *argv,
    const isvd_int_t argc,
          isvd_val_t *retv,
    const isvd_int_t retc,
    const char dista,
    const char ordera,
    const isvd_val_t *a,
    const isvd_int_t lda,
    const isvd_val_t *qt,
    const isvd_int_t ldqt,
          isvd_val_t *s,
          isvd_val_t *ut,
    const isvd_int_t ldut,
          isvd_val_t *vt,
    const isvd_int_t ldvt,
    const mpi_int_t  ut_root,
    const mpi_int_t  vt_root
) {

  fprintf(stderr, "Tall-Skinny QR Postprocessing is not implemented!\n");

  ISVD_UNUSED(param);
  ISVD_UNUSED(argv);
  ISVD_UNUSED(argc);
  ISVD_UNUSED(retv);
  ISVD_UNUSED(retc);
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

}
