////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/core/stage/@x@_postprocess.h
/// \brief      The Postprocessing utilities (@xname@ precision).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef LIBISVD_CORE_STAGE_@X@_POSTPROCESS_H_
#define LIBISVD_CORE_STAGE_@X@_POSTPROCESS_H_

#include <libisvd/def.h>
#include <isvd/la.h>
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
  // Allocate memory

  // matrix Q'
  @xtype_____@ *qt_;
  if ( use_ut ) {
    qt_ = ut;
  } else {
    qt_ = isvd_@x@Malloc(l * Pmb);
  }
  isvd_int_t ldqt_ = l;

  // ====================================================================================================================== //
  // Rearrange

  isvd_assert_pass(MPI_Allgather(qt, mb*ldqt, MPI_@XTYPE@, qt_, mb*ldqt, MPI_@XTYPE@, param.mpi_comm));

  // ====================================================================================================================== //
  // Project

  // Z := A' * Q (Z' := Q' * A)
  char transa_ = (ordera == 'C') ? 'N' : 'T';
  isvd_@x@Gemm('N', transa_, l, nj, m, 1.0, qt_, ldqt_, a, lda, 0.0, zt, ldzt);

  // ====================================================================================================================== //
  // Deallocate memory

  if ( !use_ut ) {
    isvd_Free(qt_);
  }

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
  // Allocate memory

  // matrix Z'
  @xtype_____@ *zt_;
  if ( use_vt ) {
    zt_ = vt;
  } else {
    zt_ = isvd_@x@Malloc(l * Pnb);
  }
  isvd_int_t ldzt_ = l;

  // ====================================================================================================================== //
  // Project

  // Z := A' * Q (Z' := Q' * A)
  char transa_ = (ordera == 'C') ? 'N' : 'T';
  isvd_@x@Gemm('N', transa_, l, n, mj, 1.0, qt, ldqt, a, lda, 0.0, zt_, ldzt_);

  // ====================================================================================================================== //
  // Rearrange

  isvd_assert_pass(MPI_Reduce_scatter_block(zt_, zt, nb*ldzt, MPI_@XTYPE@, MPI_SUM, param.mpi_comm));

  // ====================================================================================================================== //
  // Deallocate memory

  if ( !use_vt ) {
    isvd_Free(zt_);
  }

}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

#endif  // LIBISVD_CORE_STAGE_@X@_POSTPROCESS_H_
