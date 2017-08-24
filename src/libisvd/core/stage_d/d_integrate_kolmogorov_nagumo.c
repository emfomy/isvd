////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    src/libisvd/core/stage_d/d_integrate_kolmogorov_nagumo.c
/// @brief   The Kolmogorov-Nagumo Integration (double precision)
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/core/stage_d.h>
#include <isvd/la.h>
#include <isvd/util/memory.h>

typedef double isvd_val_t;

#define kMaxit 256
#define kTol   1e-4

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  core_stage_d_module
/// Kolmogorov-Nagumo Integration (double precision)
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
void isvd_dIntegrateKolmogorovNagumo(
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
  const isvd_int_t maxit = ( argc > ++argi ) ? argv[argi] : kMaxit;
  const isvd_val_t tol   = ( argc > ++argi ) ? argv[argi] : kTol;

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
  isvd_assert_ge(maxit, 0);
  isvd_assert_ge(tol, 0);

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

  // matrix Z
  isvd_val_t *z = isvd_dmalloc(l * l);
  isvd_int_t ldz = l;

  // matrix C
  isvd_val_t *c = isvd_dmalloc(l * l);
  isvd_int_t ldc = l;

  // matrix inv(C)
  isvd_val_t *cinv = isvd_dmalloc(l * l);
  isvd_int_t ldcinv = l;

  // vector s
  isvd_val_t *s = isvd_dmalloc(l * 2);

  // matrix Z * sqrt(S)
  isvd_val_t *zs     = cinv;
  isvd_int_t ldzs    = ldcinv;

  // matrix Z / sqrt(S)
  isvd_val_t *zinvs  = z;
  isvd_int_t ldzinvs = ldz;

  // matrix sqrt(S)
  isvd_val_t *ss = s + l;

  isvd_val_t *tmp;

  // ====================================================================================================================== //
  // Initializing

  // Qc := Q0
  isvd_domatcopy('N', l, mj, 1.0, qst, ldqst, qct, ldqct);

  // Bc := Qs' * Qc
  isvd_dgemm('N', 'T', Nl, l, mj, 1.0, qst, ldqst, qct, ldqct, 0.0, bc, ldbc);
  MPI_Allreduce(MPI_IN_PLACE, bc, ldbc*l, MPI_DOUBLE, MPI_SUM, param.mpi_comm);

  // ====================================================================================================================== //
  // Iterating

  isvd_int_t iter;
  isvd_val_t error = -1.0/0.0;

  for ( iter = 1; ; ++iter ) {

    // ================================================================================================================== //
    // Compute B, D, and G

    // Gc := 1/N * Qs * Bc (Gc' := 1/N * Bc' * Qs')
    isvd_dgemm('T', 'N', l, mj, Nl, 1.0/N, bc, ldbc, qst, ldqst, 0.0, gct, ldgct);

    // Bgc := Qs' * Gc
    isvd_dgemm('N', 'T', Nl, l, mj, 1.0, qst, ldqst, gct, ldgct, 0.0, bgc, ldbgc);
    MPI_Allreduce(MPI_IN_PLACE, bgc, ldbgc*l, MPI_DOUBLE, MPI_SUM, param.mpi_comm);

    // Dc := 1/N * Bc' * Bc
    isvd_dgemm('T', 'N', l, l, Nl, 1.0/N, bc, ldbc, bc, ldbc, 0.0, dc, lddc);

    // Dgc [in Z] := 1/N * Bc' * Bgc
    isvd_dgemmt('U', 'T', 'N', l, Nl, 1.0/N, bc, ldbc, bgc, ldbgc, 0.0, z, ldz);

    // ================================================================================================================== //
    // Compute C and inv(C)

    // Z := Dgc - Dc^2
    isvd_dsyrk('U', 'T', l, l, -1.0, dc, lddc, 1.0, z, ldz);

    // eig(Z) = Z * S * Z'
    isvd_dsyev('V', 'U', l, z, ldz, s);

    // S := sqrt( I/2 + sqrt( I/4 - S ) )
    for ( isvd_int_t ii = 0; ii < l; ++ii ) {
      s[ii] = sqrt(0.5 + sqrt(0.25 - s[ii]));
    }
    isvd_vdSqrt(l, s, ss);
    isvd_dmemcpy(cinv, z, l*l);

    // Compute Z * sqrt(S)
    for ( isvd_int_t ii = 0; ii < l; ++ii ) {
      isvd_dscal(l, ss[ii], zs + ldzs*ii, 1);
    }

    // Compute Z / sqrt(S)
    for ( isvd_int_t ii = 0; ii < l; ++ii ) {
      isvd_dscal(l, 1.0/ss[ii], zinvs + ldzinvs*ii, 1);
    }

    // C := Z * S * Z'
    isvd_dgemm('N', 'T', l, l, l, 1.0, zs, ldzs, zs, ldzs, 0.0, c, ldc);

    // inv(C) := Z * inv(S) * Z'
    isvd_dsyrk('U', 'N', l, l, 1.0, zinvs, ldzinvs, 0.0, cinv, ldcinv);

    // ================================================================================================================== //
    // Update for next iteration

    // Fc [in C] := C - Dc * inv(C)
    isvd_dsymm('R', 'U', l, l, -1.0, cinv, ldcinv, dc, lddc, 1.0, c, ldc);

    // Q+ := Qc * Fc [in C] + Gc * inv(C) (Q+' := Fc' [in C] * Qc' + inv(C) * Gc')
    isvd_dgemm('T', 'N', l, mj, l, 1.0, c, ldc, qct, ldqct, 0.0, qpt, ldqpt);
    isvd_dsymm('L', 'U', l, mj, 1.0, cinv, ldcinv, gct, ldgct, 1.0, qpt, ldqpt);

    // B+ := Bc * Fc [in C] + Bgc * inv(C)
    isvd_dgemm('N', 'N', Nl, l, l, 1.0, bc, ldbc, c, ldc, 0.0, bp, ldbp);
    isvd_dsymm('R', 'U', Nl, l, 1.0, cinv, ldcinv, bgc, ldbgc, 1.0, bp, ldbp);

    // ================================================================================================================== //
    // Check convergence: || I - C ||_F < tol
    for ( isvd_int_t ii = 0; ii < l; ++ii ) {
      s[ii] -= 1.0;
    }
    error = isvd_dnrm2(l, s, 1);
    if ( error <= tol ) {
      break;
    }

    if ( iter == maxit ) {
      ++iter;
      break;
    }

    // ================================================================================================================== //
    // Swap
    tmp = qct; qct = qpt; qpt = tmp;
    tmp = bc;  bc  = bp;  bp  = tmp;
  }

  // Swap
  tmp = qct; qct = qpt; qpt = tmp;

  // Copy Qbar
  isvd_domatcopy('N', l, mj, 1.0, qct, ldqct, qt, ldqt);

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_free(qct);
  isvd_free(qpt);
  isvd_free(gct);
  isvd_free(bc);
  isvd_free(bp);
  isvd_free(bgc);
  isvd_free(dc);
  isvd_free(z);
  isvd_free(c);
  isvd_free(cinv);
  isvd_free(s);

  // ====================================================================================================================== //
  // Set return values

  isvd_int_t reti = -1;
  if ( retc > ++reti ) retv[reti] = iter;
  if ( retc > ++reti ) retv[reti] = error;

}
