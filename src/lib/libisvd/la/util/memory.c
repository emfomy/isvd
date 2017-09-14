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

@ISVD_TYPE_MACRO_DEFINE@

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
INT*   isvd_imalloc( const size_t num ) {
  return isvd_xmalloc(num, INT);
}

REAL4* isvd_smalloc( const size_t num ) {
  return isvd_xmalloc(num, REAL4);
}

REAL8* isvd_dmalloc( const size_t num ) {
  return isvd_xmalloc(num, REAL8);
}

COMP4* isvd_cmalloc( const size_t num ) {
  return isvd_xmalloc(num, COMP4);
}

COMP8* isvd_zmalloc( const size_t num ) {
  return isvd_xmalloc(num, COMP8);
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
void isvd_imemset0( INT   *ptr, const size_t num ) {
  isvd_xmemset0(ptr, num, INT);
}

void isvd_smemset0( REAL4 *ptr, const size_t num ) {
  isvd_xmemset0(ptr, num, REAL4);
}

void isvd_dmemset0( REAL8 *ptr, const size_t num ) {
  isvd_xmemset0(ptr, num, REAL8);
}

void isvd_cmemset0( COMP4 *ptr, const size_t num ) {
  isvd_xmemset0(ptr, num, COMP4);
}

void isvd_zmemset0( COMP8 *ptr, const size_t num ) {
  isvd_xmemset0(ptr, num, COMP8);
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
void isvd_imemcpy( INT   *dst, const INT   *src, const size_t num ) {
  isvd_xmemcpy(dst, src, num, INT);
}

void isvd_smemcpy( REAL4 *dst, const REAL4 *src, const size_t num ) {
  isvd_xmemcpy(dst, src, num, REAL4);
}

void isvd_dmemcpy( REAL8 *dst, const REAL8 *src, const size_t num ) {
  isvd_xmemcpy(dst, src, num, REAL8);
}

void isvd_cmemcpy( COMP4 *dst, const COMP4 *src, const size_t num ) {
  isvd_xmemcpy(dst, src, num, COMP4);
}

void isvd_zmemcpy( COMP8 *dst, const COMP8 *src, const size_t num ) {
  isvd_xmemcpy(dst, src, num, COMP8);
}
//\}

@ISVD_TYPE_MACRO_UNDEF@
