////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/gpu/stage/@x@_sketch_gpu.h
/// \brief      The GPU Sketching utilities (@xname@ precision)
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _LIBISVD_GPU_STAGE_@X@_SKETCH_GPU_H_
#define _LIBISVD_GPU_STAGE_@X@_SKETCH_GPU_H_

#include <isvd/gpu/@x@_stage.h>
#include <libisvd/gpu/def.h>
#include <isvd/la.h>
#include <libisvd/util/function.h>
#include <libisvd/util/memory.h>
#include <libisvd/util/omp.h>

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
static void sketchBlockCol(
    const isvd_Param  param,
    const char        ordera,
    const @xtype@    *a,
    const isvd_int_t  lda,
          @xtype@    *yst,
    const isvd_int_t  ldyst,
    const isvd_int_t  seed,
    const mpi_int_t   mpi_root
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
  // Check memory

  size_t free_byte, total_byte;
  cudaMemGetInfo(&free_byte, &total_byte);
  if ( isvd_gpu_memory_limit > 0 ) free_byte = min(free_byte, isvd_gpu_memory_limit);
  isvd_int_t melem = free_byte / sizeof(@xtype@);
  isvd_int_t nelem_used = m * Nl;
  if ( melem < nelem_used ) {
    fprintf(stderr, "No enough GPU memory. (Request at least %"PRId64" bytes. Only %"PRId64" bytes free.",
            nelem_used * sizeof(@xtype@), melem * sizeof(@xtype@));
    isvd_assert_fail();
  }
  isvd_int_t n_gpu = (melem - nelem_used) / (m + Nl);
  if ( n_gpu > (isvd_int_t)isvd_kBlockSizeGpu ) n_gpu = (n_gpu / isvd_kBlockSizeGpu) * isvd_kBlockSizeGpu;
  n_gpu = min(n_gpu, nj);

  // ====================================================================================================================== //
  // Allocate memory

  @xtype@ *omegat = isvd_@x@malloc(Nl * nj);
  isvd_int_t ldomegat = Nl;

  @xtype@ *yst_ = isvd_@x@malloc(Nl * Pmb);
  isvd_int_t ldyst_ = Nl;

  @xtype@ *a_gpu;
  magma_@x@malloc(&a_gpu, m * n_gpu);
  isvd_int_t lda_gpu = (ordera == 'C') ? m : n_gpu;

  @xtype@ *omegat_gpu;
  magma_@x@malloc(&omegat_gpu, Nl * n_gpu);
  isvd_int_t ldomegat_gpu = Nl;

  @xtype@ *yst_gpu;
  magma_@x@malloc(&yst_gpu, Nl * m);
  isvd_int_t ldyst_gpu = Nl;

  // ====================================================================================================================== //
  // Random generate

  isvd_int_t seed_ = seed;
  MPI_Bcast(&seed_, sizeof(seed_), MPI_BYTE, mpi_root, param.mpi_comm);

  ISVD_OMP_PARALLEL
  {
    omp_int_t omp_size = isvd_getOmpSize();
    omp_int_t omp_rank = isvd_getOmpRank();

    isvd_int_t len   = nj * Nl / omp_size;
    isvd_int_t start = len * omp_rank;
    if ( omp_rank == omp_size-1 ) {
      len = nj * Nl - start;
    }

    isvd_VSLStreamStatePtr stream;
    isvd_vslNewStream(&stream, seed_);
    isvd_vslSkipAheadStream(stream, (nb * Nl * param.mpi_rank + start) * 2);
    isvd_v@x@RngGaussian(stream, len, omegat + start, 0.0, 1.0);

    isvd_vslDeleteStream(&stream);
  }

  // ====================================================================================================================== //
  // Project

  cudaMemset(yst_gpu, 0, ldyst_gpu * m * sizeof(@xtype@));
  char transa_ = (ordera == 'C') ? 'T' : 'N';
  isvd_int_t idx;

  for ( idx = 0; idx < nj; idx += n_gpu ) {
    const @xtype@ *a_tmp = (ordera == 'C') ? (a + lda*idx) : (a+idx);
    const @xtype@ *omegat_tmp = omegat + ldomegat*idx;
    const isvd_int_t n_tmp = min(n_gpu, nj-idx);

    // Send A and Omega
    if ( ordera == 'C' ) {
      magma_@x@setmatrix(m, n_tmp, a_tmp, lda, a_gpu, lda_gpu);
    } else {
      magma_@x@setmatrix(n_tmp, m, a_tmp, lda, a_gpu, lda_gpu);
    }
    magma_@x@setmatrix(Nl, n_tmp, omegat_tmp, ldomegat, omegat_gpu, ldomegat_gpu);

    // Yi := A * Omegai (Yi' := Omegai' * A')
    magma_@x@gemm(MagmaNoTrans, magma_trans_const(transa_), Nl, m, n_tmp,
                  1.0, omegat_gpu, ldomegat_gpu, a_gpu, lda_gpu, 1.0, yst_gpu, ldyst_gpu);
  }

  // ====================================================================================================================== //
  // Retrieve data

  magma_@x@getmatrix(Nl, m, yst_gpu, ldyst_gpu, yst_, ldyst_);

  // ====================================================================================================================== //
  // Rearrange

  MPI_Reduce_scatter_block(yst_, yst, mb*ldyst_, MPI_@X_TYPE@, MPI_SUM, param.mpi_comm);

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_free(omegat);
  magma_free(a_gpu);
  magma_free(omegat_gpu);
  magma_free(yst_gpu);

}

static void sketchBlockRow(
    const isvd_Param  param,
    const char        ordera,
    const @xtype@    *a,
    const isvd_int_t  lda,
          @xtype@    *yst,
    const isvd_int_t  ldyst,
    const isvd_int_t  seed,
    const mpi_int_t   mpi_root
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
  // Check memory

  size_t free_byte, total_byte;
  cudaMemGetInfo(&free_byte, &total_byte);
  isvd_int_t melem = free_byte / sizeof(@xtype@);
  isvd_int_t nelem_used = mj * Nl;
  if ( melem < nelem_used ) {
    fprintf(stderr, "No enough GPU memory. (Request at least %"PRId64" bytes. Only %"PRId64" bytes free.",
            nelem_used * sizeof(@xtype@), melem * sizeof(@xtype@));
    isvd_assert_fail();
  }
  isvd_int_t n_gpu = (melem - nelem_used) / (mj + Nl);
  if ( n_gpu > (isvd_int_t)isvd_kBlockSizeGpu ) n_gpu = (n_gpu / isvd_kBlockSizeGpu) * isvd_kBlockSizeGpu;
  n_gpu = min(n_gpu, n);

  // ====================================================================================================================== //
  // Allocate memory

  @xtype@ *omegat = isvd_@x@malloc(n * Nl);
  isvd_int_t ldomegat = Nl;

  @xtype@ *a_gpu;
  magma_@x@malloc(&a_gpu, mj * n_gpu);
  isvd_int_t lda_gpu = (ordera == 'C') ? mj : n_gpu;

  @xtype@ *omegat_gpu;
  magma_@x@malloc(&omegat_gpu, Nl * n_gpu);
  isvd_int_t ldomegat_gpu = Nl;

  @xtype@ *yst_gpu;
  magma_@x@malloc(&yst_gpu, Nl * mj);
  isvd_int_t ldyst_gpu = Nl;

  // ====================================================================================================================== //
  // Random generate

  isvd_int_t seed_ = seed;
  MPI_Bcast(&seed_, sizeof(isvd_VSLStreamStatePtr), MPI_BYTE, mpi_root, param.mpi_comm);

  ISVD_OMP_PARALLEL
  {
    omp_int_t omp_size = isvd_getOmpSize();
    omp_int_t omp_rank = isvd_getOmpRank();

    isvd_int_t len   = n * Nl / omp_size;
    isvd_int_t start = len * omp_rank;
    if ( omp_rank == omp_size-1 ) {
      len = n * Nl - start;
    }

    isvd_VSLStreamStatePtr stream;
    isvd_vslNewStream(&stream, seed_);
    isvd_vslSkipAheadStream(stream, start * 2);
    isvd_v@x@RngGaussian(stream, len, omegat + start, 0.0, 1.0);

    isvd_vslDeleteStream(&stream);
  }

  // ====================================================================================================================== //
  // Project

  cudaMemset(yst_gpu, 0, ldyst_gpu * mj * sizeof(@xtype@));
  char transa_ = (ordera == 'C') ? 'T' : 'N';
  isvd_int_t idx;

  for ( idx = 0; idx < n; idx += n_gpu ) {
    const @xtype@ *a_tmp = (ordera == 'C') ? (a + lda*idx) : (a+idx);
    const @xtype@ *omegat_tmp = omegat + ldomegat*idx;
    const isvd_int_t n_tmp = min(n_gpu, n-idx);

    // Send A and Omega
    if ( ordera == 'C' ) {
      magma_@x@setmatrix(mj, n_tmp, a_tmp, lda, a_gpu, lda_gpu);
    } else {
      magma_@x@setmatrix(n_tmp, mj, a_tmp, lda, a_gpu, lda_gpu);
    }
    magma_@x@setmatrix(Nl, n_tmp, omegat_tmp, ldomegat, omegat_gpu, ldomegat_gpu);

    // Yi := A * Omegai (Yi' := Omegai' * A')
    magma_@x@gemm(MagmaNoTrans, magma_trans_const(transa_), Nl, mj, n_tmp,
                  1.0, omegat_gpu, ldomegat_gpu, a_gpu, lda_gpu, 1.0, yst_gpu, ldyst_gpu);
  }

  // ====================================================================================================================== //
  // Retrieve data

  magma_@x@getmatrix(Nl, mj, yst_gpu, ldyst_gpu, yst, ldyst);

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_free(omegat);
  magma_free(a_gpu);
  magma_free(omegat_gpu);
  magma_free(yst_gpu);

}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

#endif  // _LIBISVD_GPU_STAGE_@X@_SKETCH_GPU_H_
