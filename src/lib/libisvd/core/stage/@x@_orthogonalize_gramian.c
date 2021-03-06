////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/core/stage/@x@_orthogonalize_gramian.c
/// \brief      The Gramian Orthogonalization (@xname@ precision).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/core/@x@_stage.h>
#include <libisvd/def.h>
#include <isvd/la.h>
#include <isvd/util/memory.h>
#include <isvd/util/mpi.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_stage_module
/// \brief  Gramian Orthogonalization (@xname@ precision).
///
/// \param[in]   param       The \ref isvd_Param "parameters".
/// \param[in]   argv, argc  The arguments and its length. (not using)
/// \param[in]   retv, retc  The return values and its length. (not using)
/// <hr>
/// \param[in]   yst, ldyst  The row-block 𝖄 (\f$ m_b \times Nl \f$, row-major) and its leading dimension.
/// <hr>
/// \param[out]  yst         Replaced by the row-block 𝕼 (row-major).
///
/// \note  If \b argc < 0, then a default argument query is assumed;
///        the routine only returns the first \b retc default arguments in \b retv.
///
/// \see isvd_Param, \ref tutorial_core_notation
///
void isvd_@x@OrthogonalizeGramian(
    const isvd_Param   param,
    const @xtype_____@ *argv,
    const isvd_int_t   argc,
          @xtype_____@ *retv,
    const isvd_int_t   retc,
          @xtype_____@ *yst,
    const isvd_int_t   ldyst
) {

  ISVD_UNUSED(argv);
  ISVD_UNUSED(retv);

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

  // ====================================================================================================================== //
  // Allocate memory

  // matrix Y'
  @xtype_____@ *yst_ = isvd_@x@Malloc(ldyst * mj);
  isvd_int_t ldyst_ = ldyst;

  // matrix W'
  @xtype_____@ *w = isvd_@x@Malloc(l * Nl);
  isvd_int_t ldw = l;

  // matrix S
  @xtype_____@ *s = isvd_@x@Malloc(l * N);
  isvd_int_t lds = l;

  // ====================================================================================================================== //
  // Orthogonalize

  // Wi := Yi' * Yi
  for ( isvd_int_t i = 0; i < N; ++i ) {
    isvd_@x@Gemm('N', 'T', l, l, mj, 1.0, yst + i*l, ldyst, yst + i*l, ldyst, 0.0, w + i*ldw*l, ldw);
  }
  isvd_assert_pass(MPI_Allreduce(MPI_IN_PLACE, w, ldw*Nl, MPI_@XTYPE@, MPI_SUM, param.mpi_comm));

  // eig(Wi) = Wi * Si^2 * Wi'
  for ( isvd_int_t i = 0; i < N; ++i ) {
    isvd_@x@Gesvd('O', 'N', l, l, w + i*ldw*l, ldw, s + i*lds, NULL, 1, NULL, 1);
  }
  isvd_v@x@Sqrt(lds*N, s, s);

  // Qi := Yi * Wi / Si (Qi' := (Wi / Si)' * Yi' )
  isvd_@x@Dism('R', l, Nl, 1.0, s, w, ldw);
  isvd_@x@Memcpy(yst_, yst, mj*ldyst);
  for ( isvd_int_t i = 0; i < N; ++i ) {
    isvd_@x@Gemm('T', 'N', l, mj, l, 1.0, w + i*ldw*l, ldw, yst_ + i*l, ldyst_, 0.0, yst + i*l, ldyst);
  }

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_Free(yst_);
  isvd_Free(w);
  isvd_Free(s);

}
