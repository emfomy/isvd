////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/core/isvd_d_sketch_gaussian_projection.c
/// @brief   The Gaussian Projection Sketching.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/core/dtype.h>
#include <isvd/util/memory.h>

typedef double isvd_val_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup c_core_dtype_s_module
/// Gaussian Projection Sketching (double precision)
///
void isvd_dsgp(
    const char storea,       ///< [in]  The parallel storage of A <br>
                             ///< `'C'`: Block-Column Parallelism <br>
                             ///< `'R'`: Block-Row Parallelism
    const char ordera,       ///< [in]  The storage ordering of A <br>
                             ///< `'C'`: column-major ordering <br>
                             ///< `'R'`: row-major ordering
    const isvd_Param param,  ///< [in]  The parameters
    const isvd_val_t *a,     ///< [in]  The row/column-block A.
    const isvd_int_t lda,    ///< [in]  The leading dimension of the block A.
          isvd_val_t *y,     ///< [out] The row-block Y.
    const isvd_int_t ldy,    ///< [in]  The leading dimension of the block Y.
    const isvd_int_t seed,   ///< [in]  The random seed.
    const MPI_Comm mpi_comm  ///< [in]  The MPI communicator.
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
  isvd_val_t *omega;
  switch ( storea_ ) {
   case 'C': {
     omega = isvd_dmalloc(10);
     break;
   }
  }

  isvd_free(omega);
}
