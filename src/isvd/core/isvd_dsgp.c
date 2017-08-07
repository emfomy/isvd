////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/psdbc.c
/// @brief   The Gaussian Projection Sketching.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/core.h>
#include <mkl.h>

typedef double value_t;

void isvd_dsgp(
    const char storea,
    const char ordera,
    const index_t N,
    const index_t m,
    const index_t n,
    const index_t l,
    const value_t *a,
    const index_t lda,
          value_t *y,
    const index_t ldy,
    const index_t seed,
    const MPI_Comm mpi_comm
) {
  ISVD_UNUSED(storea);
  ISVD_UNUSED(ordera);
  ISVD_UNUSED(N);
  ISVD_UNUSED(m);
  ISVD_UNUSED(n);
  ISVD_UNUSED(l);
  ISVD_UNUSED(a);
  ISVD_UNUSED(lda);
  ISVD_UNUSED(y);
  ISVD_UNUSED(ldy);
  ISVD_UNUSED(seed);
  ISVD_UNUSED(mpi_comm);
}
