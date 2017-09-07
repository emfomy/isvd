////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       demo/cdemo.c
/// \brief      The C demo code
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <stdio.h>
#include <stdlib.h>
#include <isvd.h>
#include <mpi.h>
#include <mmio/mmio.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  /// [init-isvd]
  // Initialize iSVD environment
  isvd_init(&argc, &argv, MPI_COMM_WORLD);

  mpi_int_t mpi_size = isvd_getMpiSize(MPI_COMM_WORLD);
  mpi_int_t mpi_rank = isvd_getMpiRank(MPI_COMM_WORLD);
  mpi_int_t mpi_root = 0;

  // Check input
  if ( argc < 5 ) {
    if ( mpi_rank == mpi_root ) {
      printf("Usage: %s <A-mtx-file> <S-mtx-file> <U-mtx-file> <V-mtx-file>\n\n", argv[0]);
      MPI_Abort(MPI_COMM_WORLD, 1);
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }

  // Display environment
  if ( mpi_rank == mpi_root ) {
    printf("iSVD C demo\n");
    isvd_printEnvironment(MPI_COMM_WORLD);
  }
  /// [init-isvd]

  /// [load-data]
  // Read A
  int m, n;

  FILE *file;
  MM_typecode matcode;

  file = fopen(argv[1], "r");
  mm_read_banner(file, &matcode);
  if ( !mm_is_array(matcode) || !mm_is_real(matcode) || !mm_is_general(matcode) ) {
    if ( mpi_rank == mpi_root ) {
      fprintf(stderr, "Sorry, this application does not support ");
      fprintf(stderr, "Market Market type: [%s]\n", mm_typecode_to_str(matcode));
      MPI_Abort(MPI_COMM_WORLD, 1);
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }
  mm_read_mtx_array_size(file, &m, &n);

  double *a = isvd_dmalloc(m * n);
  isvd_int_t lda = m;
  for ( isvd_int_t j = 0; j < n; ++j ) {
    for ( isvd_int_t i = 0; i < m; ++i ) {
      isvd_dfget(file, &a[i+j*lda]);
    }
  }

  if ( file != stdin ) {
    fclose(file);
  }
  /// [load-data]

  /// [alloc-matrix]
  // Allocate matrix
  const isvd_int_t k = 20, p = 12, l = k+p, N = 16, P = mpi_size;
  const isvd_int_t mb = (m-1)/P+1;
  const isvd_int_t nb = (n-1)/P+1;
  const isvd_int_t Pmb = P * mb;
  const isvd_int_t Pnb = P * nb;

  double *s  = isvd_dmalloc(l);

  double *ut = isvd_dmalloc(l * Pmb);
  isvd_int_t ldut = l;

  double *vt = isvd_dmalloc(l * Pnb);
  isvd_int_t ldvt = l;
  /// [alloc-matrix]

  /// [run-isvd]
  isvd_int_t seed = 0;
  isvd_dIsvd(
#if !defined(ISVD_USE_GPU)
    "GP", "GR", "KN", "GR", m, n, k, p, N, 'R', 'C',
#else  // ISVD_USE_GPU
    "GP_gpu", "GR", "KN", "GR_gpu", m, n, k, p, N, 'R', 'C',
#endif  // ISVD_USE_GPU
    a + mb * mpi_rank, lda, s, ut, ldut, vt, ldvt, seed, mpi_root, mpi_root, mpi_root, MPI_COMM_WORLD
  );
  /// [run-isvd]

  /// [dealloc-matrix]
  // Deallocate matrix
  isvd_free(a);
  isvd_free(s);
  isvd_free(ut);
  isvd_free(vt);
  /// [dealloc-matrix]

  /// [final-isvd]
  // Finalize iSVD
  isvd_finalize();
  /// [final-isvd]

  return 0;
}
