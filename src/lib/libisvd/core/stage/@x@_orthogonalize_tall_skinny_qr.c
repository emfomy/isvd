////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/core/stage/@x@_orthogonalize_tall_skinny_qr.c
/// \brief      The Tall-Skinny QR Orthogonalization (@xname@ precision).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/core/@x@_stage.h>
#include <libisvd/def.h>
#include <isvd/la.h>
#include <libisvd/util/function.h>
#include <isvd/util/memory.h>
#include <isvd/util/mpi.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_stage_module
/// \brief  Tall-Skinny QR Orthogonalization (@xname@ precision).
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
/// \attention  The number of MPI processes \f$P\f$ should be a power of 2.
///
/// \see isvd_Param, \ref tutorial_core_notation
///
void isvd_@x@OrthogonalizeTallSkinnyQr(
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

  const isvd_int_t m   = param.nrow;
  const isvd_int_t mj  = param.nrow_proc;
  const isvd_int_t mb  = param.nrow_each;
  const isvd_int_t Pmb = param.nrow_total;
  const isvd_int_t l   = param.dim_sketch;
  const isvd_int_t N   = param.num_sketch;
  const isvd_int_t Nl  = param.dim_sketch_total;
  const isvd_int_t l2  = 2*l;

  const isvd_int_t j   = param.mpi_rank;
  const isvd_int_t P   = param.mpi_size;

  ISVD_UNUSED(m);
  ISVD_UNUSED(mb);
  ISVD_UNUSED(Pmb);

  // ====================================================================================================================== //
  // Check arguments

  isvd_assert_true(isPowerOf2(P));
  isvd_assert_ge(ldyst, Nl);
  isvd_assert_ge(mj, l);
  isvd_assert_ge(m - (Pmb - mb), l);

  // ====================================================================================================================== //
  // Allocate memory

  // matrix Y'
  @xtype_____@ *yst_ = isvd_@x@Malloc(ldyst * mj);
  isvd_int_t ldyst_ = ldyst;

  // matrix Qc'
  @xtype_____@ *qct = isvd_@x@Malloc(Nl * l2);
  isvd_int_t ldqct = Nl;

  // matrix Q+'
  @xtype_____@ *qpt = isvd_@x@Malloc(Nl * l2);
  isvd_int_t ldqpt = Nl;

  // matrix Pc'
  @xtype_____@ *pct = isvd_@x@Malloc(Nl * l);
  isvd_int_t ldpct = Nl;

  // matrix P-'
  @xtype_____@ *pmt = isvd_@x@Malloc(Nl * l);
  isvd_int_t ldpmt = Nl;

  // matrix Tau
  @xtype_____@ *tau = isvd_@x@Malloc(l * N);
  isvd_int_t ldtau = l;

  // matrix R'
  @xtype_____@ *rtj;
  @xtype_____@ *rtjj;
  isvd_int_t ldrt = ldqpt;

  @xtype_____@ *qctj;

  @xtype_____@ *tmp;

  isvd_int_t jj;
  MPI_Status mpi_status;

  // ====================================================================================================================== //
  // First level

  // Get neighbor ID
  jj = j ^ 0x1;
  rtj  = (j < jj) ? qpt : qpt + ldqpt*l;
  rtjj = (j < jj) ? qpt + ldqpt*l : qpt;

  // Yi * Ric = qr(Yi)
  for ( isvd_int_t i = 0; i < N; ++i ) {
    isvd_@x@Gelqf(l, mj, yst + i*l, ldyst, tau + i*ldtau);
  }

  // Copy Ric
  if ( P > 1 ) {
    isvd_@x@Memset0(rtj, ldrt * l);
    for ( isvd_int_t i = 0; i < N; ++i ) {
      isvd_@x@Lacpy('L', l, l, yst + i*l, ldyst, rtj + i*l, ldrt);
    }
  }

  // Form Yi
  for ( isvd_int_t i = 0; i < N; ++i ) {
    isvd_@x@Orglq(l, mj, l, yst + i*l, ldyst, tau + i*ldtau);
  }

  // ====================================================================================================================== //
  // Iterating
  for ( isvd_int_t t = 0x2; t <= P; t <<= 1 ) {

    // Swap
    tmp = qct; qct = qpt; qpt = tmp;
    tmp = pct; pct = pmt; pmt = tmp;

    // Combine R- into Qc
    isvd_assert_pass(MPI_Sendrecv(rtj,  ldrt * l, MPI_@XTYPE@, jj, j,
                                  rtjj, ldrt * l, MPI_@XTYPE@, jj, jj, param.mpi_comm, &mpi_status));

    // Update neighbor ID
    qctj = (j < jj) ? qct : qct + ldqct*l;
    jj = j ^ t;
    rtj  = (j < jj) ? qpt : qpt + ldqpt*l;
    rtjj = (j < jj) ? qpt + ldqpt*l : qpt;

    // Qic * Ric = qr(Qic)
    for ( isvd_int_t i = 0; i < N; ++i ) {
      isvd_@x@Gelqf(l, l2, qct + i*l, ldqct, tau + i*ldtau);
    }

    // Copy Ric
    if ( t != P ) {
      isvd_@x@Memset0(rtj, ldrt * l);
      for ( isvd_int_t i = 0; i < N; ++i ) {
        isvd_@x@Lacpy('L', l, l, qct + i*l, ldqct, rtj + i*l, ldrt);
      }
    }

    // Form Qic
    for ( isvd_int_t i = 0; i < N; ++i ) {
      isvd_@x@Orglq(l, l2, l, qct + i*l, ldqct, tau + i*ldtau);
    }

    // Pic := Pi- * Qicj (Pic' := Qicj' * Pi-')
    if ( t != 0x2 ) {
      for ( isvd_int_t i = 0; i < N; ++i ) {
        isvd_@x@Gemm('N', 'N', l, l, l, 1.0, qctj + i*l, ldqct, pmt + i*l, ldpmt, 0.0, pct + i*l, ldpct);
      }
    } else {
      isvd_@x@Memcpy(pct, qctj, ldpct*l);
    }
  }

  // ====================================================================================================================== //
  // Multiplication

  // Yi *= Pi (Yi' := Pi' * Yi')
  if ( P > 1 ) {
    for ( isvd_int_t i = 0; i < N; ++i ) {
      isvd_@x@Gemm('N', 'N', l, mj, l, 1.0, pct + i*l, ldpct, yst + i*l, ldyst, 0.0, yst_ + i*l, ldyst_);
    }
    isvd_@x@Memcpy(yst, yst_, ldyst*mj);
  }

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_Free(yst_);
  isvd_Free(qct);
  isvd_Free(qpt);
  isvd_Free(pct);
  isvd_Free(pmt);
  isvd_Free(tau);

}
