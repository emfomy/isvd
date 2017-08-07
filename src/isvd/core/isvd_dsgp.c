////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/psdbc.c
/// @brief   The Gaussian Projection Sketching.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/core/dtype.h>
#include <isvd/util/memory.h>

typedef double value_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @brief  Gaussian Projection Sketching (double precision)
//
void isvd_dsgp(
    const char storea,       ///< [in] The parallel storage of A <br>
                             ///< `'C'`: Block-Column Parallelism <br>
                             ///< `'R'`: Block-Row Parallelism
    const char ordera,       ///< [in] The storage ordering of A <br>
                             ///< `'C'`: column-major ordering <br>
                             ///< `'R'`: row-major ordering
    const index_t N,         ///< [in] The number of random sketches.
    const index_t m,         ///< [in] The number of rows of A.
    const index_t n,         ///< [in] The number of columns of A.
    const index_t l,         ///< [in] The dimension of randomized sketches.
    const value_t *a,        ///< [in] The row/column-block A.
    const index_t lda,       ///< [in] The leading dimension of the block A.
          value_t *y,        ///< [out] The row-block Y.
    const index_t ldy,       ///< [in] The leading dimension of the block Y.
    const index_t seed,      ///< [in] The random seed.
    const MPI_Comm mpi_comm  ///< [in] The MPI communicator.
) {
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Check arguments

  char storea_ = isvd_arg2char("STOREA", storea, "CR", "CR");
  char transa_ = isvd_arg2char("ORDERA", ordera, "CR", "NT");
  if ( storea_ == 0 || transa_ == 0 ) return;

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Get parameters

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Allocate memory
  value_t *omega;
  switch ( storea_ ) {
   case 'C': {
     omega = isvd_dmalloc(10);
     break;
   }
  }

  isvd_free(omega);
}
