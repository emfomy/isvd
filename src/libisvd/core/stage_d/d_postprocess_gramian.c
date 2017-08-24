////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    src/libisvd/core/stage_d/d_postprocess_gramian.c
/// @brief   The Gramian Postprocessing (double precision)
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/core/stage_d.h>
#include <isvd/la.h>
#include <isvd/util/arg.h>
#include <isvd/util/memory.h>

typedef double isvd_val_t;

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
static void projectBlockCol(
    const isvd_Param param,
    const char ordera,
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
    const mpi_int_t  ut_root,
    const mpi_int_t  vt_root
) {

  ISVD_UNUSED(s);
  ISVD_UNUSED(vt);
  ISVD_UNUSED(ldut);
  ISVD_UNUSED(ldvt);
  ISVD_UNUSED(vt_root);

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
  char transa_ = (ordera == 'C') ? 'N' : 'T';
  isvd_dgemm('N', transa_, l, nj, m, 1.0, qt_, ldqt_, a, lda, 0.0, zt, ldzt);

  // ====================================================================================================================== //
  // Deallocate memory

  if ( !use_ut ) {
    isvd_free(qt_);
  }

}

static void projectBlockRow(
    const isvd_Param param,
    const char ordera,
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
    const mpi_int_t  ut_root,
    const mpi_int_t  vt_root
) {

  ISVD_UNUSED(s);
  ISVD_UNUSED(ut);
  ISVD_UNUSED(ldut);
  ISVD_UNUSED(ldvt);
  ISVD_UNUSED(ut_root);

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
  char transa_ = (ordera == 'C') ? 'N' : 'T';
  isvd_dgemm('N', transa_, l, n, mj, 1.0, qt, ldqt, a, lda, 0.0, zt_, ldzt_);

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
/// @ingroup  core_stage_d_module
/// Gramian Postprocessing (double precision)
///
/// @param[in]   param       The @ref isvd_Param "parameters".
/// @param[in]   argv, argc  The arguments and its length. (not using)
/// @param[in]   retv, retc  The return values and its length. (not using)
/// <hr>
/// @param[in]   dista       The parallel distribution of 𝑨. <br>
///                          `'C'`: block-column parallelism. <br>
///                          `'R'`: block-row parallelism.
/// @param[in]   ordera      The storage ordering of 𝑨. <br>
///                          `'C'`: column-major ordering. <br>
///                          `'R'`: row-major ordering.
/// @param[in]   a, lda      The column/row-block 𝑨 (@f$m \times n_j@f$) and its leading dimension. <br>
///                          `dista='C'`: the size must be @f$m \times n_j@f$. <br>
///                          `dista='R'`: the size must be @f$m_j \times n@f$.
/// @param[in]   qt, ldqt    The row-block 𝑸 (@f$ m_b \times l @f$, row-major) and its leading dimension.
/// @param[in]   s           The vector 𝝈 (@f$k \times 1@f$).
/// @param[in]   ut, ldut    The matrix 𝑼 (row-major) and its leading dimension. <br>
///                          `ut_root >= 0`: the size must be @f$Pm_b \times k@f$, and @p ldut must be @f$l@f$. <br>
///                          `ut_root = -1`: the size must be @f$m_b \times k@f$, and @p ldut must be at least @f$l@f$. <br>
///                          `ut_root < -1`: not referenced.
/// @param[in]   vt, ldvt    The matrix 𝑽 (row-major) and its leading dimension. <br>
///                          `vt_root >= 0`: the size must be @f$Pn_b \times k@f$, and @p ldvt must be @f$l@f$. <br>
///                          `vt_root = -1`: the size must be @f$n_b \times k@f$, and @p ldvt must be at least @f$l@f$. <br>
///                          `vt_root < -1`: not referenced.
/// @param[in]   ut_root     The option for computing 𝑼. <br>
///                          `ut_root >= 0`: gather 𝑼 to the MPI process of ID `ut_root`. <br>
///                          `ut_root = -1`: compute row-block 𝑼. <br>
///                          `ut_root < -1`: does not compute 𝑼.
/// @param[in]   vt_root     The option for computing 𝑽. <br>
///                          `vt_root >= 0`: gather 𝑽 to the MPI process of ID `vt_root`. <br>
///                          `vt_root = -1`: compute row-block 𝑽. <br>
///                          `vt_root < -1`: does not compute 𝑽.
/// <hr>
/// @param[out]  s           Replaced by the singular values 𝝈.
/// @param[out]  ut          Replaced by the left singular vectors 𝑼 (row-major).
/// @param[out]  vt          Replaced by the right singular vectors 𝑽 (row-major).
///
void isvd_dPostprocessGramian(
    const isvd_Param param,
    const isvd_val_t *argv,
    const isvd_int_t argc,
          isvd_val_t *retv,
    const isvd_int_t retc,
    const char dista,
    const char ordera,
    const isvd_val_t *a,
    const isvd_int_t lda,
    const isvd_val_t *qt,
    const isvd_int_t ldqt,
          isvd_val_t *s,
          isvd_val_t *ut,
    const isvd_int_t ldut,
          isvd_val_t *vt,
    const isvd_int_t ldvt,
    const mpi_int_t  ut_root,
    const mpi_int_t  vt_root
) {

  ISVD_UNUSED(argv);
  ISVD_UNUSED(argc);
  ISVD_UNUSED(retv);
  ISVD_UNUSED(retc);

  // ====================================================================================================================== //
  // Get parameters

  const isvd_int_t mj = param.nrow_proc;
  const isvd_int_t mb = param.nrow_each;
  const isvd_int_t nj = param.ncol_proc;
  const isvd_int_t nb = param.ncol_each;
  const isvd_int_t k  = param.rank;
  const isvd_int_t l  = param.dim_sketch;

  // ====================================================================================================================== //
  // Check arguments

  const char dista_  = isvd_arg2char("DISTA",  dista,  "CR", NULL);
  const char ordera_ = isvd_arg2char("ORDERA", ordera, "CR", NULL);
  if ( !dista_ || !ordera_ ) return;

  if ( ut_root >= 0 ) {
    isvd_assert_eq(ldut, l);
  } else if ( ut_root == -1 ) {
    isvd_assert_ge(ldut, l);
  }

  if ( vt_root >= 0 ) {
    isvd_assert_eq(ldvt, l);
  } else if ( vt_root == -1 ) {
    isvd_assert_ge(ldvt, l);
  }

  // ====================================================================================================================== //
  // Allocate memory

  isvd_val_t *zt = isvd_dmalloc(nb * l);
  isvd_int_t ldzt = l;

  isvd_val_t *w = isvd_dmalloc(l * l);
  isvd_int_t ldw = l;

  // ====================================================================================================================== //
  // Projection

  switch ( dista_ ) {
    case 'C': {
      projectBlockCol(param, ordera_, a, lda, qt, ldqt, zt, ldzt, s, ut, ldut, vt, ldvt, ut_root, vt_root);
      break;
    }
    case 'R': {
      projectBlockRow(param, ordera_, a, lda, qt, ldqt, zt, ldzt, s, ut, ldut, vt, ldvt, ut_root, vt_root);
      break;
    }
  }

  // ====================================================================================================================== //
  // Compute eigen-decomposition

  // W := Z' * Z
  isvd_dgemm('N', 'T', l, l, nj, 1.0, zt, ldzt, zt, ldzt, 0.0, w, ldw);
  MPI_Allreduce(MPI_IN_PLACE, w, ldw*l, MPI_DOUBLE, MPI_SUM, param.mpi_comm);

  // eig(W) = W * S^2 * W'
  const char jobw_ = (ut_root >= -1 || vt_root >= -1) ? 'O' : 'N';
  isvd_dgesvd(jobw_, 'N', l, l, w, ldw, s, NULL, 1, NULL, 1);
  vdSqrt(l, s, s);

  // ====================================================================================================================== //
  // Compute singular vectors

  // U := Q * W (U' := W' * Q')
  if ( ut_root >= -1 ) {
    isvd_dgemm('T', 'N', k, mj, k, 1.0, w, ldw, qt, ldqt, 0.0, ut, ldut);

    if ( ut_root >= 0 ) {
      if ( param.mpi_rank == ut_root ) {
        MPI_Gather(MPI_IN_PLACE, mb*ldut, MPI_DOUBLE, ut, mb*ldut, MPI_DOUBLE, ut_root, param.mpi_comm);
      } else {
        MPI_Gather(ut, mb*ldut, MPI_DOUBLE, NULL, mb*ldut, MPI_DOUBLE, ut_root, param.mpi_comm);
      }
    }
  }

  // V := Z * W / S (V' := (W / S)' * Z')
  if ( vt_root >= -1 ) {
    for ( isvd_int_t ii = 0; ii < l; ++ii ) {
      isvd_dscal(l, 1.0/s[ii], w + ii*ldw, 1);
    }
    isvd_dgemm('T', 'N', k, nj, k, 1.0, w, ldw, zt, ldzt, 0.0, vt, ldvt);

    if ( vt_root >= 0 ) {
      if ( param.mpi_rank == vt_root ) {
        MPI_Gather(MPI_IN_PLACE, nb*ldvt, MPI_DOUBLE, vt, nb*ldvt, MPI_DOUBLE, vt_root, param.mpi_comm);
      } else {
        MPI_Gather(vt, nb*ldvt, MPI_DOUBLE, NULL, nb*ldvt, MPI_DOUBLE, vt_root, param.mpi_comm);
      }
    }
  }

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_free(zt);
  isvd_free(w);

}
