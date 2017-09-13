////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/core/stage/@x@_integrate_hierarchical_reduction.c
/// \brief      The Hierarchical Reduction Integration (@xname@ precision).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/core/@x@_stage.h>
#include <libisvd/def.h>
#include <isvd/la.h>
#include <isvd/util/memory.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_@x@_stage_module
/// \brief  Hierarchical Reduction Integration (@xname@ precision).
///
/// \param[in]   param       The \ref isvd_Param "parameters".
/// \param[in]   argv, argc  The arguments and its length. (not using)
/// \param[in]   retv, retc  The return values and its length. (not using)
/// <hr>
/// \param[in]   yst, ldyst  The row-block 𝕼 (\f$ m_b \times Nl \f$, row-major) and its leading dimension.
/// \param[in]   qt, ldqt    The row-block 𝑸 (\f$ m_b \times l \f$, row-major) and its leading dimension.
/// <hr>
/// \param[out]  qt          Replaced by the row-block 𝑸 (row-major).
///
/// \attention  \b yst will be destroyed!
///
/// \note  If \b argc < 0, then a default argument query is assumed;
///        the routine only returns the first \b retc default arguments in \b retv.
///
void isvd_@x@IntegrateHierarchicalReduction(
    const isvd_Param  param,
    const @xtype@    *argv,
    const isvd_int_t  argc,
          @xtype@    *retv,
    const isvd_int_t  retc,
          @xtype@    *yst,
    const isvd_int_t  ldyst,
          @xtype@    *qt,
    const isvd_int_t  ldqt
) {

  if ( argc > 0 ) { isvd_assert_ne(argv, nullptr); }
  if ( retc > 0 ) { isvd_assert_ne(retv, nullptr); }
  if ( argc < 0 ) return;

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

  @xtype@ *qst = yst;
  isvd_int_t ldqst = ldyst;

  // matrix B
  @xtype@ *bs = isvd_@x@malloc(l * l * (N+1)/2);
  isvd_int_t ldbs = l;

  // matrix T
  @xtype@ *tt = isvd_@x@malloc(l * l);
  isvd_int_t ldtt = l;

  // vector s
  @xtype@ *s = isvd_@x@malloc(l);

  @xtype@ *tmpt = qt;
  isvd_int_t ldtmpt = ldqt;

  // ====================================================================================================================== //
  // Loop
  for ( isvd_int_t Nt = N; Nt > 1; Nt = (Nt+1)/2 ) {
    const isvd_int_t h = Nt / 2;

    // B(i) := Q(i)' * Q(i+h)
    for ( isvd_int_t i = 0; i < h; ++i ) {
      isvd_@x@Gemm('N', 'T', l, l, mj, 1.0, qst + i*l, ldqst, qst + (i+h)*l, ldqst, 0.0, bs + i*ldbs*l, ldbs);
    }
    MPI_Allreduce(MPI_IN_PLACE, bs, ldbs*l*h, MPI_@X_TYPE@, MPI_SUM, param.mpi_comm);

    for ( isvd_int_t i = 0; i < h; ++i ) {

      // matrix W
      @xtype@ *w = bs + i*ldbs*l;
      isvd_int_t ldw = ldbs;

      // matrix Q(i)
      @xtype@ *qit = qst + i*l;
      isvd_int_t ldqit = ldqst;

      // matrix Q(i+h)
      @xtype@ *qiht = qst + (i+h)*l;
      isvd_int_t ldqiht = ldqst;

      // svd(B(i)) = W * S * T'
      isvd_@x@Gesvd('O', 'S', l, l, w, ldw, s, NULL, 1, tt, ldtt);

      // Q(i) := Q(i) * W + Q(i+h) * T (Q(i)' := W' * Q(i)' + T' * Q(i+h)')
      isvd_@x@Omatcopy('N', l, mj, 1.0, qit, ldqit, tmpt, ldtmpt);
      isvd_@x@Gemm('T', 'N', l, mj, l, 1.0, w, ldw, tmpt, ldtmpt, 0.0, qit, ldqit);
      isvd_@x@Gemm('N', 'N', l, mj, l, 1.0, tt, ldtt, qiht, ldqiht, 1.0, qit, ldqit);

      // Q(i) /= sqrt(2(I+S))
      for ( isvd_int_t ii = 0; ii < l; ++ii ) {
        isvd_@x@Scal(mj, 1.0/sqrt(2.0*(1.0+s[ii])), qit + ii, ldqit);
      }
    }
  }

  // Qbar := Q(i)
  isvd_@x@Omatcopy('N', l, mj, 1.0, qst, ldqst, qt, ldqt);

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_free(bs);
  isvd_free(tt);
  isvd_free(s);

}
