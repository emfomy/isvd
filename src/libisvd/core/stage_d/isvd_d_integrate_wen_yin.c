////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    src/libisvd/core/stage_d/isvd_d_integrate_wen_yin.c
/// @brief   The Wen-Yin Integration (double precision)
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/core/stage_d.h>
#include <isvd/la.h>
#include <isvd/util/memory.h>

typedef double isvd_val_t;

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
/// @ingroup  core_stage_d_module
/// Wen-Yin Integration (double precision)
///
/// @param[in]   param       The @ref isvd_Param "parameters".
/// @param[in]   argv, argc  The arguments and its length. <br>
///                          `argv[0]`: The maximum number of iteration. (optional, default as @ref kMaxit) <br>
///                          `argv[1]`: The tolerance of convergence condition. (optional, default as @ref kTol)
/// @param[in]   retv, retc  The return values and its length.
/// <hr>
/// @param[in]   yst, ldyst  The row-block 𝕼 (@f$ m_b \times Nl @f$, row-major) and its leading dimension.
/// @param[in]   qt, ldqt    The row-block 𝑸 (@f$ m_b \times l @f$, row-major) and its leading dimension.
/// <hr>
/// @param[out]  retv        Replaced by return values.
///                          `retv[0]`: The number of iteration.
///                          `retv[1]`: The error.
/// @param[out]  qt          Replaced by the row-block 𝑸 (row-major).
///
void isvd_dIntegrateWenYin(
    const isvd_Param param,
    const isvd_val_t *argv,
    const isvd_int_t argc,
          isvd_val_t *retv,
    const isvd_int_t retc,
    const isvd_val_t *yst,
    const isvd_int_t ldyst,
          isvd_val_t *qt,
    const isvd_int_t ldqt
) {

  // ====================================================================================================================== //
  // Get arguments

  isvd_int_t argi = -1;
  const isvd_int_t maxit    = ( argc > ++argi ) ? argv[argi] : kMaxit;
  const isvd_val_t tol      = ( argc > ++argi ) ? argv[argi] : kTol;
  const isvd_val_t tau0     = ( argc > ++argi ) ? argv[argi] : kTau0;
  const isvd_val_t taumax   = ( argc > ++argi ) ? argv[argi] : kTaumax;
  const isvd_val_t taumin   = ( argc > ++argi ) ? argv[argi] : kTaumin;
  const isvd_int_t taumaxit = ( argc > ++argi ) ? argv[argi] : kTauMaxit;
  const isvd_val_t beta     = ( argc > ++argi ) ? argv[argi] : kBeta;
  const isvd_val_t sigma    = ( argc > ++argi ) ? argv[argi] : kSigma;
  const isvd_val_t eta      = ( argc > ++argi ) ? argv[argi] : kEta;

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

  const isvd_val_t *qst = yst;
  isvd_int_t ldqst = ldyst;

  // matrix Qc'
  isvd_val_t *qct = isvd_dmalloc(mj * l);
  isvd_int_t ldqct = l;

  // matrix Q+'
  isvd_val_t *qpt = isvd_dmalloc(mj * l);
  isvd_int_t ldqpt = l;

  // matrix Gc'
  isvd_val_t *gct = isvd_dmalloc(mj * l);
  isvd_int_t ldgct = l;

  // matrix Xc'
  isvd_val_t *xct = isvd_dmalloc(mj * l);
  isvd_int_t ldxct = l;

  // matrix X+'
  isvd_val_t *xpt = isvd_dmalloc(mj * l);
  isvd_int_t ldxpt = l;

  // matrix Bc
  isvd_val_t *bc = isvd_dmalloc(Nl * l);
  isvd_int_t ldbc = Nl;

  // matrix B+
  isvd_val_t *bp = isvd_dmalloc(Nl * l);
  isvd_int_t ldbp = Nl;

  // matrix Bgc
  isvd_val_t *bgc = isvd_dmalloc(Nl * l);
  isvd_int_t ldbgc = Nl;

  // matrix Dc
  isvd_val_t *dc = isvd_dmalloc(l * l);
  isvd_int_t lddc = l;

  // matrix Dgc
  isvd_val_t *dgc = isvd_dmalloc(l * l);
  isvd_int_t lddgc = l;

  // matrix C & inv(C)
  isvd_val_t *c = isvd_dmalloc(l2 * l2);
  isvd_int_t ldc = l2;

  // matrix inv(C)_??
  isvd_val_t *c11 = c;
  isvd_val_t *c21 = c + l;
  isvd_val_t *c12 = c + ldc*l;
  isvd_val_t *c22 = c + l + ldc*l;

  // matrix inv(C)_#?
  isvd_val_t *cs1 = c11;
  isvd_val_t *cs2 = c12;

  // matrix Fc
  isvd_val_t *fc = c21;
  isvd_int_t ldfc = ldc;

  // matrix Fgc
  isvd_val_t *fgc = c11;
  isvd_int_t ldfgc = ldc;

  isvd_val_t *tmp;

  isvd_val_t taug, zeta, phi, mu;

  // ====================================================================================================================== //
  // Initializing

  // Qc := Q0
  mkl_domatcopy('R', 'N', mj, l, 1.0, qst, ldqst, qct, ldqct);

  // Bc := Qs' * Qc
  isvd_dgemm('N', 'T', Nl, l, mj, 1.0, qst, ldqst, qct, ldqct, 0.0, bc, ldbc);
  MPI_Allreduce(MPI_IN_PLACE, bc, ldbc*l, MPI_DOUBLE, MPI_SUM, param.mpi_comm);

  // Dc := 1/N * Bc' * Bc
  isvd_dgemm('T', 'N', l, l, Nl, 1.0/N, bc, ldbc, bc, ldbc, 0.0, dc, lddc);

  // Gc := 1/N * Qs * Bc (Gc' := 1/N * Bc' * Qs')
  isvd_dgemm('T', 'N', l, mj, Nl, 1.0/N, bc, ldbc, qst, ldqst, 0.0, gct, ldgct);

  // Bgc := Qs' * Gc
  isvd_dgemm('N', 'T', Nl, l, mj, 1.0, qst, ldqst, gct, ldgct, 0.0, bgc, ldbgc);
  MPI_Allreduce(MPI_IN_PLACE, bgc, ldbgc*l, MPI_DOUBLE, MPI_SUM, param.mpi_comm);

  // Dgc := 1/N * Bc' * Bgc
  isvd_dgemm('T', 'N', l, l, Nl, 1.0/N, bc, ldbc, bgc, ldbgc, 0.0, dgc, lddgc);

  // Xc := Gc - Qc * Dc (Xc' := Gc' - Dc' * Qc')
  isvd_dmemcpy(xct, gct, mj * l);
  isvd_dgemm('T', 'N', l, mj, l, -1.0, dc, lddc, qct, ldqct, 1.0, xct, ldxct);

  // mu := tr( Dgc ) - norm( Dc )_F^2
  mu = isvd_dasum(l, dgc, lddgc+1) - isvd_ddot(lddc*l, dc, 1, dc, 1);

  // taug := tau0; zeta := 1; phi := 1/2N * norm( Bc )_F^2
  taug = tau0;
  zeta = 1.0;
  phi = 0.5/N * isvd_ddot(ldbc*l, bc, 1, bc, 1);

  // ====================================================================================================================== //
  // Iterating

  isvd_int_t iter;
  isvd_val_t error = -1.0/0.0;

  for ( iter = 1; ; ++iter ) {

    // ================================================================================================================== //
    // Find step size
    isvd_val_t tau = taug, phit = phi;
    for ( isvd_int_t tauiter = 1; tauiter <= taumaxit; ++tauiter, tau *= beta ) {

      // C := [ Dc/2 - I/tau , I/2          ;
      //       -Dgc/2,        -Dc/2 - I/tau ]
      isvd_dmemset0(c, ldc*l2);
      mkl_domatcopy('C', 'N', l, l,  0.5, dc,  lddc,  c11, ldc);
      mkl_domatcopy('C', 'N', l, l, -0.5, dgc, lddgc, c21, ldc);
      mkl_domatcopy('C', 'N', l, l, -0.5, dc,  lddc,  c22, ldc);
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
      isvd_dgeinv(l2, c, ldc);

      // Fc  [in C21] := I + inv(C22) * Dc - inv(C21)
      // Fgc [in C11] :=     inv(C12) * Dc - inv(C21)
      isvd_dgemm('N', 'N', l2, l, l, 1.0, cs2, ldc, dc, lddc, -1.0, cs1, ldc);
      for ( isvd_int_t ii = 0; ii < l; ++ii ) {
        c21[ii+ldc*ii] += 1.0;
      }

      // B+ := Bc * Fc + Bgc * Fgc
      isvd_dgemm('N', 'N', Nl, l, l, 1.0, bc,  ldbc,  fc,  ldfc,  0.0, bp, ldbp);
      isvd_dgemm('N', 'N', Nl, l, l, 1.0, bgc, ldbgc, fgc, ldfgc, 1.0, bp, ldbp);

      // ~phi := 1/2N * norm( B+ )_F^2
      phit = 0.5/N * isvd_ddot(ldbp*l, bp, 1, bp, 1);

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
    isvd_dgemm('T', 'N', l, mj, l, 1.0, fc,  ldfc,  qct, ldqct, 0.0, qpt, ldqpt);
    isvd_dgemm('T', 'N', l, mj, l, 1.0, fgc, ldfgc, gct, ldgct, 1.0, qpt, ldqpt);

    // D+ [in Dc] := 1/N * B+' * B+
    isvd_dgemm('T', 'N', l, l, Nl, 1.0/N, bp, ldbp, bp, ldbp, 0.0, dc, lddc);

    // G+ [in Gc] := 1/N * Qs * B+ (G+'[in Gc'] := 1/N * B+' * Qs')
    isvd_dgemm('T', 'N', l, mj, Nl, 1.0/N, bp, ldbp, qst, ldqst, 0.0, gct, ldgct);

    // Bg+ [in Bgc] := Qs' * G+ [in Gc]
    isvd_dgemm('N', 'T', Nl, l, mj, 1.0, qst, ldqst, gct, ldgct, 0.0, bgc, ldbgc);
    MPI_Allreduce(MPI_IN_PLACE, bgc, ldbgc*l, MPI_DOUBLE, MPI_SUM, param.mpi_comm);

    // Dg+ [in Dgc] := 1/N * B+' * Bg+ [in Bgc]
    isvd_dgemm('T', 'N', l, l, Nl, 1.0/N, bp, ldbp, bgc, ldbgc, 0.0, dgc, lddgc);

    // mu := tr( Dg+ [in Dgc] ) - norm( D+ [in Dc] )_F^2
    mu = isvd_dasum(l, dgc, lddgc+1) - isvd_ddot(lddc*l, dc, 1, dc, 1);

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
    isvd_dmemcpy(xpt, gct, mj * l);
    isvd_dgemm('T', 'N', l, mj, l, -1.0, dc, lddc, qpt, ldqpt, 1.0, xpt, ldxpt);

    // Delta1 [in Qc] := Qc - Q+; Delta2 [in Xc] := Xc - X+
    vdSub(mj*ldqct, qct, qpt, qct);
    vdSub(mj*ldxct, xct, xpt, xct);

    // Update taug
    isvd_val_t t[2];

    if ( iter % 2 ) {
      t[0] = isvd_ddot(mj*ldqct, qct, 1, qct, 1);
      t[1] = isvd_ddot(mj*ldqct, qct, 1, xct, 1);
    } else {
      t[0] = isvd_ddot(mj*ldxct, xct, 1, qct, 1);
      t[1] = isvd_ddot(mj*ldxct, xct, 1, xct, 1);
    }

    MPI_Allreduce(MPI_IN_PLACE, t, 2, MPI_DOUBLE, MPI_SUM, param.mpi_comm);

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
  mkl_domatcopy('C', 'N', l, mj, 1.0, qct, ldqct, qt, ldqt);

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
  if ( retc > ++reti ) retv[reti] = error;

}
