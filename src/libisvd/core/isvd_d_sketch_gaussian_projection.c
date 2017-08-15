////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    src/libisvd/core/isvd_d_sketch_gaussian_projection.c
/// @brief   The Gaussian Projection Sketching (double precision)
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/core/dtype.h>
#include <isvd/util/memory.h>
#include <isvd/util/omp.h>

typedef double isvd_val_t;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
void isvd_dSketchGaussianProjectionBlockCol(
    const char transa,
    const isvd_Param param,
    const isvd_val_t *a,
    const isvd_int_t lda,
          isvd_val_t *yt,
    const isvd_int_t ldyt,
    const isvd_int_t seed,
    const mpi_int_t mpi_root
) {

  // ====================================================================================================================== //
  // Get parameters

  isvd_int_t m   = param.nrow;
  isvd_int_t mb  = param.nrow_each;
  isvd_int_t Pmb = param.nrow_total;
  isvd_int_t nj  = param.ncol_proc;
  isvd_int_t nb  = param.ncol_each;
  isvd_int_t Nl  = param.dim_sketch_total;

  // ====================================================================================================================== //
  // Check arguments

  switch ( transa ) {
    case 'N': isvd_assert_ge(lda,  m);  break;
    case 'T': isvd_assert_ge(lda,  nj); break;
  }
  isvd_assert_eq(ldyt, Nl);

  // ====================================================================================================================== //
  // Allocate memory

  isvd_val_t *omegat = isvd_dmalloc(nj * Nl);
  isvd_int_t ldomegat = Nl;

  isvd_val_t *yt_ = isvd_dmalloc(Pmb * Nl);
  isvd_int_t ldyt_ = Nl;

  // ====================================================================================================================== //
  // Random generate

  isvd_int_t seed_ = seed;
  MPI_Bcast(&seed_, sizeof(VSLStreamStatePtr), MPI_BYTE, mpi_root, param.mpi_comm);

#ifdef _OPENMP
  #pragma omp parallel
#endif  // _OPENMP
  {
    isvd_int_t omp_size = isvd_getOmpSize();
    isvd_int_t omp_rank = isvd_getOmpRank();

    isvd_int_t len   = nj * Nl / omp_size;
    isvd_int_t start = len * omp_rank;
    if ( omp_rank == omp_size-1 ) {
      len = nj * Nl - start;
    }

    VSLStreamStatePtr stream;
    vslNewStream(&stream, VSL_BRNG_SFMT19937, seed_);
    vslSkipAheadStream(stream, (nb * Nl * param.mpi_rank + start) * 2);
    vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER, stream, len, omegat + start, 0.0, 1.0);

    vslDeleteStream(&stream);
  }

  // ====================================================================================================================== //
  // Project

  // Yi := A * Omegai (Yi' := Omegai' * A')
  isvd_dmemset0(yt_, Pmb * Nl);
  CBLAS_TRANSPOSE transa_ = (transa == 'N') ? CblasTrans : CblasNoTrans;
  cblas_dgemm(CblasColMajor, CblasNoTrans, transa_, Nl, m, nj,
              1.0, omegat, ldomegat, a, lda, 0.0, yt_, ldyt_);

  // ====================================================================================================================== //
  // Rearrange

  MPI_Reduce_scatter_block(yt_, yt, mb * Nl, MPI_DOUBLE, MPI_SUM, param.mpi_comm);

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_free(omegat);

}

void isvd_dSketchGaussianProjectionBlockRow(
    const char transa,
    const isvd_Param param,
    const isvd_val_t *a,
    const isvd_int_t lda,
          isvd_val_t *yt,
    const isvd_int_t ldyt,
    const isvd_int_t seed,
    const mpi_int_t mpi_root
) {

  // ====================================================================================================================== //
  // Get parameters

  isvd_int_t mj = param.nrow_proc;
  isvd_int_t mb = param.nrow_each;
  isvd_int_t n  = param.ncol;
  isvd_int_t Nl = param.dim_sketch_total;

  // ====================================================================================================================== //
  // Check arguments

  switch ( transa ) {
    case 'T': isvd_assert_ge(lda,  mj); break;
    case 'N': isvd_assert_ge(lda,  n);  break;
  }
  isvd_assert_ge(ldyt, Nl);

  // ====================================================================================================================== //
  // Allocate memory

  isvd_val_t *omegat = isvd_dmalloc(n * Nl);
  isvd_int_t ldomegat = Nl;

  // ====================================================================================================================== //
  // Random generate

  isvd_int_t seed_ = seed;
  MPI_Bcast(&seed_, sizeof(VSLStreamStatePtr), MPI_BYTE, mpi_root, param.mpi_comm);

#ifdef _OPENMP
  #pragma omp parallel
#endif  // _OPENMP
  {
    isvd_int_t omp_size = isvd_getOmpSize();
    isvd_int_t omp_rank = isvd_getOmpRank();

    isvd_int_t len   = n * Nl / omp_size;
    isvd_int_t start = len * omp_rank;
    if ( omp_rank == omp_size-1 ) {
      len = n * Nl - start;
    }

    VSLStreamStatePtr stream;
    vslNewStream(&stream, VSL_BRNG_SFMT19937, seed_);
    vslSkipAheadStream(stream, start * 2);
    vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER, stream, len, omegat + start, 0.0, 1.0);

    vslDeleteStream(&stream);
  }

  // ====================================================================================================================== //
  // Project

  // Yi := A * Omegai (Yi' := Omegai' * A')
  isvd_dmemset0(yt, mb * Nl);
  CBLAS_TRANSPOSE transa_ = (transa == 'N') ? CblasTrans : CblasNoTrans;
  cblas_dgemm(CblasColMajor, CblasNoTrans, transa_, Nl, mj, n, 1.0, omegat, ldomegat, a, lda, 0.0, yt, ldyt);

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_free(omegat);

}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  core_dtype_module
/// Gaussian Projection Sketching (double precision)
///
/// @param[in]   dista     The parallel distribution of 𝑨. <br>
///                        `'C'`: block-column parallelism. <br>
///                        `'R'`: block-row parallelism.
/// @param[in]   ordera    The storage ordering of 𝑨. <br>
///                        `'C'`: column-major ordering. <br>
///                        `'R'`: row-major ordering.
/// @param[in]   param     The @ref isvd_Param "parameters".
/// @param[in]   a, lda    The column/row-block 𝑨 (@f$m \times n_j@f$) and its leading dimension. <br>
///                        If `dista='C'`: the size must be @f$m \times n_j@f$. <br>
///                        If `dista='R'`: the size must be @f$m_j \times n@f$.
/// @param[in]   yt, ldyt  The row-block 𝖄 (@f$m_b \times Nl@f$, row-major) and its leading dimension. <br>
///                        If `dista='C'`: @p ldyt must be @f$Nl@f$.
/// @param[in]   seed      The random seed.
/// @param[in]   mpi_root  The root MPI process ID.
/// <hr>
/// @param[out]  yt        Replaced by the row-block 𝖄 (row-major).
///
void isvd_dSketchGaussianProjection(
    const char dista,
    const char ordera,
    const isvd_Param param,
    const isvd_val_t *a,
    const isvd_int_t lda,
          isvd_val_t *yt,
    const isvd_int_t ldyt,
    const isvd_int_t seed,
    const mpi_int_t mpi_root
) {

  // ====================================================================================================================== //
  // Check arguments

  char dista_  = isvd_arg2char("STOREA", dista,  "CR", "CR");
  char transa_ = isvd_arg2char("ORDERA", ordera, "CR", "NT");
  if ( dista_ == '\0' || transa_ == '\0' ) return;

  // ====================================================================================================================== //
  // Run

  switch ( dista_ ) {
    case 'C': isvd_dSketchGaussianProjectionBlockCol(transa_, param, a, lda, yt, ldyt, seed, mpi_root); break;
    case 'R': isvd_dSketchGaussianProjectionBlockRow(transa_, param, a, lda, yt, ldyt, seed, mpi_root); break;
  }
}
