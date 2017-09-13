////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/nogpu/@x@_stage.c
/// \brief      The iSVD stages with NOGPU support.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/gpu/@x@_stage.h>
#include <libisvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

#define dummy( name ) fprintf(stderr, "'%s' requires GPU support!\n", #name);

// Sketching
void isvd_@x@SketchGaussianProjection_gpu(
    const isvd_Param  param,
    const @xtype@    *argv,
    const isvd_int_t  argc,
          @xtype@    *retv,
    const isvd_int_t  retc,
    const char        dista,
    const char        ordera,
    const @xtype@    *a,
    const isvd_int_t  lda,
          @xtype@    *yst,
    const isvd_int_t  ldyst,
    const isvd_int_t  seed,
    const mpi_int_t   mpi_root
) {
  ISVD_UNUSED(param);
  ISVD_UNUSED(argv);
  ISVD_UNUSED(argc);
  ISVD_UNUSED(retv);
  ISVD_UNUSED(retc);
  ISVD_UNUSED(dista);
  ISVD_UNUSED(ordera);
  ISVD_UNUSED(a);
  ISVD_UNUSED(lda);
  ISVD_UNUSED(yst);
  ISVD_UNUSED(ldyst);
  ISVD_UNUSED(seed);
  ISVD_UNUSED(mpi_root);

  dummy(isvd_@x@SketchGaussianProjection_gpu);
}

// Postprocessing
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

  dummy(isvd_@x@PostprocessTallSkinnyQr_gpu);
}

void isvd_@x@PostprocessGramian_gpu(
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

  dummy(isvd_@x@PostprocessGramian_gpu);
}

void isvd_@x@PostprocessSymmetric_gpu(
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

  dummy(isvd_@x@PostprocessSymmetric_gpu);
}

#endif  // DOXYGEN_SHOULD_SKIP_THIS

#if defined(__cplusplus)
}
#endif  // __cplusplus
