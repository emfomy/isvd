////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/core/stage/@x@_integrate_wen_yin.c
/// \brief      The Wen-Yin Integration (@xname@ precision).
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

#define kMaxit    256
#define kTol      1e-3
#define kTau0     1.0
#define kTaumax   1e14
#define kTaumin   1e-14
#define kTauMaxit 20
#define kBeta     0.5
#define kSigma    1e-4
#define kEta      0.85

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_stage_module
/// \brief  Wen-Yin Integration (@xname@ precision).
///
/// \param[in]   param       The \ref isvd_Param "parameters".
/// \param[in]   argv, argc  The arguments and its length. <br>
///                          \b argv[0]: The maximum number of iteration. <br>
///                          \b argv[1]: The tolerance of convergence condition. <br>
///                          \b argv[2]: The initial step size \f$ \tau_0 \f$. <br>
///                          \b argv[3]: The maximum predicting step size \f$ \tau_\max \f$. <br>
///                          \b argv[4]: The minimum predicting step size \f$ \tau_\min \f$. <br>
///                          \b argv[5]: The maximum number of iteration in predicting step size. <br>
///                          \b argv[6]: The scaling parameter for step size searching \f$ \beta \f$. <br>
///                          \b argv[7]: The parameter for step size searching \f$ \sigma \f$. <br>
///                          \b argv[8]: The parameter for next step searching \f$ \eta \f$.
/// \param[in]   retv, retc  The return values and its length.
/// <hr>
/// \param[in]   yst, ldyst  The row-block 𝕼 (\f$ m_b \times Nl \f$, row-major) and its leading dimension.
/// \param[in]   qt, ldqt    The row-block 𝑸 (\f$ m_b \times l \f$, row-major) and its leading dimension.
/// <hr>
/// \param[out]  retv        Replaced by return values. <br>
///                          \b retv[0]: The number of iteration. <br>
///                          \b retv[1]: The error.
/// \param[out]  qt          Replaced by the row-block 𝑸 (row-major).
///
/// \note  If \b argc < 0, then a default argument query is assumed;
///        the routine only returns the first \b retc default arguments in \b retv.
///
/// \see isvd_Param, \ref tutorial_core_notation
///
void isvd_@x@IntegrateWenYin(
    const isvd_Param   param,
    const @xtype_____@ *argv,
    const isvd_int_t   argc,
          @xtype_____@ *retv,
    const isvd_int_t   retc,
    const @xtype_____@ *yst,
    const isvd_int_t   ldyst,
          @xtype_____@ *qt,
    const isvd_int_t   ldqt
) {

  if ( argc > 0 ) { isvd_assert_ne(argv, nullptr); }
  if ( retc > 0 ) { isvd_assert_ne(retv, nullptr); }

  // ====================================================================================================================== //
  // Query arguments

  if ( argc < 0 ) {
    isvd_int_t argi = -1;
    if ( retc > ++argi ) retv[argi] = kMaxit;
    if ( retc > ++argi ) retv[argi] = kTol;
    if ( retc > ++argi ) retv[argi] = kTau0;
    if ( retc > ++argi ) retv[argi] = kTaumax;
    if ( retc > ++argi ) retv[argi] = kTaumin;
    if ( retc > ++argi ) retv[argi] = kTauMaxit;
    if ( retc > ++argi ) retv[argi] = kBeta;
    if ( retc > ++argi ) retv[argi] = kSigma;
    if ( retc > ++argi ) retv[argi] = kEta;
    return;
  }

  // ====================================================================================================================== //
  // Get arguments

  isvd_int_t argi = -1;
  const isvd_int_t   maxit    = (argc > ++argi) ? argv[argi] : kMaxit;
  const @xtype_____@ tol      = (argc > ++argi) ? argv[argi] : kTol;
  const @xtype_____@ tau0     = (argc > ++argi) ? argv[argi] : kTau0;
  const @xtype_____@ taumax   = (argc > ++argi) ? argv[argi] : kTaumax;
  const @xtype_____@ taumin   = (argc > ++argi) ? argv[argi] : kTaumin;
  const isvd_int_t   taumaxit = (argc > ++argi) ? argv[argi] : kTauMaxit;
  const @xtype_____@ beta     = (argc > ++argi) ? argv[argi] : kBeta;
  const @xtype_____@ sigma    = (argc > ++argi) ? argv[argi] : kSigma;
  const @xtype_____@ eta      = (argc > ++argi) ? argv[argi] : kEta;

  // ====================================================================================================================== //
  // Get parameters

  const isvd_int_t mj = param.nrow_proc;
  const isvd_int_t l  = param.dim_sketch;
  const isvd_int_t N  = param.num_sketch;
  const isvd_int_t Nl = param.dim_sketch_total;
  const isvd_int_t l2 = 2*l;

  // ====================================================================================================================== //
  // Check arguments
  isvd_assert_ge(ldyst, Nl);
  isvd_assert_ge(ldqt, l);
  isvd_assert_ge(maxit, 0);
  isvd_assert_ge(tol, 0);
  isvd_assert_ge(tau0, 0);
  isvd_assert_ge(taumax, 0);
  isvd_assert_ge(taumin, 0);
  isvd_assert_ge(taumaxit, 0);
  isvd_assert_gtlt(beta, 0, 1);
  isvd_assert_gtlt(sigma, 0, 1);
  isvd_assert_gtlt(eta, 0, 1);

  // ====================================================================================================================== //
  // Allocate memory

  // matrix Q'
  const @xtype_____@ *qst = yst;
  isvd_int_t ldqst = ldyst;

  // matrix Qc'
  @xtype_____@ *qct = isvd_@x@Malloc(l * mj);
  isvd_int_t ldqct = l;

  // matrix Q+'
  @xtype_____@ *qpt = isvd_@x@Malloc(l * mj);
  isvd_int_t ldqpt = l;

  // matrix Gc'
  @xtype_____@ *gct = isvd_@x@Malloc(l * mj);
  isvd_int_t ldgct = l;

  // matrix Xc'
  @xtype_____@ *xct = isvd_@x@Malloc(l * mj);
  isvd_int_t ldxct = l;

  // matrix X+'
  @xtype_____@ *xpt = isvd_@x@Malloc(l * mj);
  isvd_int_t ldxpt = l;

  // matrix Bc
  @xtype_____@ *bc = isvd_@x@Malloc(Nl * l);
  isvd_int_t ldbc = Nl;

  // matrix B+
  @xtype_____@ *bp = isvd_@x@Malloc(Nl * l);
  isvd_int_t ldbp = Nl;

  // matrix Bgc
  @xtype_____@ *bgc = isvd_@x@Malloc(Nl * l);
  isvd_int_t ldbgc = Nl;

  // matrix Dc
  @xtype_____@ *dc = isvd_@x@Malloc(l * l);
  isvd_int_t lddc = l;

  // matrix Dgc
  @xtype_____@ *dgc = isvd_@x@Malloc(l * l);
  isvd_int_t lddgc = l;

  // matrix C & inv(C)
  @xtype_____@ *c = isvd_@x@Malloc(l2 * l2);
  isvd_int_t ldc = l2;

  // matrix inv(C)_??
  @xtype_____@ *c11 = c;
  @xtype_____@ *c21 = c + l;
  @xtype_____@ *c12 = c + ldc*l;
  @xtype_____@ *c22 = c + l + ldc*l;

  // matrix inv(C)_#?
  @xtype_____@ *cs1 = c11;
  @xtype_____@ *cs2 = c12;

  // matrix Fc
  @xtype_____@ *fc = c21;
  isvd_int_t ldfc = ldc;

  // matrix Fgc
  @xtype_____@ *fgc = c11;
  isvd_int_t ldfgc = ldc;

  @xtype_____@ *tmp;

  @xtype_____@ taug, zeta, phi, mu;

  // ====================================================================================================================== //
  // Initializing

  // Qc := Q0
  isvd_@x@Omatcopy('N', l, mj, 1.0, qst, ldqst, qct, ldqct);

  // Bc := Qs' * Qc
  isvd_@x@Gemm('N', 'T', Nl, l, mj, 1.0, qst, ldqst, qct, ldqct, 0.0, bc, ldbc);
  isvd_assert_pass(MPI_Allreduce(MPI_IN_PLACE, bc, ldbc*l, MPI_@XTYPE@, MPI_SUM, param.mpi_comm));

  // Dc := 1/N * Bc' * Bc
  isvd_@x@Gemm('T', 'N', l, l, Nl, 1.0/N, bc, ldbc, bc, ldbc, 0.0, dc, lddc);

  // Gc := 1/N * Qs * Bc (Gc' := 1/N * Bc' * Qs')
  isvd_@x@Gemm('T', 'N', l, mj, Nl, 1.0/N, bc, ldbc, qst, ldqst, 0.0, gct, ldgct);

  // Bgc := Qs' * Gc
  isvd_@x@Gemm('N', 'T', Nl, l, mj, 1.0, qst, ldqst, gct, ldgct, 0.0, bgc, ldbgc);
  isvd_assert_pass(MPI_Allreduce(MPI_IN_PLACE, bgc, ldbgc*l, MPI_@XTYPE@, MPI_SUM, param.mpi_comm));

  // Dgc := 1/N * Bc' * Bgc
  isvd_@x@Gemm('T', 'N', l, l, Nl, 1.0/N, bc, ldbc, bgc, ldbgc, 0.0, dgc, lddgc);

  // Xc := Gc - Qc * Dc (Xc' := Gc' - Dc' * Qc')
  isvd_@x@Memcpy(xct, gct, mj * l);
  isvd_@x@Gemm('T', 'N', l, mj, l, -1.0, dc, lddc, qct, ldqct, 1.0, xct, ldxct);

  // mu := tr( Dgc ) - norm( Dc )_F^2
  mu = isvd_@x@Asum(l, dgc, lddgc+1) - isvd_@x@Dot(lddc*l, dc, 1, dc, 1);

  // taug := tau0; zeta := 1; phi := 1/2N * norm( Bc )_F^2
  taug = tau0;
  zeta = 1.0;
  phi = 0.5/N * isvd_@x@Dot(ldbc*l, bc, 1, bc, 1);

  // ====================================================================================================================== //
  // Iterating

  isvd_int_t iter;

  for ( iter = 1; ; ++iter ) {

    // ================================================================================================================== //
    // Find step size
    @xtype_____@ tau = taug, phit = phi;
    for ( isvd_int_t tauiter = 1; tauiter <= taumaxit; ++tauiter, tau *= beta ) {

      // C := [ Dc/2 - I/tau , I/2          ;
      //       -Dgc/2,        -Dc/2 - I/tau ]
      isvd_@x@Memset0(c, ldc*l2);
      isvd_@x@Omatcopy('N', l, l,  0.5, dc,  lddc,  c11, ldc);
      isvd_@x@Omatcopy('N', l, l, -0.5, dgc, lddgc, c21, ldc);
      isvd_@x@Omatcopy('N', l, l, -0.5, dc,  lddc,  c22, ldc);
      for ( isvd_int_t ii = 0; ii < l; ++ii ) {
        c11[ii+ldc*ii] -= 1.0/tau;
      }
      for ( isvd_int_t ii = 0; ii < l; ++ii ) {
        c12[ii+ldc*ii] += 0.5;
      }
      for ( isvd_int_t ii = 0; ii < l; ++ii ) {
        c22[ii+ldc*ii] -= 1.0/tau;
      }

      // Compute inv(C)
      isvd_@x@Geinv(l2, c, ldc);

      // Fc  [in C_21] := I + inv(C)_22 * Dc - inv(C)_21
      // Fgc [in C_11] :=     inv(C)_12 * Dc - inv(C)_21
      isvd_@x@Gemm('N', 'N', l2, l, l, 1.0, cs2, ldc, dc, lddc, -1.0, cs1, ldc);
      for ( isvd_int_t ii = 0; ii < l; ++ii ) {
        c21[ii+ldc*ii] += 1.0;
      }

      // B+ := Bc * Fc + Bgc * Fgc
      isvd_@x@Gemm('N', 'N', Nl, l, l, 1.0, bc,  ldbc,  fc,  ldfc,  0.0, bp, ldbp);
      isvd_@x@Gemm('N', 'N', Nl, l, l, 1.0, bgc, ldbgc, fgc, ldfgc, 1.0, bp, ldbp);

      // ~phi := 1/2N * norm( B+ )_F^2
      phit = 0.5/N * isvd_@x@Dot(ldbp*l, bp, 1, bp, 1);

      // Check condition
      if ( phit >= phi + tau * sigma * mu ) {
        break;
      }
    }

    // ================================================================================================================== //
    // Update for next iteration

    // Update phi and zeta
    phi = (eta * zeta * phi + phit) / (eta * zeta + 1);
    zeta = eta * zeta + 1;

    // Q+ := Qc * Fc + Gc * Fgc (Q+' := Fc' * Qc' + Fgc' * Gc')
    isvd_@x@Gemm('T', 'N', l, mj, l, 1.0, fc,  ldfc,  qct, ldqct, 0.0, qpt, ldqpt);
    isvd_@x@Gemm('T', 'N', l, mj, l, 1.0, fgc, ldfgc, gct, ldgct, 1.0, qpt, ldqpt);

    // D+ [in Dc] := 1/N * B+' * B+
    isvd_@x@Gemm('T', 'N', l, l, Nl, 1.0/N, bp, ldbp, bp, ldbp, 0.0, dc, lddc);

    // G+ [in Gc] := 1/N * Qs * B+ (G+'[in Gc'] := 1/N * B+' * Qs')
    isvd_@x@Gemm('T', 'N', l, mj, Nl, 1.0/N, bp, ldbp, qst, ldqst, 0.0, gct, ldgct);

    // Bg+ [in Bgc] := Qs' * G+ [in Gc]
    isvd_@x@Gemm('N', 'T', Nl, l, mj, 1.0, qst, ldqst, gct, ldgct, 0.0, bgc, ldbgc);
    isvd_assert_pass(MPI_Allreduce(MPI_IN_PLACE, bgc, ldbgc*l, MPI_@XTYPE@, MPI_SUM, param.mpi_comm));

    // Dg+ [in Dgc] := 1/N * B+' * Bg+ [in Bgc]
    isvd_@x@Gemm('T', 'N', l, l, Nl, 1.0/N, bp, ldbp, bgc, ldbgc, 0.0, dgc, lddgc);

    // mu := tr( Dg+ [in Dgc] ) - norm( D+ [in Dc] )_F^2
    mu = isvd_@x@Asum(l, dgc, lddgc+1) - isvd_@x@Dot(lddc*l, dc, 1, dc, 1);

    // ================================================================================================================== //
    // Check convergence: mu < tol^2

    if ( mu < tol * tol ) {
      break;
    }

    if ( iter == maxit ) {
      ++iter;
      break;
    }

    // ================================================================================================================== //
    // Update taug

    // X+ := G+ [in Gc] - Q+ * D+ [in Dc]
    isvd_@x@Memcpy(xpt, gct, mj * l);
    isvd_@x@Gemm('T', 'N', l, mj, l, -1.0, dc, lddc, qpt, ldqpt, 1.0, xpt, ldxpt);

    // Delta1 [in Qc] := Qc - Q+; Delta2 [in Xc] := Xc - X+
    isvd_v@x@Sub(mj*ldqct, qct, qpt, qct);
    isvd_v@x@Sub(mj*ldxct, xct, xpt, xct);

    // Update taug
    @xtype_____@ t[2];

    if ( iter % 2 ) {
      t[0] = isvd_@x@Dot(mj*ldqct, qct, 1, qct, 1);
      t[1] = isvd_@x@Dot(mj*ldqct, qct, 1, xct, 1);
    } else {
      t[0] = isvd_@x@Dot(mj*ldxct, xct, 1, qct, 1);
      t[1] = isvd_@x@Dot(mj*ldxct, xct, 1, xct, 1);
    }

    isvd_assert_pass(MPI_Allreduce(MPI_IN_PLACE, t, 2, MPI_@XTYPE@, MPI_SUM, param.mpi_comm));

    taug = fabs(t[0]/t[1]);
    if ( taug < taumin ) { taug = taumin; }
    if ( taug > taumax ) { taug = taumax; }

    // ================================================================================================================== //
    // Swap
    tmp = qct; qct = qpt; qpt = tmp;
    tmp = xct; xct = xpt; xpt = tmp;
    tmp = bc;  bc  = bp;  bp  = tmp;
  }

  // Swap
  tmp = qct; qct = qpt; qpt = tmp;

  // Copy Qbar
  isvd_@x@Omatcopy('N', l, mj, 1.0, qct, ldqct, qt, ldqt);

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_Free(qct);
  isvd_Free(qpt);
  isvd_Free(gct);
  isvd_Free(xct);
  isvd_Free(xpt);
  isvd_Free(bc);
  isvd_Free(bp);
  isvd_Free(bgc);
  isvd_Free(dc);
  isvd_Free(dgc);
  isvd_Free(c);

  // ====================================================================================================================== //
  // Set return values

  isvd_int_t reti = -1;
  if ( retc > ++reti ) retv[reti] = iter;
  if ( retc > ++reti ) retv[reti] = mu;

}
