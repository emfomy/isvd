////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    src/libisvd/core/isvd_d_postprocess_gramian.c
/// @brief   The Gramian Postprocessing (double precision)
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/core/dtype.h>
#include <isvd/util/memory.h>

typedef double isvd_val_t;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
void projectBlockCol(
    const char jobut,
    const char jobvt,
    const char ordera,
    const isvd_Param param,
    const isvd_val_t *a,
    const isvd_int_t lda,
    const isvd_val_t *qt,
    const isvd_int_t ldqt,
          isvd_val_t *zt,
    const isvd_int_t ldzt,
          isvd_val_t *s,
          isvd_val_t *ut,
    const isvd_int_t ldut,
          isvd_val_t *vt,
    const isvd_int_t ldvt,
    const mpi_int_t mpi_root
) {

  ISVD_UNUSED(jobvt);
  ISVD_UNUSED(s);
  ISVD_UNUSED(vt);
  ISVD_UNUSED(ldut);
  ISVD_UNUSED(ldvt);

  // ====================================================================================================================== //
  // Get parameters

  isvd_int_t m   = param.nrow;
  isvd_int_t mb  = param.nrow_each;
  isvd_int_t Pmb = param.nrow_total;
  isvd_int_t nj  = param.ncol_proc;
  isvd_int_t l   = param.dim_sketch;

  // ====================================================================================================================== //
  // Check arguments

  bool use_ut = (jobut == 'S' && mpi_root >= 0);

  switch ( ordera ) {
    case 'C': isvd_assert_ge(lda, m);  break;
    case 'R': isvd_assert_ge(lda, nj); break;
  }
  isvd_assert_eq(ldqt, l);
  isvd_assert_ge(ldzt, l);
  if ( use_ut ) {
    isvd_assert_eq(ldut, l);
  }

  // ====================================================================================================================== //
  // Allocate memory

  isvd_val_t *qt_;
  if ( use_ut ) {
    qt_ = ut;
  } else {
    qt_ = isvd_dmalloc(Pmb * l);
  }
  isvd_int_t ldqt_ = l;

  // ====================================================================================================================== //
  // Rearrange

  MPI_Allgather(qt, mb*ldqt, MPI_DOUBLE, qt_, mb*ldqt, MPI_DOUBLE, param.mpi_comm);

  // ====================================================================================================================== //
  // Project

  // Z := A' * Q (Z' := Q' * A)
  CBLAS_TRANSPOSE transa_ = (ordera == 'C') ? CblasNoTrans : CblasTrans;
  cblas_dgemm(CblasColMajor, CblasNoTrans, transa_, l, nj, m, 1.0, qt_, ldqt_, a, lda, 0.0, zt, ldzt);

  // ====================================================================================================================== //
  // Deallocate memory

  if ( !use_ut ) {
    isvd_free(qt_);
  }

}

void projectBlockRow(
    const char jobut,
    const char jobvt,
    const char ordera,
    const isvd_Param param,
    const isvd_val_t *a,
    const isvd_int_t lda,
    const isvd_val_t *qt,
    const isvd_int_t ldqt,
          isvd_val_t *zt,
    const isvd_int_t ldzt,
          isvd_val_t *s,
          isvd_val_t *ut,
    const isvd_int_t ldut,
          isvd_val_t *vt,
    const isvd_int_t ldvt,
    const mpi_int_t mpi_root
) {

  ISVD_UNUSED(jobut);
  ISVD_UNUSED(s);
  ISVD_UNUSED(ut);
  ISVD_UNUSED(ldut);
  ISVD_UNUSED(ldvt);

  // ====================================================================================================================== //
  // Get parameters

  isvd_int_t mj  = param.nrow_proc;
  isvd_int_t n   = param.ncol;
  isvd_int_t nb  = param.ncol_each;
  isvd_int_t Pnb = param.ncol_total;
  isvd_int_t l   = param.dim_sketch;

  // ====================================================================================================================== //
  // Check arguments

  bool use_vt = (jobvt == 'S' && mpi_root >= 0);

  switch ( ordera ) {
    case 'C': isvd_assert_ge(lda, mj); break;
    case 'R': isvd_assert_ge(lda, n);  break;
  }
  isvd_assert_ge(ldqt, l);
  isvd_assert_eq(ldzt, l);
  if ( use_vt ) {
    isvd_assert_eq(ldvt, l);
  }

  // ====================================================================================================================== //
  // Allocate memory

  isvd_val_t *zt_;
  if ( use_vt ) {
    zt_ = vt;
  } else {
    zt_ = isvd_dmalloc(Pnb * l);
  }
  isvd_int_t ldzt_ = l;

  // ====================================================================================================================== //
  // Project

  // Z := A' * Q (Z' := Q' * A)
  CBLAS_TRANSPOSE transa_ = (ordera == 'C') ? CblasNoTrans : CblasTrans;
  cblas_dgemm(CblasColMajor, CblasNoTrans, transa_, l, n, mj, 1.0, qt, ldqt, a, lda, 0.0, zt_, ldzt_);

  // ====================================================================================================================== //
  // Rearrange

  MPI_Reduce_scatter_block(zt_, zt, nb*ldzt, MPI_DOUBLE, MPI_SUM, param.mpi_comm);

  // ====================================================================================================================== //
  // Deallocate memory

  if ( !use_vt ) {
    isvd_free(zt_);
  }

}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  core_dtype_module
/// Gramian Postprocessing (double precision)
///
/// @param[in]   jobut     The option for computing 𝑼. <br>
///                        `'S'`: computes 𝑼. <br>
///                        `'N'`: does not compute 𝑼.
/// @param[in]   jobvt     The option for computing 𝑽. <br>
///                        `'S'`: computes 𝑽. <br>
///                        `'N'`: does not compute 𝑽.
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
/// @param[in]   qt, ldqt  The row-block 𝑸 (@f$ m_b \times l @f$, row-major) and its leading dimension.
/// @param[in]   s         The vector 𝝈 (@f$k \times 1@f$).
/// @param[in]   ut, ldut  The matrix ̂̂𝑼 (row-major) and its leading dimension. <br>
///                        If `mpi_root >= 0`: the size must be @f$Pm_b \times k@f$, and @p ldut must be @f$l@f$. <br>
///                        If `mpi_root = -1`: the size must be @f$m_b \times k@f$, and @p ldut must be at least @f$l@f$.
/// @param[in]   vt, ldvt  The matrix 𝑽 (row-major) and its leading dimension. <br>
///                        If `mpi_root >= 0`: the size must be @f$Pn_b \times k@f$, and @p ldvt must be @f$l@f$. <br>
///                        If `mpi_root = -1`: the size must be @f$n_b \times k@f$, and @p ldvt must be at least @f$l@f$.
/// @param[in]   mpi_root  The root MPI process ID. <br>
/// <hr>
/// @param[out]  s         Replaced by the singular values 𝝈.
/// @param[out]  ut        Replaced by the left singular vectors 𝑼 (row-major).
/// @param[out]  vt        Replaced by the right singular vectors 𝑽 (row-major).
///
/// @attention  If `mpi_root >= 0`, then the result matrices are sent to the MPI process of ID `mpi_root`. <br>
///             If `mpi_root = -1`, then the result matrices are left on each MPI process and stored in row-blocks.
///
/// @see  isvd_Param
///
void isvd_dPostprocessGramian(
    const char jobut,
    const char jobvt,
    const char dista,
    const char ordera,
    const isvd_Param param,
    const isvd_val_t *a,
    const isvd_int_t lda,
    const isvd_val_t *qt,
    const isvd_int_t ldqt,
          isvd_val_t *s,
          isvd_val_t *ut,
    const isvd_int_t ldut,
          isvd_val_t *vt,
    const isvd_int_t ldvt,
    const mpi_int_t mpi_root
) {

  // ====================================================================================================================== //
  // Get parameters

  isvd_int_t mj = param.nrow_proc;
  isvd_int_t mb = param.nrow_each;
  isvd_int_t nj = param.ncol_proc;
  isvd_int_t nb = param.ncol_each;
  isvd_int_t k  = param.rank;
  isvd_int_t l  = param.dim_sketch;

  // ====================================================================================================================== //
  // Check arguments

  char jobut_  = isvd_arg2char("JOBUT",  jobut,  "SN", "SN");
  char jobvt_  = isvd_arg2char("JOBVT",  jobvt,  "SN", "SN");
  char dista_  = isvd_arg2char("DISTA",  dista,  "CR", "CR");
  char ordera_ = isvd_arg2char("ORDERA", ordera, "CR", "CR");
  if ( dista_ == '\0' || ordera_ == '\0' ) abort();

  if ( jobut == 'S' ) {
    if ( mpi_root >= 0 ) {
      isvd_assert_eq(ldut, l);
    } else {
      isvd_assert_ge(ldut, l);
    }
  }

  if ( jobvt == 'S' ) {
    if ( mpi_root >= 0 ) {
      isvd_assert_eq(ldvt, l);
    } else {
      isvd_assert_ge(ldvt, l);
    }
  }

  // ====================================================================================================================== //
  // Allocate memory

  isvd_val_t *zt = isvd_dmalloc(nb * l);
  isvd_int_t ldzt = l;

  isvd_val_t *w = isvd_dmalloc(l * l);
  isvd_int_t ldw = l;

  isvd_val_t *superb = isvd_dmalloc(l-2);

  // ====================================================================================================================== //
  // Projection

  switch ( dista_ ) {
    case 'C': {
      projectBlockCol(jobut_, jobvt_, ordera_, param, a, lda, qt, ldqt, zt, ldzt, s, ut, ldut, vt, ldvt, mpi_root);
      break;
    }
    case 'R': {
      projectBlockRow(jobut_, jobvt_, ordera_, param, a, lda, qt, ldqt, zt, ldzt, s, ut, ldut, vt, ldvt, mpi_root);
      break;
    }
  }

  // ====================================================================================================================== //
  // Compute eigen-decomposition

  // W := Z' * Z
  cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans, l, l, nj, 1.0, zt, ldzt, zt, ldzt, 0.0, w, ldw);
  MPI_Allreduce(MPI_IN_PLACE, w, ldw*l, MPI_DOUBLE, MPI_SUM, param.mpi_comm);

  // eig(W) = W * S^2 * W'
  isvd_assert_pass(LAPACKE_dgesvd(LAPACK_COL_MAJOR, 'O', 'N', l, l, w, ldw, s, NULL, 1, NULL, 1, superb));
  vdSqrt(l, s, s);

  // ====================================================================================================================== //
  // Compute singular vectors

  // U := Q * W (U' := W' * Q')
  if ( jobvt == 'S' ) {
    cblas_dgemm(CblasColMajor, CblasTrans, CblasNoTrans, k, mj, k, 1.0, w, ldw, qt, ldqt, 0.0, ut, ldut);

    if ( mpi_root >= 0 ) {
      MPI_Gather(MPI_IN_PLACE, mb*ldut, MPI_DOUBLE, ut, mb*ldut, MPI_DOUBLE, mpi_root, param.mpi_comm);
    }
  }

  // V := Z * W / S (V' := (W / S)' * Z')
  if ( jobvt == 'S' ) {
    for ( isvd_int_t ii = 0; ii < l; ++ii ) {
      cblas_dscal(l, 1.0/s[ii], w + ii*ldw, 1);
    }
    cblas_dgemm(CblasColMajor, CblasTrans, CblasNoTrans, k, nj, k, 1.0, w, ldw, zt, ldzt, 0.0, vt, ldvt);

    if ( mpi_root >= 0 ) {
      MPI_Gather(MPI_IN_PLACE, nb*ldvt, MPI_DOUBLE, vt, nb*ldvt, MPI_DOUBLE, mpi_root, param.mpi_comm);
    }
  }

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_free(zt);
  isvd_free(w);
  isvd_free(superb);

}
