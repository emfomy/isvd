////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/core/stage/@x@_integrate_wen_yin.c
/// \brief      The Wen-Yin Integration (@xname@ precision)
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/core/@x@_stage.h>
#include <libisvd/def.h>
#include <isvd/la.h>
#include <libisvd/util/memory.h>

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
/// \ingroup  c_core_@x@_stage_module
/// Wen-Yin Integration (@xname@ precision)
///
/// \param[in]   param       The \ref isvd_Param "parameters".
/// \param[in]   argv, argc  The arguments and its length. <br>
///                          \b argv[0]: The maximum number of iteration. (optional, default as \ref kMaxit) <br>
///                          \b argv[1]: The tolerance of convergence condition. (optional, default as \ref kTol)
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
void isvd_@x@IntegrateWenYin(
    const isvd_Param  param,
    const @xtype@    *argv,
    const isvd_int_t  argc,
          @xtype@    *retv,
    const isvd_int_t  retc,
    const @xtype@    *yst,
    const isvd_int_t  ldyst,
          @xtype@    *qt,
    const isvd_int_t  ldqt
) {

  // ====================================================================================================================== //
  // Get arguments

  isvd_int_t argi = -1;
  const isvd_int_t maxit    = ( argc > ++argi ) ? argv[argi] : kMaxit;
  const @xtype@ tol         = ( argc > ++argi ) ? argv[argi] : kTol;
  const @xtype@ tau0        = ( argc > ++argi ) ? argv[argi] : kTau0;
  const @xtype@ taumax      = ( argc > ++argi ) ? argv[argi] : kTaumax;
  const @xtype@ taumin      = ( argc > ++argi ) ? argv[argi] : kTaumin;
  const isvd_int_t taumaxit = ( argc > ++argi ) ? argv[argi] : kTauMaxit;
  const @xtype@ beta        = ( argc > ++argi ) ? argv[argi] : kBeta;
  const @xtype@ sigma       = ( argc > ++argi ) ? argv[argi] : kSigma;
  const @xtype@ eta         = ( argc > ++argi ) ? argv[argi] : kEta;

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

  const @xtype@ *qst = yst;
  isvd_int_t ldqst = ldyst;

  // matrix Qc'
  @xtype@ *qct = isvd_@x@malloc(l * mj);
  isvd_int_t ldqct = l;

  // matrix Q+'
  @xtype@ *qpt = isvd_@x@malloc(l * mj);
  isvd_int_t ldqpt = l;

  // matrix Gc'
  @xtype@ *gct = isvd_@x@malloc(l * mj);
  isvd_int_t ldgct = l;

  // matrix Xc'
  @xtype@ *xct = isvd_@x@malloc(l * mj);
  isvd_int_t ldxct = l;

  // matrix X+'
  @xtype@ *xpt = isvd_@x@malloc(l * mj);
  isvd_int_t ldxpt = l;

  // matrix Bc
  @xtype@ *bc = isvd_@x@malloc(Nl * l);
  isvd_int_t ldbc = Nl;

  // matrix B+
  @xtype@ *bp = isvd_@x@malloc(Nl * l);
  isvd_int_t ldbp = Nl;

  // matrix Bgc
  @xtype@ *bgc = isvd_@x@malloc(Nl * l);
  isvd_int_t ldbgc = Nl;

  // matrix Dc
  @xtype@ *dc = isvd_@x@malloc(l * l);
  isvd_int_t lddc = l;

  // matrix Dgc
  @xtype@ *dgc = isvd_@x@malloc(l * l);
  isvd_int_t lddgc = l;

  // matrix C & inv(C)
  @xtype@ *c = isvd_@x@malloc(l2 * l2);
  isvd_int_t ldc = l2;

  // matrix inv(C)_??
  @xtype@ *c11 = c;
  @xtype@ *c21 = c + l;
  @xtype@ *c12 = c + ldc*l;
  @xtype@ *c22 = c + l + ldc*l;

  // matrix inv(C)_#?
  @xtype@ *cs1 = c11;
  @xtype@ *cs2 = c12;

  // matrix Fc
  @xtype@ *fc = c21;
  isvd_int_t ldfc = ldc;

  // matrix Fgc
  @xtype@ *fgc = c11;
  isvd_int_t ldfgc = ldc;

  @xtype@ *tmp;

  @xtype@ taug, zeta, phi, mu;

  // ====================================================================================================================== //
  // Initializing

  // Qc := Q0
  isvd_@x@Omatcopy('N', l, mj, 1.0, qst, ldqst, qct, ldqct);

  // Bc := Qs' * Qc
  isvd_@x@Gemm('N', 'T', Nl, l, mj, 1.0, qst, ldqst, qct, ldqct, 0.0, bc, ldbc);
  MPI_Allreduce(MPI_IN_PLACE, bc, ldbc*l, MPI_@X_TYPE@, MPI_SUM, param.mpi_comm);

  // Dc := 1/N * Bc' * Bc
  isvd_@x@Gemm('T', 'N', l, l, Nl, 1.0/N, bc, ldbc, bc, ldbc, 0.0, dc, lddc);

  // Gc := 1/N * Qs * Bc (Gc' := 1/N * Bc' * Qs')
  isvd_@x@Gemm('T', 'N', l, mj, Nl, 1.0/N, bc, ldbc, qst, ldqst, 0.0, gct, ldgct);

  // Bgc := Qs' * Gc
  isvd_@x@Gemm('N', 'T', Nl, l, mj, 1.0, qst, ldqst, gct, ldgct, 0.0, bgc, ldbgc);
  MPI_Allreduce(MPI_IN_PLACE, bgc, ldbgc*l, MPI_@X_TYPE@, MPI_SUM, param.mpi_comm);

  // Dgc := 1/N * Bc' * Bgc
  isvd_@x@Gemm('T', 'N', l, l, Nl, 1.0/N, bc, ldbc, bgc, ldbgc, 0.0, dgc, lddgc);

  // Xc := Gc - Qc * Dc (Xc' := Gc' - Dc' * Qc')
  isvd_@x@memcpy(xct, gct, mj * l);
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
    @xtype@ tau = taug, phit = phi;
    for ( isvd_int_t tauiter = 1; tauiter <= taumaxit; ++tauiter, tau *= beta ) {

      // C := [ Dc/2 - I/tau , I/2          ;
      //       -Dgc/2,        -Dc/2 - I/tau ]
      isvd_@x@memset0(c, ldc*l2);
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
    MPI_Allreduce(MPI_IN_PLACE, bgc, ldbgc*l, MPI_@X_TYPE@, MPI_SUM, param.mpi_comm);

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
    isvd_@x@memcpy(xpt, gct, mj * l);
    isvd_@x@Gemm('T', 'N', l, mj, l, -1.0, dc, lddc, qpt, ldqpt, 1.0, xpt, ldxpt);

    // Delta1 [in Qc] := Qc - Q+; Delta2 [in Xc] := Xc - X+
    isvd_v@x@Sub(mj*ldqct, qct, qpt, qct);
    isvd_v@x@Sub(mj*ldxct, xct, xpt, xct);

    // Update taug
    @xtype@ t[2];

    if ( iter % 2 ) {
      t[0] = isvd_@x@Dot(mj*ldqct, qct, 1, qct, 1);
      t[1] = isvd_@x@Dot(mj*ldqct, qct, 1, xct, 1);
    } else {
      t[0] = isvd_@x@Dot(mj*ldxct, xct, 1, qct, 1);
      t[1] = isvd_@x@Dot(mj*ldxct, xct, 1, xct, 1);
    }

    MPI_Allreduce(MPI_IN_PLACE, t, 2, MPI_@X_TYPE@, MPI_SUM, param.mpi_comm);

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

  isvd_free(qct);
  isvd_free(qpt);
  isvd_free(gct);
  isvd_free(xct);
  isvd_free(xpt);
  isvd_free(bc);
  isvd_free(bp);
  isvd_free(bgc);
  isvd_free(dc);
  isvd_free(dgc);
  isvd_free(c);

  // ====================================================================================================================== //
  // Set return values

  isvd_int_t reti = -1;
  if ( retc > ++reti ) retv[reti] = iter;
  if ( retc > ++reti ) retv[reti] = mu;

}
