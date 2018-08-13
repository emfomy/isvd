////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/util/memory.c
/// \brief      The memory utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/util/memory.h>
#include <libisvd/la/def.h>
#include <stdlib.h>
#include <string.h>

#if defined(ISVD_USE_MKL)
  #define isvd_xMalloc( num, type ) (type*)(mkl_malloc(num * sizeof(type), 64));
#else  // ISVD_USE_MKL
  #define isvd_xMalloc( num, type ) (type*)(malloc(num * sizeof(type)));
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
isvd_int_t*   isvd_iMalloc( const size_t num ) {
  return isvd_xMalloc(num, isvd_int_t);
}

isvd_s_val_t* isvd_sMalloc( const size_t num ) {
  return isvd_xMalloc(num, isvd_s_val_t);
}

isvd_d_val_t* isvd_dMalloc( const size_t num ) {
  return isvd_xMalloc(num, isvd_d_val_t);
}

isvd_c_val_t* isvd_cMalloc( const size_t num ) {
  return isvd_xMalloc(num, isvd_c_val_t);
}

isvd_z_val_t* isvd_zMalloc( const size_t num ) {
  return isvd_xMalloc(num, isvd_z_val_t);
}
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_util_memory_module
/// \brief  Deallocates \a ptr.
///
/// \param  ptr  The pointer to the array.
///
//\{
void isvd_Free( void *ptr ) {
#if defined(ISVD_USE_MKL)
  mkl_free(ptr);
#else  // ISVD_USE_MKL
  free(ptr);
#endif  // ISVD_USE_MKL
}
//\}

#define isvd_xMemset0( ptr, num, type ) memset((void*)(ptr), 0, num * sizeof(type));

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_util_memory_module
/// \brief  Sets the memory to zero.
///
/// \param  ptr  The destination pointer to the array.
/// \param  num  The number of objects.
///
//\{
void isvd_iMemset0( isvd_int_t   *ptr, const size_t num ) {
  isvd_xMemset0(ptr, num, isvd_int_t);
}

void isvd_sMemset0( isvd_s_val_t *ptr, const size_t num ) {
  isvd_xMemset0(ptr, num, isvd_s_val_t);
}

void isvd_dMemset0( isvd_d_val_t *ptr, const size_t num ) {
  isvd_xMemset0(ptr, num, isvd_d_val_t);
}

void isvd_cMemset0( isvd_c_val_t *ptr, const size_t num ) {
  isvd_xMemset0(ptr, num, isvd_c_val_t);
}

void isvd_zMemset0( isvd_z_val_t *ptr, const size_t num ) {
  isvd_xMemset0(ptr, num, isvd_z_val_t);
}
//\}

#define isvd_xMemcpy( dst, src, num, type ) memcpy((void*)(dst), (void*)(src), num * sizeof(type));

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_util_memory_module
/// \brief  Copies the array.
///
/// \param  dst  The destination pointer to the array.
/// \param  src  The source pointer to the array.
/// \param  num  The number of objects.
///
//\{
void isvd_iMemcpy( isvd_int_t   *dst, const isvd_int_t   *src, const size_t num ) {
  isvd_xMemcpy(dst, src, num, isvd_int_t);
}

void isvd_sMemcpy( isvd_s_val_t *dst, const isvd_s_val_t *src, const size_t num ) {
  isvd_xMemcpy(dst, src, num, isvd_s_val_t);
}

void isvd_dMemcpy( isvd_d_val_t *dst, const isvd_d_val_t *src, const size_t num ) {
  isvd_xMemcpy(dst, src, num, isvd_d_val_t);
}

void isvd_cMemcpy( isvd_c_val_t *dst, const isvd_c_val_t *src, const size_t num ) {
  isvd_xMemcpy(dst, src, num, isvd_c_val_t);
}

void isvd_zMemcpy( isvd_z_val_t *dst, const isvd_z_val_t *src, const size_t num ) {
  isvd_xMemcpy(dst, src, num, isvd_z_val_t);
}
//\}
