////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/isvd/util/memory.c
/// \brief      The memory utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/util/memory.h>
#include <libisvd/la/def.h>
#include <stdlib.h>
#include <string.h>

#if defined(ISVD_USE_MKL)
  #define isvd_xmalloc( num, type ) (type*)(mkl_malloc(num * sizeof(type), 64));
#else  // ISVD_USE_MKL
  #define isvd_xmalloc( num, type ) (type*)(malloc(num * sizeof(type)));
#endif  // ISVD_USE_MKL

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_util_memory_module
/// \brief  Allocates an array with size \a num.
///
/// \param  num  The number of objects.
///
/// \return      The pointer to the array.
///
//\{
isvd_int_t* isvd_imalloc( const size_t num ) {
  return isvd_xmalloc(num, isvd_int_t);
}

float* isvd_smalloc( const size_t num ) {
  return isvd_xmalloc(num, float);
}

double* isvd_dmalloc( const size_t num ) {
  return isvd_xmalloc(num, double);
}

_Complex float* isvd_cmalloc( const size_t num ) {
  return isvd_xmalloc(num, _Complex float);
}

_Complex double* isvd_zmalloc( const size_t num ) {
  return isvd_xmalloc(num, _Complex double);
}
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_util_memory_module
/// \brief  Deallocates \a ptr.
///
/// \param  ptr  The pointer to the array.
///
//\{
void isvd_free( void *ptr ) {
#if defined(ISVD_USE_MKL)
  mkl_free(ptr);
#else  // ISVD_USE_MKL
  free(ptr);
#endif  // ISVD_USE_MKL
}
//\}

#define isvd_xmemset0( ptr, num, type ) memset((void*)(ptr), 0, num * sizeof(type));

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_util_memory_module
/// \brief  Sets the memory to zero.
///
/// \param  ptr  The destination pointer to the array.
/// \param  num  The number of objects.
///
//\{
void isvd_imemset0( isvd_int_t *ptr, const size_t num ) {
  isvd_xmemset0(ptr, num, isvd_int_t);
}

void isvd_smemset0( float *ptr, const size_t num ) {
  isvd_xmemset0(ptr, num, float);
}

void isvd_dmemset0( double *ptr, const size_t num ) {
  isvd_xmemset0(ptr, num, double);
}

void isvd_cmemset0( _Complex float *ptr, const size_t num ) {
  isvd_xmemset0(ptr, num, _Complex float);
}

void isvd_zmemset0( _Complex double *ptr, const size_t num ) {
  isvd_xmemset0(ptr, num, _Complex double);
}
//\}

#define isvd_xmemcpy( dst, src, num, type ) memcpy((void*)(dst), (void*)(src), num * sizeof(type));

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_util_memory_module
/// \brief  Copies the array.
///
/// \param  dst  The destination pointer to the array.
/// \param  src  The source pointer to the array.
/// \param  num  The number of objects.
///
//\{
void isvd_imemcpy( isvd_int_t *dst, const isvd_int_t *src, const size_t num ) {
  isvd_xmemcpy(dst, src, num, isvd_int_t);
}

void isvd_smemcpy( float *dst, const float *src, const size_t num ) {
  isvd_xmemcpy(dst, src, num, float);
}

void isvd_dmemcpy( double *dst, const double *src, const size_t num ) {
  isvd_xmemcpy(dst, src, num, double);
}

void isvd_cmemcpy( _Complex float *dst, const _Complex float *src, const size_t num ) {
  isvd_xmemcpy(dst, src, num, _Complex float);
}

void isvd_zmemcpy( _Complex double *dst, const _Complex double *src, const size_t num ) {
  isvd_xmemcpy(dst, src, num, _Complex double);
}
//\}
