////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/gpu/stage/@x@_postprocess_gpu.h
/// \brief      The GPU Postprocessing utilities (@xname@ precision)
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _LIBISVD_GPU_STAGE_@X@_POSTPROCESS_GPU_H_
#define _LIBISVD_GPU_STAGE_@X@_POSTPROCESS_GPU_H_

#include <isvd/gpu/@x@_stage.h>
#include <libisvd/gpu/def.h>
#include <isvd/la.h>
#include <libisvd/util/memory.h>

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
static void projectBlockCol_gpu(
    const isvd_Param  param,
    const char        ordera,
    const @xtype@    *a,
    const isvd_int_t  lda,
    const @xtype@    *qt,
    const isvd_int_t  ldqt,
          @xtype@    *zt,
    const isvd_int_t  ldzt,
          @xtype@    *s,
          @xtype@    *ut,
    const isvd_int_t  ldut,
    const mpi_int_t   ut_root
) {

  ISVD_UNUSED(s);
  ISVD_UNUSED(ut);
  ISVD_UNUSED(ldut);

  // ====================================================================================================================== //
  // Get parameters

  const isvd_int_t m   = param.nrow;
  const isvd_int_t mb  = param.nrow_each;
  const isvd_int_t Pmb = param.nrow_total;
  const isvd_int_t nj  = param.ncol_proc;
  const isvd_int_t l   = param.dim_sketch;

  // ====================================================================================================================== //
  // Check arguments

  const bool use_ut = (ut_root >= 0);

  switch ( ordera ) {
    case 'C': isvd_assert_ge(lda, m);  break;
    case 'R': isvd_assert_ge(lda, nj); break;
    default:  isvd_assert_fail();
  }
  isvd_assert_eq(ldqt, l);
  isvd_assert_ge(ldzt, l);
  if ( use_ut ) {
    isvd_assert_eq(ldut, l);
  }

  // ====================================================================================================================== //
  // Allocate memory

  @xtype@ *qt_;
  if ( use_ut ) {
    qt_ = ut;
  } else {
    qt_ = isvd_@x@malloc(l * Pmb);
  }
  isvd_int_t ldqt_ = l;

  @xtype@ *da;
  magma_@x@malloc(&da, m * nj);
  isvd_int_t ldda = (ordera == 'C') ? m : nj;

  @xtype@ *dqt_;
  magma_@x@malloc(&dqt_, ldqt_ * m);
  isvd_int_t lddqt_ = ldqt_;

  @xtype@ *dzt;
  magma_@x@malloc(&dzt, ldzt * nj);
  isvd_int_t lddzt = ldzt;

  // ====================================================================================================================== //
  // Rearrange

  MPI_Allgather(qt, mb*ldqt, MPI_@X_TYPE@, qt_, mb*ldqt, MPI_@X_TYPE@, param.mpi_comm);

  // ====================================================================================================================== //
  // Send data

  if ( ordera == 'C' ) {
    magma_@x@setmatrix(m, nj, a, lda, da, ldda);
  } else {
    magma_@x@setmatrix(nj, m, a, lda, da, ldda);
  }
  magma_@x@setmatrix(ldqt_, m, qt_, ldqt_, dqt_, lddqt_);

  // ====================================================================================================================== //
  // Project

  // Z := A' * Q (Z' := Q' * A)
  char transa_ = (ordera == 'C') ? 'N' : 'T';
  magma_@x@gemm(MagmaNoTrans, magma_trans_const(transa_), l, nj, m, 1.0, dqt_, lddqt_, da, ldda, 0.0, dzt, lddzt);

  // ====================================================================================================================== //
  // Retrieve data

  magma_@x@getmatrix(ldzt, nj, dzt, lddzt, zt, ldzt);

  // ====================================================================================================================== //
  // Deallocate memory

  if ( !use_ut ) {
    isvd_free(qt_);
  }

}

static void projectBlockRow_gpu(
    const isvd_Param  param,
    const char        ordera,
    const @xtype@    *a,
    const isvd_int_t  lda,
    const @xtype@    *qt,
    const isvd_int_t  ldqt,
          @xtype@    *zt,
    const isvd_int_t  ldzt,
          @xtype@    *s,
          @xtype@    *vt,
    const isvd_int_t  ldvt,
    const mpi_int_t   vt_root
) {

  ISVD_UNUSED(s);
  ISVD_UNUSED(vt);
  ISVD_UNUSED(ldvt);

  // ====================================================================================================================== //
  // Get parameters

  const isvd_int_t mj  = param.nrow_proc;
  const isvd_int_t n   = param.ncol;
  const isvd_int_t nb  = param.ncol_each;
  const isvd_int_t Pnb = param.ncol_total;
  const isvd_int_t l   = param.dim_sketch;

  // ====================================================================================================================== //
  // Check arguments

  const bool use_vt = (vt_root >= 0);

  switch ( ordera ) {
    case 'C': isvd_assert_ge(lda, mj); break;
    case 'R': isvd_assert_ge(lda, n);  break;
    default:  isvd_assert_fail();
  }
  isvd_assert_ge(ldqt, l);
  isvd_assert_eq(ldzt, l);
  if ( use_vt ) {
    isvd_assert_eq(ldvt, l);
  }

  // ====================================================================================================================== //
  // Allocate memory

  @xtype@ *zt_;
  if ( use_vt ) {
    zt_ = vt;
  } else {
    zt_ = isvd_@x@malloc(l * Pnb);
  }
  isvd_int_t ldzt_ = l;

  @xtype@ *da;
  magma_@x@malloc(&da, mj * n);
  isvd_int_t ldda = (ordera == 'C') ? mj : n;

  @xtype@ *dqt;
  magma_@x@malloc(&dqt, ldqt * mj);
  isvd_int_t lddqt = ldqt;

  @xtype@ *dzt_;
  magma_@x@malloc(&dzt_, ldzt_ * n);
  isvd_int_t lddzt_ = ldzt_;

  // ====================================================================================================================== //
  // Send data

  if ( ordera == 'C' ) {
    magma_@x@setmatrix(mj, n, a, lda, da, ldda);
  } else {
    magma_@x@setmatrix(n, mj, a, lda, da, ldda);
  }
  magma_@x@setmatrix(ldqt, mj, qt, ldqt, dqt, lddqt);

  // ====================================================================================================================== //
  // Project

  // Z := A' * Q (Z' := Q' * A)
  char transa_ = (ordera == 'C') ? 'N' : 'T';
  magma_@x@gemm(MagmaNoTrans, magma_trans_const(transa_), l, n, mj, 1.0, dqt, lddqt, da, ldda, 0.0, dzt_, lddzt_);

  // ====================================================================================================================== //
  // Retrieve data

  magma_@x@getmatrix(ldzt_, n, dzt_, lddzt_, zt_, ldzt_);

  // ====================================================================================================================== //
  // Rearrange

  MPI_Reduce_scatter_block(zt_, zt, nb*ldzt, MPI_@X_TYPE@, MPI_SUM, param.mpi_comm);

  // ====================================================================================================================== //
  // Deallocate memory

  if ( !use_vt ) {
    isvd_free(zt_);
  }

}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

#endif  // _LIBISVD_GPU_STAGE_@X@_POSTPROCESS_GPU_H_
