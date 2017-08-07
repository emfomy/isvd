////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/dtype.h
/// @brief   The core header for double precision.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_CORE_DTYPE_H_
#define _ISVD_CORE_DTYPE_H_

#include <isvd/def.h>

// Sketching
void isvd_dsgp( const char storea, const char ordera, const index_t N, const index_t m, const index_t n, const index_t l,
                const double *a, const index_t lda, double *y, const index_t ldy, const index_t seed,
                const MPI_Comm mpi_comm );

// Orthogonalization
void isvd_doqr( const index_t N, const index_t m, const index_t l,
                double *y, const index_t ldy,
                const MPI_Comm mpi_comm );

void isvd_dogr( const index_t N, const index_t m, const index_t l,
                double *y, const index_t ldy,
                const MPI_Comm mpi_comm );

// Integration
void isvd_dikn( const index_t N, const index_t m, const index_t l,
                double *y, const index_t ldy, double *q, const index_t ldq,
                const MPI_Comm mpi_comm );

void isvd_diwy( const index_t N, const index_t m, const index_t l,
                double *y, const index_t ldy, double *q, const index_t ldq,
                const MPI_Comm mpi_comm );

// Postprocessing
void isvd_dpqr( const index_t jobu, const index_t jobv, const char storea,
                const char ordera, const char majoru, const char majorv,
                const index_t N, const index_t m, const index_t n, const index_t l, const index_t k,
                const double *a, const index_t lda, const double *q, const index_t ldq,
                double *s, double *u, const index_t ldu, double *v, const index_t ldv,
                const mpi_int_t mpi_root, const MPI_Comm mpi_comm );

void isvd_dpgr( const index_t jobu, const index_t jobv, const char storea,
                const char ordera, const char majoru, const char majorv,
                const index_t N, const index_t m, const index_t n, const index_t l, const index_t k,
                const double *a, const index_t lda, const double *q, const index_t ldq,
                double *s, double *u, const index_t ldu, double *v, const index_t ldv,
                const mpi_int_t mpi_root, const MPI_Comm mpi_comm );

void isvd_dpsy( const index_t jobu, const char storea, const char ordera, const char majoru,
                const index_t N, const index_t m, const index_t n, const index_t l, const index_t k,
                const double *a, const index_t lda, const double *q, const index_t ldq,
                double *s, double *u, const index_t ldu,
                const mpi_int_t mpi_root, const MPI_Comm mpi_comm );

#endif  // _ISVD_CORE_DTYPE_H_
