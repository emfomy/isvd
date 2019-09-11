////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/gpu/stage/@x@_postprocess_gpu.h
/// \brief      The GPU Postprocessing utilities (@xname@ precision).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef LIBISVD_GPU_STAGE_@X@_POSTPROCESS_GPU_H_
#define LIBISVD_GPU_STAGE_@X@_POSTPROCESS_GPU_H_

#if defined(LIBISVD_CORE_STAGE_@X@_POSTPROCESS_H_)
#error LIBISVD_CORE_STAGE_@X@_POSTPROCESS_H_ should not be defined!
#endif  // LIBISVD_CORE_STAGE_@X@_POSTPROCESS_H_

#define LIBISVD_CORE_STAGE_@X@_POSTPROCESS_H_

#include <isvd/gpu/@x@_stage.h>
#include <libisvd/gpu/def.h>
#include <isvd/gpu/env.h>
#include <isvd/la.h>
#include <libisvd/util/function.h>
#include <isvd/util/memory.h>
#include <isvd/util/mpi.h>

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
static void projectBlockCol(
    const isvd_Param    param,
    const char          ordera,
    const @xtype_____@ *a,
    const isvd_int_t    lda,
    const @xtype_____@ *qt,
    const isvd_int_t    ldqt,
          @xtype_____@ *zt,
    const isvd_int_t    ldzt,
          @xtype_____@ *s,
          @xtype_____@ *ut,
    const isvd_int_t    ldut,
    const mpi_int_t     ut_root
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
  // Check memory

  size_t free_byte, total_byte;
  cudaMemGetInfo(&free_byte, &total_byte);
  if ( isvd_gpu_memory_limit > 0 ) free_byte = minl(free_byte, isvd_gpu_memory_limit);
  size_t melem = free_byte / sizeof(@xtype_____@);
  size_t nelem_used = m * l;
  isvd_int_t n_gpu = (melem - nelem_used) / (m + l);
  if ( n_gpu > (isvd_int_t)isvd_kBlockSizeGpu ) n_gpu = (n_gpu / isvd_kBlockSizeGpu) * isvd_kBlockSizeGpu;
  n_gpu = min(n_gpu, nj);
  if ( n_gpu <= 0 ) {
    fprintf(stderr, "No enough GPU memory. (Request at least %" PRId64 " bytes. Only %" PRId64 " bytes free.",
            nelem_used * sizeof(@xtype_____@), melem * sizeof(@xtype_____@));
    isvd_assert_fail();
  }

  // ====================================================================================================================== //
  // Allocate memory

  @xtype_____@ *qt_;
  if ( use_ut ) {
    qt_ = ut;
  } else {
    qt_ = isvd_@x@Malloc(l * Pmb);
  }
  isvd_int_t ldqt_ = l;

  @xtype_____@ *a_gpu;
  magma_@x@malloc(&a_gpu, m * n_gpu);
  isvd_int_t lda_gpu = (ordera == 'C') ? m : n_gpu;

  @xtype_____@ *qt_gpu;
  magma_@x@malloc(&qt_gpu, l * m);
  isvd_int_t ldqt_gpu = l;

  @xtype_____@ *zt_gpu;
  magma_@x@malloc(&zt_gpu, l * n_gpu);
  isvd_int_t ldzt_gpu = l;

  // ====================================================================================================================== //
  // Rearrange

  isvd_assert_pass(MPI_Allgather(qt, mb*ldqt, MPI_@XTYPE@, qt_, mb*ldqt, MPI_@XTYPE@, param.mpi_comm));

  // ====================================================================================================================== //
  // Send data

  magma_@x@setmatrix(l, m, qt_, ldqt_, qt_gpu, ldqt_gpu);

  // ====================================================================================================================== //
  // Project

  char transa_ = (ordera == 'C') ? 'N' : 'T';
  isvd_int_t idx;

  for ( idx = 0; idx < nj; idx += n_gpu ) {
    const @xtype_____@ *a_tmp = (ordera == 'C') ? (a + lda*idx) : (a+idx);
          @xtype_____@ *zt_tmp = zt + ldzt*idx;
    const isvd_int_t n_tmp = min(n_gpu, nj-idx);

    // Send A
    if ( ordera == 'C' ) {
      magma_@x@setmatrix(m, n_tmp, a_tmp, lda, a_gpu, lda_gpu);
    } else {
      magma_@x@setmatrix(n_tmp, m, a_tmp, lda, a_gpu, lda_gpu);
    }

    // Z := A' * Q (Z' := Q' * A)
    magma_@x@gemm(MagmaNoTrans, magma_trans_const(transa_), l, n_tmp, m,
                  1.0, qt_gpu, ldqt_gpu, a_gpu, lda_gpu, 0.0, zt_gpu, ldzt_gpu);

    // Retrieve Z
    magma_@x@getmatrix(l, n_tmp, zt_gpu, ldzt_gpu, zt_tmp, ldzt);
  }

  // ====================================================================================================================== //
  // Deallocate memory

  if ( !use_ut ) {
    isvd_Free(qt_);
  }

  magma_free(a_gpu);
  magma_free(qt_gpu);
  magma_free(zt_gpu);

}

static void projectBlockRow(
    const isvd_Param    param,
    const char          ordera,
    const @xtype_____@ *a,
    const isvd_int_t    lda,
    const @xtype_____@ *qt,
    const isvd_int_t    ldqt,
          @xtype_____@ *zt,
    const isvd_int_t    ldzt,
          @xtype_____@ *s,
          @xtype_____@ *vt,
    const isvd_int_t    ldvt,
    const mpi_int_t     vt_root
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
  // Check memory

  size_t free_byte, total_byte;
  cudaMemGetInfo(&free_byte, &total_byte);
  size_t melem = free_byte / sizeof(@xtype_____@);
  size_t nelem_used = mj * l;
  isvd_int_t n_gpu = (melem - nelem_used) / (mj + l);
  if ( n_gpu > (isvd_int_t)isvd_kBlockSizeGpu ) n_gpu = (n_gpu / isvd_kBlockSizeGpu) * isvd_kBlockSizeGpu;
  n_gpu = min(n_gpu, n);
  if ( n_gpu <= 0 ) {
    fprintf(stderr, "No enough GPU memory. (Request at least %" PRId64 " bytes. Only %" PRId64 " bytes free.",
            nelem_used * sizeof(@xtype_____@), melem * sizeof(@xtype_____@));
    isvd_assert_fail();
  }

  // ====================================================================================================================== //
  // Allocate memory

  @xtype_____@ *zt_;
  if ( use_vt ) {
    zt_ = vt;
  } else {
    zt_ = isvd_@x@Malloc(l * Pnb);
  }
  isvd_int_t ldzt_ = l;

  @xtype_____@ *a_gpu;
  magma_@x@malloc(&a_gpu, mj * n_gpu);
  isvd_int_t lda_gpu = (ordera == 'C') ? mj : n_gpu;

  @xtype_____@ *qt_gpu;
  magma_@x@malloc(&qt_gpu, l * mj);
  isvd_int_t ldqt_gpu = l;

  @xtype_____@ *zt_gpu;
  magma_@x@malloc(&zt_gpu, l * n_gpu);
  isvd_int_t ldzt_gpu = l;

  // ====================================================================================================================== //
  // Send data

  magma_@x@setmatrix(l, mj, qt, ldqt, qt_gpu, ldqt_gpu);

  // ====================================================================================================================== //
  // Project

  char transa_ = (ordera == 'C') ? 'N' : 'T';
  isvd_int_t idx;

  for ( idx = 0; idx < n; idx += n_gpu ) {
    const @xtype_____@ *a_tmp = (ordera == 'C') ? (a + lda*idx) : (a+idx);
          @xtype_____@ *zt_tmp = zt_ + ldzt*idx;
    const isvd_int_t n_tmp = min(n_gpu, n-idx);

    // Send A
    if ( ordera == 'C' ) {
      magma_@x@setmatrix(mj, n_tmp, a_tmp, lda, a_gpu, lda_gpu);
    } else {
      magma_@x@setmatrix(n_tmp, mj, a_tmp, lda, a_gpu, lda_gpu);
    }

    // Z := A' * Q (Z' := Q' * A)
    magma_@x@gemm(MagmaNoTrans, magma_trans_const(transa_), l, n_tmp, mj,
                  1.0, qt_gpu, ldqt_gpu, a_gpu, lda_gpu, 0.0, zt_gpu, ldzt_gpu);

    // Retrieve Z
    magma_@x@getmatrix(l, n_tmp, zt_gpu, ldzt_gpu, zt_tmp, ldzt_);
  }

  // ====================================================================================================================== //
  // Rearrange

  isvd_assert_pass(MPI_Reduce_scatter_block(zt_, zt, nb*ldzt, MPI_@XTYPE@, MPI_SUM, param.mpi_comm));

  // ====================================================================================================================== //
  // Deallocate memory

  if ( !use_vt ) {
    isvd_Free(zt_);
  }

  magma_free(a_gpu);
  magma_free(qt_gpu);
  magma_free(zt_gpu);

}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

#endif  // LIBISVD_GPU_STAGE_@X@_POSTPROCESS_GPU_H_
