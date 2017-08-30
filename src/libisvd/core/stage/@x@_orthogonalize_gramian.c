////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/core/stage/@x@_orthogonalize_gramian.c
/// \brief      The Gramian Orthogonalization (@xname@ precision)
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/core/@x@_stage.h>
#include <libisvd/def.h>
#include <libisvd/la.h>
#include <libisvd/util/memory.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_@x@_stage_module
/// Gramian Orthogonalization (@xname@ precision)
///
/// \param[in]   param       The \ref isvd_Param "parameters".
/// \param[in]   argv, argc  The arguments and its length. (not using)
/// \param[in]   retv, retc  The return values and its length. (not using)
/// <hr>
/// \param[in]   yst, ldyst  The row-block 𝖄 (\f$ m_b \times Nl \f$, row-major) and its leading dimension.
/// <hr>
/// \param[out]  yst         Replaced by the row-block 𝕼 (row-major).
///
void isvd_@x@OrthogonalizeGramian(
    const isvd_Param  param,
    const @xtype@    *argv,
    const isvd_int_t  argc,
          @xtype@    *retv,
    const isvd_int_t  retc,
          @xtype@    *yst,
    const isvd_int_t  ldyst
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

  // ====================================================================================================================== //
  // Allocate memory

  @xtype@ *yst_ = isvd_@x@malloc(mj * ldyst);
  isvd_int_t ldyst_ = ldyst;

  @xtype@ *w = isvd_@x@malloc(l * Nl);
  isvd_int_t ldw = l;

  @xtype@ *s = isvd_@x@malloc(l * N);
  isvd_int_t lds = l;

  // ====================================================================================================================== //
  // Orthogonalize

  // Wi := Yi' * Yi
  for ( isvd_int_t i = 0; i < N; ++i ) {
    isvd_@x@Gemm('N', 'T', l, l, mj, 1.0, yst + i*l, ldyst, yst + i*l, ldyst, 0.0, w + i*ldw*l, ldw);
  }
  MPI_Allreduce(MPI_IN_PLACE, w, ldw*Nl, MPI_@X_TYPE@, MPI_SUM, param.mpi_comm);

  // eig(Wi) = Wi * Si^2 * Wi'
  for ( isvd_int_t i = 0; i < N; ++i ) {
    isvd_@x@Gesvd('O', 'N', l, l, w + i*ldw*l, ldw, s + i*lds, nullptr, 1, nullptr, 1);
  }
  isvd_v@x@Sqrt(lds*N, s, s);

  // Qi := Yi * Wi / Si (Qi' := (Wi / Si)' * Yi' )
  for ( isvd_int_t ii = 0; ii < Nl; ++ii ) {
    isvd_@x@Scal(l, 1.0/s[ii], w + ii*ldw, 1);
  }
  isvd_@x@memcpy(yst_, yst, mj*ldyst);
  for ( isvd_int_t i = 0; i < N; ++i ) {
    isvd_@x@Gemm('T', 'N', l, mj, l, 1.0, w + i*ldw*l, ldw, yst_ + i*l, ldyst_, 0.0, yst + i*l, ldyst);
  }

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_free(yst_);
  isvd_free(w);
  isvd_free(s);

}
