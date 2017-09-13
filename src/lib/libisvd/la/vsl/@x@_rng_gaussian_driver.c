////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/vsl/@x@_rng_gaussian_driver.c
/// \brief      The VSL RngGaussian driver (@xname@ precision).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/la/vsl/driver.h>
#include <libisvd/la/def.h>
#include <isvd/la/vsl/service.h>
#include <isvd/la/vsl/distribution.h>
#include <isvd/util/omp.h>

void isvd_v@x@RngGaussianDriver(
    const isvd_int_t seed,
    const isvd_int_t nskip,
    const isvd_int_t n,
          @xtype@ *r,
    const @xtype@ a,
    const @xtype@ sigma
) {
  ISVD_OMP_PARALLEL
  {
    omp_int_t omp_size = isvd_getOmpSize();
    omp_int_t omp_rank = isvd_getOmpRank();

    isvd_int_t length = n / omp_size;
    isvd_int_t start = length * omp_rank;
    if ( omp_rank == omp_size-1 ) {
      length = n - start;
    }

    isvd_VSLStreamStatePtr stream;
    isvd_vslNewStream(&stream, seed);
    isvd_vslSkipAheadStream(stream, (nskip + start) * 2);
    isvd_v@x@RngGaussian(stream, length, r + start, a, sigma);
    isvd_vslDeleteStream(&stream);
  }
}
