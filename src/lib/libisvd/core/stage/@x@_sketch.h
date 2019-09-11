////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/core/stage/@x@_sketch.h
/// \brief      The Sketching utilities (@xname@ precision).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef LIBISVD_CORE_STAGE_@X@_SKETCH_H_
#define LIBISVD_CORE_STAGE_@X@_SKETCH_H_

#include <isvd/core/@x@_stage.h>
#include <libisvd/def.h>
#include <isvd/la.h>
#include <isvd/util/memory.h>
#include <isvd/util/mpi.h>
#include <isvd/util/omp.h>

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
static void sketchBlockCol(
    const isvd_Param    param,
    const char          ordera,
    const @xtype_____@ *a,
    const isvd_int_t    lda,
          @xtype_____@ *yst,
    const isvd_int_t    ldyst,
    const isvd_int_t    seed,
    const mpi_int_t     mpi_root
) {

  ISVD_UNUSED(ldyst);

  // ====================================================================================================================== //
  // Get parameters

  const isvd_int_t m   = param.nrow;
  const isvd_int_t mb  = param.nrow_each;
  const isvd_int_t Pmb = param.nrow_total;
  const isvd_int_t nj  = param.ncol_proc;
  const isvd_int_t nb  = param.ncol_each;
  const isvd_int_t Nl  = param.dim_sketch_total;

  // ====================================================================================================================== //
  // Check arguments

  switch ( ordera ) {
    case 'C': isvd_assert_ge(lda, m);  break;
    case 'R': isvd_assert_ge(lda, nj); break;
    default:  isvd_assert_fail();
  }
  isvd_assert_eq(ldyst, Nl);

  // ====================================================================================================================== //
  // Allocate memory

  // matrix Omega'
  @xtype_____@ *omegat = isvd_@x@Malloc(Nl * nj);
  isvd_int_t ldomegat = Nl;

  // matrix Y'
  @xtype_____@ *yst_ = isvd_@x@Malloc(Nl * Pmb);
  isvd_int_t ldyst_ = Nl;

  // ====================================================================================================================== //
  // Random generate

  isvd_int_t seed_ = seed;
  isvd_assert_pass(MPI_Bcast(&seed_, sizeof(seed_), MPI_BYTE, mpi_root, param.mpi_comm));
  isvd_v@x@RngGaussianDriver(seed_, Nl * nb * param.mpi_rank, nj * Nl, omegat, 0.0, 1.0);

  // ====================================================================================================================== //
  // Project

  // Yi := A * Omegai (Yi' := Omegai' * A')
  char transa_ = (ordera == 'C') ? 'T' : 'N';
  isvd_@x@Gemm('N', transa_, Nl, m, nj, 1.0, omegat, ldomegat, a, lda, 0.0, yst_, ldyst_);

  // ====================================================================================================================== //
  // Rearrange

  isvd_assert_pass(MPI_Reduce_scatter_block(yst_, yst, mb*ldyst_, MPI_@XTYPE@, MPI_SUM, param.mpi_comm));

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_Free(omegat);
  isvd_Free(yst_);

}

static void sketchBlockRow(
    const isvd_Param    param,
    const char          ordera,
    const @xtype_____@ *a,
    const isvd_int_t    lda,
          @xtype_____@ *yst,
    const isvd_int_t    ldyst,
    const isvd_int_t    seed,
    const mpi_int_t     mpi_root
) {

  // ====================================================================================================================== //
  // Get parameters

  const isvd_int_t mj = param.nrow_proc;
  const isvd_int_t n  = param.ncol;
  const isvd_int_t Nl = param.dim_sketch_total;

  // ====================================================================================================================== //
  // Check arguments

  switch ( ordera ) {
    case 'C': isvd_assert_ge(lda, mj); break;
    case 'R': isvd_assert_ge(lda, n);  break;
    default:  isvd_assert_fail();
  }
  isvd_assert_ge(ldyst, Nl);

  // ====================================================================================================================== //
  // Allocate memory

  // matrix Omega'
  @xtype_____@ *omegat = isvd_@x@Malloc(Nl * n);
  isvd_int_t ldomegat = Nl;

  // ====================================================================================================================== //
  // Random generate

  isvd_int_t seed_ = seed;
  isvd_assert_pass(MPI_Bcast(&seed_, sizeof(seed_), MPI_BYTE, mpi_root, param.mpi_comm));
  isvd_v@x@RngGaussianDriver(seed_, 0, n * Nl, omegat, 0.0, 1.0);

  // ====================================================================================================================== //
  // Project

  // Yi := A * Omegai (Yi' := Omegai' * A')
  char transa_ = (ordera == 'C') ? 'T' : 'N';
  isvd_@x@Gemm('N', transa_, Nl, mj, n, 1.0, omegat, ldomegat, a, lda, 0.0, yst, ldyst);

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_Free(omegat);

}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

#endif  // LIBISVD_CORE_STAGE_@X@_SKETCH_H_
