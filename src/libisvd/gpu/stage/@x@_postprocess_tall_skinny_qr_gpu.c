////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/gpu/stage/@x@_postprocess_tall_skinny_qr_gpu.c
/// \brief      The GPU Tall-Skinny QR Postprocessing (@xname@ precision)
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/gpu/@x@_stage.h>
#include <libisvd/gpu/def.h>
#include <isvd/la.h>
// #include <libisvd/gpu/stage/@x@_postprocess_gpu.h>
#include <libisvd/util/memory.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_gpu_@x@_stage_module
/// GPU Tall-Skinny QR Postprocessing (@xname@ precision)
///
/// \attention  Not implemented!
///
void isvd_@x@PostprocessTallSkinnyQr_gpu(
    const isvd_Param  param,
    const @xtype@    *argv,
    const isvd_int_t  argc,
          @xtype@    *retv,
    const isvd_int_t  retc,
    const char        dista,
    const char        ordera,
    const @xtype@    *a,
    const isvd_int_t  lda,
    const @xtype@    *qt,
    const isvd_int_t  ldqt,
          @xtype@    *s,
          @xtype@    *ut,
    const isvd_int_t  ldut,
          @xtype@    *vt,
    const isvd_int_t  ldvt,
    const mpi_int_t   ut_root,
    const mpi_int_t   vt_root
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
