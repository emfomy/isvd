////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/util/memory.c
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
isvd_int_t*   isvd_imalloc( const size_t num ) {
  return isvd_xmalloc(num, isvd_int_t);
}

isvd_s_val_t* isvd_smalloc( const size_t num ) {
  return isvd_xmalloc(num, isvd_s_val_t);
}

isvd_d_val_t* isvd_dmalloc( const size_t num ) {
  return isvd_xmalloc(num, isvd_d_val_t);
}

isvd_c_val_t* isvd_cmalloc( const size_t num ) {
  return isvd_xmalloc(num, isvd_c_val_t);
}

isvd_z_val_t* isvd_zmalloc( const size_t num ) {
  return isvd_xmalloc(num, isvd_z_val_t);
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
void isvd_imemset0( isvd_int_t   *ptr, const size_t num ) {
  isvd_xmemset0(ptr, num, isvd_int_t);
}

void isvd_smemset0( isvd_s_val_t *ptr, const size_t num ) {
  isvd_xmemset0(ptr, num, isvd_s_val_t);
}

void isvd_dmemset0( isvd_d_val_t *ptr, const size_t num ) {
  isvd_xmemset0(ptr, num, isvd_d_val_t);
}

void isvd_cmemset0( isvd_c_val_t *ptr, const size_t num ) {
  isvd_xmemset0(ptr, num, isvd_c_val_t);
}

void isvd_zmemset0( isvd_z_val_t *ptr, const size_t num ) {
  isvd_xmemset0(ptr, num, isvd_z_val_t);
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
void isvd_imemcpy( isvd_int_t   *dst, const isvd_int_t   *src, const size_t num ) {
  isvd_xmemcpy(dst, src, num, isvd_int_t);
}

void isvd_smemcpy( isvd_s_val_t *dst, const isvd_s_val_t *src, const size_t num ) {
  isvd_xmemcpy(dst, src, num, isvd_s_val_t);
}

void isvd_dmemcpy( isvd_d_val_t *dst, const isvd_d_val_t *src, const size_t num ) {
  isvd_xmemcpy(dst, src, num, isvd_d_val_t);
}

void isvd_cmemcpy( isvd_c_val_t *dst, const isvd_c_val_t *src, const size_t num ) {
  isvd_xmemcpy(dst, src, num, isvd_c_val_t);
}

void isvd_zmemcpy( isvd_z_val_t *dst, const isvd_z_val_t *src, const size_t num ) {
  isvd_xmemcpy(dst, src, num, isvd_z_val_t);
}
//\}
