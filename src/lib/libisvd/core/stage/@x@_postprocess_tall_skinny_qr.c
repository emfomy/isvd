////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/core/stage/@x@_postprocess_tall_skinny_qr.c
/// \brief      The Tall-Skinny QR Postprocessing (@xname@ precision).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/core/@x@_stage.h>
#include <libisvd/def.h>
#include <isvd/la.h>
#include <libisvd/core/stage/@x@_postprocess.h>
#include <libisvd/util/arg.h>
#include <libisvd/util/function.h>
#include <isvd/util/memory.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_@x@_stage_module
/// \brief  Tall-Skinny QR Postprocessing (@xname@ precision).
///
/// \attention  Not implemented!
///
/// \note  If \b argc < 0, then a default argument query is assumed;
///        the routine only returns the first \b retc default arguments in \b retv.
///
/// \see isvd_Param, \ref tutorial_core_notation
///
void isvd_@x@PostprocessTallSkinnyQr(
    const isvd_Param    param,
    const @xtype_____@ *argv,
    const isvd_int_t    argc,
          @xtype_____@ *retv,
    const isvd_int_t    retc,
    const char          dista,
    const char          ordera,
    const @xtype_____@ *a,
    const isvd_int_t    lda,
    const @xtype_____@ *qt,
    const isvd_int_t    ldqt,
          @xtype_____@ *s,
          @xtype_____@ *ut,
    const isvd_int_t    ldut,
          @xtype_____@ *vt,
    const isvd_int_t    ldvt,
    const mpi_int_t     ut_root,
    const mpi_int_t     vt_root
) {

  ISVD_UNUSED(argv);
  ISVD_UNUSED(retv);

  if ( argc > 0 ) { isvd_assert_ne(argv, nullptr); }
  if ( retc > 0 ) { isvd_assert_ne(retv, nullptr); }
  if ( argc < 0 ) return;

  // ====================================================================================================================== //
  // Get parameters

  const isvd_int_t mj  = param.nrow_proc;
  const isvd_int_t mb  = param.nrow_each;
  const isvd_int_t n   = param.ncol;
  const isvd_int_t nj  = param.ncol_proc;
  const isvd_int_t nb  = param.ncol_each;
  const isvd_int_t Pnb = param.ncol_total;
  const isvd_int_t k   = param.rank;
  const isvd_int_t l   = param.dim_sketch;
  const isvd_int_t l2  = 2*l;

  const isvd_int_t j   = param.mpi_rank;
  const isvd_int_t P   = param.mpi_size;

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

  isvd_assert_true(isPowerOf2(P));
  isvd_assert_ge(nj, l);
  isvd_assert_ge(n - (Pnb - nb), l);

  // ====================================================================================================================== //
  // Allocate memory

  // matrix Z'
  @xtype_____@ *zt = isvd_@x@malloc(l * nb);
  isvd_int_t ldzt = l;

  // matrix Qc'
  @xtype_____@ *qct = isvd_@x@malloc(l * l2);
  isvd_int_t ldqct = l;

  // matrix Q+'
  @xtype_____@ *qpt = isvd_@x@malloc(l * l2);
  isvd_int_t ldqpt = l;

  // matrix Pc'
  @xtype_____@ *pct = NULL;
  if ( vt_root >= -1 ) {
    pct = isvd_@x@malloc(l * l);
  }
  isvd_int_t ldpct = l;

  // matrix P-'
  @xtype_____@ *pmt = NULL;
  if ( vt_root >= -1 ) {
    pmt = isvd_@x@malloc(l * l);
  }
  isvd_int_t ldpmt = l;

  // vector Tau
  @xtype_____@ *tau = s;

  // matrix R'
  @xtype_____@ *rtj;
  @xtype_____@ *rtjj;
  isvd_int_t ldrt = ldqpt;

  @xtype_____@ *qctj;

  @xtype_____@ *tmp;

  isvd_int_t jj;
  MPI_Status mpi_status;

  // ====================================================================================================================== //
  // Projection

  switch ( dista_ ) {
    case 'C': projectBlockCol(param, ordera_, a, lda, qt, ldqt, zt, ldzt, s, ut, ldut, ut_root); break;
    case 'R': projectBlockRow(param, ordera_, a, lda, qt, ldqt, zt, ldzt, s, vt, ldvt, vt_root); break;
    default:  isvd_assert_fail();
  }

  // ====================================================================================================================== //
  // First level

  // Get neighbor ID
  jj = j ^ 0x1;
  rtj  = (j < jj) ? qpt : qpt + ldqpt*l;
  rtjj = (j < jj) ? qpt + ldqpt*l : qpt;

  // Z * Rc = qr(Z)
  isvd_@x@Gelqf(l, nj, zt, ldzt, tau);

  // Copy Rc
  isvd_@x@memset0(rtj, ldrt * l);
  isvd_@x@Lacpy('L', l, l, zt, ldzt, rtj, ldrt);

  // Form Z
  if ( vt_root >= -1 ) {
    isvd_@x@Orglq(l, nj, l, zt, ldzt, tau);
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

    // Qc * Rc = qr(Qc)
    isvd_@x@Gelqf(l, l2, qct, ldqct, tau);

    // Copy Rc
    isvd_@x@memset0(rtj, ldrt * l);
    isvd_@x@Lacpy('L', l, l, qct, ldqct, rtj, ldrt);

    if ( vt_root >= -1 ) {
      // Form Qc
      isvd_@x@Orglq(l, l2, l, qct, ldqct, tau);

      // Pc := P- * Qcj (Pc' := Qcj' * P-')
      if ( t != 0x2 ) {
        isvd_@x@Gemm('N', 'N', l, l, l, 1.0, qctj, ldqct, pmt, ldpmt, 0.0, pct, ldpct);
      } else {
        isvd_@x@memcpy(pct, qctj, ldpct*l);
      }
    }
  }

  // ====================================================================================================================== //
  // Last level

  // svd(R) = W[in R] * S * T' (svd(R') = T * S * W')
  @xtype_____@ *wt = rtj;
  isvd_int_t ldwt = ldrt;
  @xtype_____@ *tt = qct;
  isvd_int_t ldtt = ldqct;
  const char jobwt_ = (ut_root >= -1) ? 'O' : 'N';
  const char jobtt_ = (vt_root >= -1) ? 'S' : 'N';
  isvd_@x@Gesvd(jobtt_, jobwt_, l, l, wt, ldwt, s, tt, ldtt, NULL, 1);

  // ====================================================================================================================== //
  // Compute singular vectors

  if ( ut_root >= -1 ) {
    // U := Q * W[in R] (U' := W[in R]' * Q')
    isvd_@x@Gemm('N', 'N', k, mj, l, 1.0, wt, ldwt, qt, ldqt, 0.0, ut, ldut);

    if ( ut_root >= 0 ) {
      if ( param.mpi_rank == ut_root ) {
        isvd_assert_pass(MPI_Gather(MPI_IN_PLACE, mb*ldut, MPI_@XTYPE@, ut, mb*ldut, MPI_@XTYPE@, ut_root, param.mpi_comm));
      } else {
        isvd_assert_pass(MPI_Gather(ut, mb*ldut, MPI_@XTYPE@, NULL, mb*ldut, MPI_@XTYPE@, ut_root, param.mpi_comm));
      }
    }
  }

  if ( vt_root >= -1 ) {
    // V := Z * Pc * T (V' := T' * Pc' * Z')
    if ( P > 1 ) {
      isvd_@x@Gemm('N', 'N', l, l, l, 1.0, tt, ldtt, pct, ldpct, 0.0, pmt, ldpmt);
      isvd_@x@Gemm('N', 'N', l, nj, l, 1.0, pmt, ldpmt, zt, ldzt, 0.0, vt, ldvt);
    } else {
      isvd_@x@Gemm('N', 'N', l, nj, l, 1.0, tt, ldtt, zt, ldzt, 0.0, vt, ldvt);
    }

    if ( vt_root >= 0 ) {
      if ( param.mpi_rank == vt_root ) {
        isvd_assert_pass(MPI_Gather(MPI_IN_PLACE, nb*ldvt, MPI_@XTYPE@, vt, nb*ldvt, MPI_@XTYPE@, vt_root, param.mpi_comm));
      } else {
        isvd_assert_pass(MPI_Gather(vt, nb*ldvt, MPI_@XTYPE@, NULL, nb*ldvt, MPI_@XTYPE@, vt_root, param.mpi_comm));
      }
    }
  }

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_free(zt);
  isvd_free(qct);
  isvd_free(qpt);
  if ( vt_root >= -1 ) {
    isvd_free(pct);
    isvd_free(pmt);
  }

}
