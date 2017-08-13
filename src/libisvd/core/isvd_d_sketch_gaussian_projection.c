////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    src/libisvd/core/isvd_d_sketch_gaussian_projection.c
/// @brief   The Gaussian Projection Sketching.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/core/dtype.h>
#include <isvd/util/memory.h>

typedef double isvd_val_t;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
void isvd_dSketchGaussianProjectionBlockCol(
    const char transa,
    const isvd_Param param,
    const isvd_val_t *a,
    const isvd_int_t lda,
          isvd_val_t *yt,
    const isvd_int_t ldyt,
    const isvd_int_t seed
) {

  // ====================================================================================================================== //
  // Get parameters

  isvd_int_t m   = param.nrow;
  isvd_int_t mb  = param.nrow_each;
  isvd_int_t Pmb = param.nrow_total;
  isvd_int_t nj  = param.ncol_proc;
  isvd_int_t Nl  = param.dim_sketch_total;

  // ====================================================================================================================== //
  // Check arguments

  switch ( transa ) {
    case 'T': isvd_assert_ge(lda,  m);  break;
    case 'N': isvd_assert_ge(lda,  nj); break;
  }
  isvd_assert_eq(ldyt, Nl);

  // ====================================================================================================================== //
  // Allocate memory

  isvd_val_t *omega = isvd_dmalloc(nj * Nl);
  isvd_int_t ldomega = Nl;

  isvd_val_t *yt_ = isvd_dmalloc(Pmb * Nl);
  isvd_int_t ldyt_ = Nl;

  // ====================================================================================================================== //
  // Random generate

  #pragma warning
  isvd_int_t iseed[] = {0, 0, 0, 1};
  LAPACKE_dlarnv(3, iseed, nj * Nl, omega);

  // ====================================================================================================================== //
  // Project

  isvd_dmemset0(yt_, Pmb * Nl);
  CBLAS_TRANSPOSE transa_ = (transa == 'C') ? CblasNoTrans : CblasTrans;
  cblas_dgemm(CblasRowMajor, transa_, CblasNoTrans, m, Nl, nj, 1.0, a, lda, omega, ldomega, 0.0, yt_, ldyt_);

  // ====================================================================================================================== //
  // Rearrange

  MPI_Reduce_scatter_block(yt_, yt, mb * Nl, MPI_DOUBLE, MPI_SUM, param.mpi_comm);

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_free(omega);

}

void isvd_dSketchGaussianProjectionBlockRow(
    const char transa,
    const isvd_Param param,
    const isvd_val_t *a,
    const isvd_int_t lda,
          isvd_val_t *yt,
    const isvd_int_t ldyt,
    const isvd_int_t seed
) {

  // ====================================================================================================================== //
  // Get parameters

  isvd_int_t mj  = param.nrow_proc;
  isvd_int_t mb  = param.nrow_each;
  isvd_int_t Pmb = param.nrow_total;
  isvd_int_t n   = param.ncol;
  isvd_int_t Nl  = param.dim_sketch_total;

  // ====================================================================================================================== //
  // Check arguments

  switch ( transa ) {
    case 'T': isvd_assert_ge(lda,  mj); break;
    case 'N': isvd_assert_ge(lda,  n);  break;
  }
  isvd_assert_ge(ldyt, Nl);

  // ====================================================================================================================== //
  // Allocate memory

  isvd_val_t *omega = isvd_dmalloc(n * Nl);
  isvd_int_t ldomega = Nl;

  // ====================================================================================================================== //
  // Random generate

  #pragma warning
  isvd_int_t iseed[] = {0, 0, 0, 1};
  LAPACKE_dlarnv(3, iseed, n * Nl, omega);

  // ====================================================================================================================== //
  // Project

  isvd_dmemset0(yt, mb * Nl);
  CBLAS_TRANSPOSE transa_ = (transa == 'C') ? CblasNoTrans : CblasTrans;
  cblas_dgemm(CblasRowMajor, transa_, CblasNoTrans, mj, Nl, n, 1.0, a, lda, omega, ldomega, 0.0, yt, ldyt);

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_free(omega);

}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  core_dtype_s_module
/// Gaussian Projection Sketching (double precision)
///
/// @attention  The size of 𝑨 must be @f$ m \times n_j @f$ for block-column parallelism.
/// @attention  The size of 𝑨 must be @f$ m_j \times n @f$ for block-row parallelism.
/// @attention  The size of 𝖄 must be @f$ m_b \times Nl @f$ in row-major with leading dimension @f$ Nl @f$.
///
/// @see  isvd_Param
///
void isvd_dSketchGaussianProjection(
    const char dista,        ///< [in]  The parallel distribution of 𝑨. <br>
                             ///< `'C'`: block-column parallelism. <br>
                             ///< `'R'`: block-row parallelism.
    const char ordera,       ///< [in]  The storage ordering of 𝑨. <br>
                             ///< `'C'`: column-major ordering. <br>
                             ///< `'R'`: row-major ordering.
    const isvd_Param param,  ///< [in]  The parameters.
    const isvd_val_t *a,     ///< [in]  The row/column-block 𝑨.
    const isvd_int_t lda,    ///< [in]  The leading dimension of the block 𝑨.
          isvd_val_t *yt,    ///< [out] The row-block 𝖄 (row-major).
    const isvd_int_t ldyt,   ///< [in]  The leading dimension of the row-block 𝖄 (row-major).
    const isvd_int_t seed    ///< [in]  The random seed.
) {

  // ====================================================================================================================== //
  // Check arguments

  char dista_  = isvd_arg2char("STOREA", dista,  "CR", "CR");
  char transa_;
  switch ( dista_ ) {
    case 'C': transa_ = isvd_arg2char("ORDERA", ordera, "CR", "NT"); break;
    case 'R': transa_ = isvd_arg2char("ORDERA", ordera, "CR", "TN"); break;
  }
  if ( dista_ == 0 || transa_ == 0 ) return;

  // ====================================================================================================================== //
  // Run

  switch ( dista_ ) {
    case 'C': isvd_dSketchGaussianProjectionBlockCol(transa_, param, a, lda, yt, ldyt, seed); break;
    case 'R': isvd_dSketchGaussianProjectionBlockRow(transa_, param, a, lda, yt, ldyt, seed); break;
  }
}
