////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    src/libisvd/core/stage_d/isvd_d_integrate_hierarchical_reduction.c
/// @brief   The Hierarchical Reduction Integration (double precision)
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/core/stage_d.h>
#include <isvd/util/memory.h>

typedef double isvd_val_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  core_stage_d_module
/// Hierarchical Reduction Integration (double precision)
///
/// @param[in]   param       The @ref isvd_Param "parameters".
/// @param[in]   argv, argc  The arguments and its length. (not using)
/// @param[in]   retv, retc  The return values and its length. (not using)
/// <hr>
/// @param[in]   yst, ldyst  The row-block 𝕼 (@f$ m_b \times Nl @f$, row-major) and its leading dimension.
/// @param[in]   qt, ldqt    The row-block 𝑸 (@f$ m_b \times l @f$, row-major) and its leading dimension.
/// <hr>
/// @param[out]  qt          Replaced by the row-block 𝑸 (row-major).
///
/// @attention  @p yst will be destroyed!
///
void isvd_dIntegrateHierarchicalReduction(
    const isvd_Param param,
    const isvd_val_t *argv,
    const isvd_int_t argc,
          isvd_val_t *retv,
    const isvd_int_t retc,
          isvd_val_t *yst,
    const isvd_int_t ldyst,
          isvd_val_t *qt,
    const isvd_int_t ldqt
) {

  ISVD_UNUSED(argv);
  ISVD_UNUSED(argc);
  ISVD_UNUSED(retv);
  ISVD_UNUSED(retc);

  // ====================================================================================================================== //
  // Get parameters

  const isvd_int_t mj = param.nrow_proc;
  const isvd_int_t l  = param.dim_sketch;
  const isvd_int_t N  = param.num_sketch;
  const isvd_int_t Nl = param.dim_sketch_total;

  // ====================================================================================================================== //
  // Check arguments
  isvd_assert_ge(ldyst, Nl);
  isvd_assert_ge(ldqt, l);

  // ====================================================================================================================== //
  // Allocate memory

  isvd_val_t *qst = yst;
  isvd_int_t ldqst = ldyst;

  // matrix B
  isvd_val_t *bs = isvd_dmalloc(l * l * (N+1)/2);
  isvd_int_t ldbs = l;

  // matrix T
  isvd_val_t *t = isvd_dmalloc(l * l);
  isvd_int_t ldt = l;

  // temporary matrix
  isvd_val_t *tmpt = isvd_dmalloc(mj * ldqst);
  isvd_int_t ldtmpt = ldqst;

  // vector s
  isvd_val_t *s = isvd_dmalloc(l);

  // vector superb
  isvd_val_t *superb = isvd_dmalloc(l-2);

  // ====================================================================================================================== //
  // Loop
  for ( isvd_int_t N_ = N; N_ > 1; N_ = (N_+1)/2 ) {
    const isvd_int_t h = N_ / 2;

    // B(i) := Q(i)' * Q(i+h)
    for ( isvd_int_t i = 0; i < h; ++i ) {
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans, l, l, mj, 1.0,
                  qst + i*l, ldqst, qst, ldqst + (i+h)*l, 0.0, bs + i*ldbs*l, ldbs);
    }
    MPI_Allreduce(MPI_IN_PLACE, bs, ldbs*l*h, MPI_DOUBLE, MPI_SUM, param.mpi_comm);

    for ( isvd_int_t i = 0; i < h; ++i ) {

      // matrix W
      isvd_val_t *w = bs + i*ldbs*l;
      isvd_int_t ldw = ldbs;

      // matrix Q(i)
      isvd_val_t *qit = qst + i*l;
      isvd_int_t ldqit = ldqst;

      // matrix Q(i+h)
      isvd_val_t *qiht = qst + (i+h)*l;
      isvd_int_t ldqiht = ldqst;

      // svd(B(i)) = W * S * T'
      isvd_assert_pass(LAPACKE_dgesvd(LAPACK_COL_MAJOR, 'O', 'S', l, l, w, ldw, s, NULL, 1, t, ldt, superb));

      // Q(i) := Q(i) * W + Q(i+h) * T (Q(i)' := W' * Q(i)' + T' * Q(i+h)')
      isvd_dmemcpy(tmpt, qit, mj*ldqst);
      cblas_dgemm(CblasColMajor, CblasTrans, CblasNoTrans, l, mj, l, 1.0, w, ldw, tmpt, ldtmpt, 0.0, qit, ldqit);
      cblas_dgemm(CblasColMajor, CblasTrans, CblasNoTrans, l, mj, l, 1.0, t, ldt, qiht, ldqiht, 1.0, qit, ldqit);

      // Q(i) /= sqrt(2(I+S))
      for ( isvd_int_t ii = 0; ii < l; ++ii ) {
        cblas_dscal(l, 1.0/sqrt(2.0*(1.0+s[ii])), qit + ii, ldqit);
      }
    }
  }

  // Qbar := Q(i)
  mkl_domatcopy('C', 'N', l, mj, 1.0, qst, ldqst, qt, ldqt);

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_free(bs);
  isvd_free(t);
  isvd_free(tmpt);
  isvd_free(s);
  isvd_free(superb);

}
