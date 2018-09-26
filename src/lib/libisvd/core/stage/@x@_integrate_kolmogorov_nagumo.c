////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/core/stage/@x@_integrate_kolmogorov_nagumo.c
/// \brief      The Kolmogorov-Nagumo Integration (@xname@ precision).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/core/@x@_stage.h>
#include <libisvd/def.h>
#include <isvd/la.h>
#include <isvd/util/memory.h>
#include <isvd/util/mpi.h>

#define kMaxit 256
#define kTol   1e-4

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_stage_module
/// \brief  Kolmogorov-Nagumo Integration (@xname@ precision).
///
/// \param[in]   param       The \ref isvd_Param "parameters".
/// \param[in]   argv, argc  The arguments and its length. <br>
///                          \b argv[0]: The maximum number of iteration. <br>
///                          \b argv[1]: The tolerance of convergence condition.
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
void isvd_@x@IntegrateKolmogorovNagumo(
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
    return;
  }

  // ====================================================================================================================== //
  // Get arguments

  isvd_int_t argi = -1;
  const isvd_int_t maxit = (argc > ++argi) ? argv[argi] : kMaxit;
  const @xtype_____@ tol = (argc > ++argi) ? argv[argi] : kTol;

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

  // matrix Z
  @xtype_____@ *z = isvd_@x@Malloc(l * l);
  isvd_int_t ldz = l;

  // matrix C
  @xtype_____@ *c = isvd_@x@Malloc(l * l);
  isvd_int_t ldc = l;

  // matrix inv(C)
  @xtype_____@ *cinv = isvd_@x@Malloc(l * l);
  isvd_int_t ldcinv = l;

  // vector s
  @xtype_____@ *s = isvd_@x@Malloc(l * 2);

  // matrix Z * sqrt(S)
  @xtype_____@ *zs = cinv;
  isvd_int_t ldzs = ldcinv;

  // matrix Z / sqrt(S)
  @xtype_____@ *zinvs = z;
  isvd_int_t ldzinvs = ldz;

  // matrix sqrt(S)
  @xtype_____@ *ss = s + l;

  @xtype_____@ *tmp;

  // ====================================================================================================================== //
  // Initializing

  // Qc := Q0
  isvd_@x@Omatcopy('N', l, mj, 1.0, qst, ldqst, qct, ldqct);

  // Bc := Qs' * Qc
  isvd_@x@Gemm('N', 'T', Nl, l, mj, 1.0, qst, ldqst, qct, ldqct, 0.0, bc, ldbc);
  isvd_assert_pass(MPI_Allreduce(MPI_IN_PLACE, bc, ldbc*l, MPI_@XTYPE@, MPI_SUM, param.mpi_comm));

  // ====================================================================================================================== //
  // Iterating

  isvd_int_t iter;
  @xtype_____@ error = -1.0/0.0;

  for ( iter = 1; ; ++iter ) {

    // ================================================================================================================== //
    // Compute B, D, and G

    // Gc := 1/N * Qs * Bc (Gc' := 1/N * Bc' * Qs')
    isvd_@x@Gemm('T', 'N', l, mj, Nl, 1.0/N, bc, ldbc, qst, ldqst, 0.0, gct, ldgct);

    // Bgc := Qs' * Gc
    isvd_@x@Gemm('N', 'T', Nl, l, mj, 1.0, qst, ldqst, gct, ldgct, 0.0, bgc, ldbgc);
    isvd_assert_pass(MPI_Allreduce(MPI_IN_PLACE, bgc, ldbgc*l, MPI_@XTYPE@, MPI_SUM, param.mpi_comm));

    // Dc := 1/N * Bc' * Bc
    isvd_@x@Gemm('T', 'N', l, l, Nl, 1.0/N, bc, ldbc, bc, ldbc, 0.0, dc, lddc);

    // Dgc [in Z] := 1/N * Bc' * Bgc
    isvd_@x@Gemmt('U', 'T', 'N', l, Nl, 1.0/N, bc, ldbc, bgc, ldbgc, 0.0, z, ldz);

    // ================================================================================================================== //
    // Compute C and inv(C)

    // Z := Dgc - Dc^2
    isvd_@x@Syrk('U', 'T', l, l, -1.0, dc, lddc, 1.0, z, ldz);

    // eig(Z) = Z * S * Z'
    isvd_@x@Syev('V', 'U', l, z, ldz, s);

    // S := sqrt( I/2 + sqrt( I/4 - S ) )
    for ( isvd_int_t ii = 0; ii < l; ++ii ) {
      s[ii] = sqrt(0.5 + sqrt(0.25 - s[ii]));
    }
    isvd_v@x@Sqrt(l, s, ss);
    isvd_@x@Memcpy(cinv, z, l*l);

    // Compute Z * sqrt(S)
    isvd_@x@Dimm('R', l, l, 1.0, ss, zs, ldzs);

    // Compute Z / sqrt(S)
    isvd_@x@Dism('R', l, l, 1.0, ss, zinvs, ldzinvs);

    // C := Z * S * Z'
    isvd_@x@Gemm('N', 'T', l, l, l, 1.0, zs, ldzs, zs, ldzs, 0.0, c, ldc);

    // inv(C) := Z * inv(S) * Z'
    isvd_@x@Syrk('U', 'N', l, l, 1.0, zinvs, ldzinvs, 0.0, cinv, ldcinv);

    // ================================================================================================================== //
    // Update for next iteration

    // Fc [in C] := C - Dc * inv(C)
    isvd_@x@Symm('R', 'U', l, l, -1.0, cinv, ldcinv, dc, lddc, 1.0, c, ldc);

    // Q+ := Qc * Fc [in C] + Gc * inv(C) (Q+' := Fc' [in C] * Qc' + inv(C) * Gc')
    isvd_@x@Gemm('T', 'N', l, mj, l, 1.0, c, ldc, qct, ldqct, 0.0, qpt, ldqpt);
    isvd_@x@Symm('L', 'U', l, mj, 1.0, cinv, ldcinv, gct, ldgct, 1.0, qpt, ldqpt);

    // B+ := Bc * Fc [in C] + Bgc * inv(C)
    isvd_@x@Gemm('N', 'N', Nl, l, l, 1.0, bc, ldbc, c, ldc, 0.0, bp, ldbp);
    isvd_@x@Symm('R', 'U', Nl, l, 1.0, cinv, ldcinv, bgc, ldbgc, 1.0, bp, ldbp);

    // ================================================================================================================== //
    // Check convergence: || I - C ||_F < tol
    for ( isvd_int_t ii = 0; ii < l; ++ii ) {
      s[ii] -= 1.0;
    }
    error = isvd_@x@Nrm2(l, s, 1);
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
  isvd_@x@Omatcopy('N', l, mj, 1.0, qct, ldqct, qt, ldqt);

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_Free(qct);
  isvd_Free(qpt);
  isvd_Free(gct);
  isvd_Free(bc);
  isvd_Free(bp);
  isvd_Free(bgc);
  isvd_Free(dc);
  isvd_Free(z);
  isvd_Free(c);
  isvd_Free(cinv);
  isvd_Free(s);

  // ====================================================================================================================== //
  // Set return values

  isvd_int_t reti = -1;
  if ( retc > ++reti ) retv[reti] = iter;
  if ( retc > ++reti ) retv[reti] = error;

}
