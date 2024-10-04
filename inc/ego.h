# ifndef __EGO_H__
#   define __EGO_H__

/*
 * =========================================================================== *
 * Platform-dependent declarations and definitions                             *
 * =========================================================================== *
 */

#   if defined(__STDC_VERSION__)
#     if __STDC_VERSION__ <= 199901L
#       define C_STANDARD_99 /* ISO/IEC 9899:1999 */
#     elif __STDC_VERSION__ <= 201112L
#       define C_STANDARD_11 /* ISO/IEC 9899:2011 */
#     elif __STDC_VERSION__ <= 201710L
#       define C_STANDARD_17 /* ISO/IEC 9899:2018 */
#     else
#       define C_STANDARD_94 /* ISO/IEC 9899-1:1994 */
#     endif
#   else
#     define C_STANDARD_89 /* ANSI X3.159-1989 */
#     define C_STANDARD_90 /* ISO/IEC 9899:1990 */
#   endif

#   if (                                                                       \
      defined(C_STANDARD_94) ||                                                \
      defined(C_STANDARD_90) || defined(C_STANDARD_89)                         \
    )
#     error: the C standard is not supported by this implementation.
#   endif

#   if defined(_WIN32)
#     define C_DLL_EXPORT __declspec(dllexport)
#     define C_DLL_IMPORT __declspec(dllimport)
#   elif (                                                                     \
      defined(__GNUC__) && (                                                   \
        ( __GNUC__ >= 4 ) || ( __GNUC__ == 3 && __GNUC_MINOR__ >= 3 )          \
      )                                                                        \
    )
#     define C_DLL_EXPORT __attribute__((visibility("default")))
#     define C_DLL_IMPORT __attribute__((visibility("default")))
#   else
#     define C_DLL_EXPORT
#     define C_DLL_IMPORT
#   endif

#   if defined(__GNUC__)
#     define C_INLINE        inline
#     define C_ALWAYS_INLINE inline __attribute__((always_inline))
#   else
#     define C_INLINE        inline
#     define C_ALWAYS_INLINE inline
#   endif

#   define c_round_up(value, multiple)                                         \
  (                                                                            \
    ( ( (value) + (multiple) - 1 ) / (multiple) ) * (multiple)                 \
  )
#   define c_round_down(value, multiple)                                       \
  (                                                                            \
    ( (value) ) / (multiple) ) * (multiple)                                    \
  )

#   define c_round_up_to_power_of_2(value, multiple)                           \
  (                                                                            \
    ( (value) - 1 ) & ~( (multiple) - 1 )                                      \
  )
#   define c_round_down_to_power_of_2(value, multiple)                         \
  (                                                                            \
    (value) & ~( (multiple) - 1 )                                              \
  )

#   define c_align_up(pointer, alignment)                                      \
  (                                                                            \
    (void_t *)(                                                                \
      (u_addr_t)(pointer) +                                                    \
        c_round_up_to_power_of_2((u_addr_t)(pointer), (u_addr_t)(alignment))   \
    )                                                                          \
  )
#   define c_align_down(pointer, alignment)                                    \
  (                                                                            \
    (void_t *)(                                                                \
      c_round_down_to_power_of_2((u_addr_t)(pointer), (u_addr_t)(alignment))   \
    )                                                                          \
  )
#   define c_is_aligned(pointer, alignment)                                    \
  (                                                                            \
    !( (u_addr_t)(pointer) & (u_addr_t)( (alignment) - 1 ) )                   \
  )

#   define c_paste_impl(left, right) left ## right
#   define c_paste(left, right)      c_paste_impl(left, right)
#   define c_quote_impl(value)       #value
#   define c_quote(value)            c_quote_impl(value)

#   if ( defined(__GNUC__) && ( __GNUC__ > 2 ) ) || defined(__clang__)
#      define c_unlikely(expr) __builtin_expect((expr), 0 != 0)
#      define c_likely(expr)   __builtin_expect((expr), 0 == 0)
#   else
#      define c_unlikely(expr) (expr)
#      define c_likely(expr)   (expr)
#   endif

#   define c_unused_id(param) c_paste(_unused_, param)

#   if defined(__GNUC__) || defined(__clang__)
#     define c_unused(param) c_unused_id(param) __attribute__((unused))
#   else
#     define c_unused(param) c_unused_id(param)
#   endif

#   include <assert.h>

#   define c_assert(expr) assert(expr)

#   define C_LF   "\n"
#   define C_CR   "\r"
#   define C_CRLF C_CR C_LF

#   if defined(_WIN32)
#     define C_NL C_CRLF
#   else
#     define C_NL C_LF
#   endif

#   if (                                                                       \
      defined(C_STANDARD_94) ||                                                \
      defined(C_STANDARD_90) || defined(C_STANDARD_89)                         \
    )
#     define bool  int
#     define false ( 0 != 0 )
#     define true  ( 0 == 0 )
#   else
#     include <stdbool.h>
#   endif

typedef unsigned int u_bool_t;

#   define U_FALSE  0
#   define U_TRUE  +1

#   define U_BOOL(n) ( !!(n) ? U_TRUE : U_FALSE )

typedef   signed int s_bool_t;

#   define S_FALSE  0
#   define S_TRUE  -1

#   define S_BOOL(n) ( !!(n) ? S_TRUE : S_FALSE )

typedef bool bool_t;

#   define FALSE false
#   define TRUE  true

#   define BOOL(n) ( !!(n) )

#   if (                                                                       \
      defined(C_STANDARD_94) ||                                                \
      defined(C_STANDARD_90) || defined(C_STANDARD_89)                         \
    )
#     error: <limits.h> is not implemented in C94/90/89.
#   else
#     include <limits.h>
#   endif

typedef unsigned char u_char_t;

#   define U_CHAR(n)  n
#   define U_CHAR_MIN U_CHAR(0)
#   define U_CHAR_MAX UCHAR_MAX

typedef   signed char s_char_t;

#   define S_CHAR(n)  n
#   define S_CHAR_MIN SCHAR_MIN
#   define S_CHAR_MAX SCHAR_MAX

typedef char char_t;

/* Note: `CHAR_MIN` and `CHAR_MAX` are already defined in <limits.h>.          *
 */

#   if (                                                                       \
      defined(C_STANDARD_94) ||                                                \
      defined(C_STANDARD_90) || defined(C_STANDARD_89)                         \
    )
#     error: <stdint.h> is not implemented in C94/90/89.
#   else
#     include <stdint.h>
#   endif

typedef uint8_t  u_byte_t;
typedef uint16_t u_word_t;
typedef uint32_t u_dword_t;
typedef uint64_t u_qword_t;

#   define U_BYTE(n)  UINT8_C(n)
#   define U_WORD(n)  UINT16_C(n)
#   define U_DWORD(n) UINT32_C(n)
#   define U_QWORD(n) UINT64_C(n)

#   define U_BYTE_MIN  U_BYTE(0)
#   define U_WORD_MIN  U_WORD(0)
#   define U_DWORD_MIN U_DWORD(0)
#   define U_QWORD_MIN U_QWORD(0)

#   define U_BYTE_MAX  UINT8_MAX
#   define U_WORD_MAX  UINT16_MAX
#   define U_DWORD_MAX UINT32_MAX
#   define U_QWORD_MAX UINT64_MAX

typedef  int8_t  s_byte_t;
typedef  int16_t s_word_t;
typedef  int32_t s_dword_t;
typedef  int64_t s_qword_t;

#   define S_BYTE(n)  INT8_C(n)
#   define S_WORD(n)  INT16_C(n)
#   define S_DWORD(n) INT32_C(n)
#   define S_QWORD(n) INT64_C(n)

#   define S_BYTE_MIN  S_BYTE(0)
#   define S_WORD_MIN  S_WORD(0)
#   define S_DWORD_MIN S_DWORD(0)
#   define S_QWORD_MIN S_QWORD(0)

#   define S_BYTE_MAX  INT8_MAX
#   define S_WORD_MAX  INT16_MAX
#   define S_DWORD_MAX INT32_MAX
#   define S_QWORD_MAX INT64_MAX

#   if (                                                                       \
      defined(C_STANDARD_94) ||                                                \
      defined(C_STANDARD_90) || defined(C_STANDARD_89)                         \
    )
#     error: <float.h> is not implemented in C94/90/89.
#   else
#     include <float.h>
#   endif

typedef float  f_dword_t;
typedef double f_qword_t;

#   define F_DWORD(n)  n ## F
#   define F_QWORD(n)  n

#   define F_DWORD_MIN FLT_MIN
#   define F_QWORD_MIN DBL_MIN

#   define F_DWORD_MAX FLT_MAX
#   define F_QWORD_MAX DBL_MAX

#   define F_DWORD_EPS FLT_EPSILON
#   define F_QWORD_EPS DBL_EPSILON

#   define C_PLATFORM_8_BIT   8
#   define C_PLATFORM_16_BIT 16
#   define C_PLATFORM_32_BIT 32
#   define C_PLATFORM_64_BIT 64

#   define C_PLATFORM_ENDIAN_LE 0
#   define C_PLATFORM_ENDIAN_BE 1

#   if                                                                         \
      defined(__amd64__)  || defined(__amd64)  ||                              \
      defined(__x86_64__) || defined(__x86_64)
#     define C_PLATFORM_N_BIT  C_PLATFORM_64_BIT
#     define C_PLATFORM_ENDIAN C_PLATFORM_ENDIAN_LE
#   elif defined(__i386__) || defined(__i386) || defined(i386)
#     define C_PLATFORM_N_BIT  C_PLATFORM_32_BIT
#     define C_PLATFORM_ENDIAN C_PLATFORM_ENDIAN_LE
#   else
#     if defined(__LP64__) || defined(_WIN64)
#       define C_PLATFORM_N_BIT C_PLATFORM_64_BIT
#     else
#       define C_PLATFORM_N_BIT C_PLATFORM_32_BIT
#     endif

#     if defined(__BYTE_ORDER__)
#       if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#         define C_PLATFORM_ENDIAN C_PLATFORM_ENDIAN_LE
#       elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#         define C_PLATFORM_ENDIAN C_PLATFORM_ENDIAN_BE
#       else
#         error: the platform endian is not supported by this implementation.
#       endif
#     endif

#     if !defined(C_PLATFORM_N_BIT) || !defined(C_PLATFORM_ENDIAN)
#       error: the platform is not supported by this implementation.
#     endif
#   endif

#   if C_PLATFORM_32_BIT < C_PLATFORM_N_BIT
#     define __u_addr_t   u_qword_t
#     define __s_addr_t   s_qword_t
#     define __U_ADDR(n)  U_QWORD(n)
#     define __S_ADDR(n)  S_QWORD(n)
#     define __U_ADDR_MIN U_QWORD_MIN
#     define __U_ADDR_MAX U_QWORD_MAX
#     define __S_ADDR_MIN S_QWORD_MIN
#     define __S_ADDR_MAX S_QWORD_MAX
#     define __u_size_t   u_qword_t
#     define __s_size_t   s_qword_t
#     define __U_SIZE(n)  U_QWORD(n)
#     define __S_SIZE(n)  S_QWORD(n)
#     define __U_SIZE_MIN S_QWORD_MIN
#     define __U_SIZE_MAX S_QWORD_MAX
#     define __S_SIZE_MIN S_QWORD_MIN
#     define __S_SIZE_MAX S_QWORD_MAX
#   else
#     define __u_addr_t   u_dword_t
#     define __s_addr_t   s_dword_t
#     define __U_ADDR(n)  U_DWORD(n)
#     define __S_ADDR(n)  S_DWORD(n)
#     define __U_ADDR_MIN U_DWORD_MIN
#     define __U_ADDR_MAX U_DWORD_MAX
#     define __S_ADDR_MIN S_DWORD_MIN
#     define __S_ADDR_MAX S_DWORD_MAX
#     define __u_size_t   u_dword_t
#     define __s_size_t   s_dword_t
#     define __U_SIZE(n)  U_DWORD(n)
#     define __S_SIZE(n)  S_DWORD(n)
#     define __U_SIZE_MIN S_DWORD_MIN
#     define __U_SIZE_MAX S_DWORD_MAX
#     define __S_SIZE_MIN S_DWORD_MIN
#     define __S_SIZE_MAX S_DWORD_MAX
#   endif

typedef __u_addr_t u_addr_t;
typedef __u_size_t u_size_t;

#   define U_ADDR(n)  __U_ADDR(n)
#   define U_SIZE(n)  __U_SIZE(n)

#   define U_ADDR_MIN __U_ADDR_MIN
#   define U_SIZE_MIN __U_SIZE_MIN

#   define U_ADDR_MAX __U_ADDR_MAX
#   define U_SIZE_MAX __U_SIZE_MAX

#   define U_ADDR_KiB ( U_ADDR(1) << 10 )
#   define U_SIZE_KiB ( U_SIZE(1) << 10 )

#   if C_PLATFORM_32_BIT <= C_PLATFORM_N_BIT
#     define U_ADDR_MiB ( U_ADDR(1) << 20 )
#     define U_SIZE_MiB ( U_SIZE(1) << 20 )
#     define U_ADDR_GiB ( U_ADDR(1) << 30 )
#     define U_SIZE_GiB ( U_SIZE(1) << 30 )
#   endif

#   if C_PLATFORM_64_BIT <= C_PLATFORM_N_BIT
#     define U_ADDR_TiB ( U_ADDR(1) << 40 )
#     define U_SIZE_TiB ( U_SIZE(1) << 40 )
#     define U_ADDR_PiB ( U_ADDR(1) << 50 )
#     define U_SIZE_PiB ( U_SIZE(1) << 50 )
#     define U_ADDR_EiB ( U_ADDR(1) << 60 )
#     define U_SIZE_EiB ( U_SIZE(1) << 60 )
#   endif

typedef __s_addr_t s_addr_t;
typedef __s_size_t s_size_t;

#   define S_ADDR(n)  __S_ADDR(n)
#   define S_SIZE(n)  __S_SIZE(n)

#   define S_ADDR_MIN __S_ADDR_MIN
#   define S_SIZE_MIN __S_SIZE_MIN

#   define S_ADDR_MAX __S_ADDR_MAX
#   define S_SIZE_MAX __S_SIZE_MAX

#   define S_ADDR_KiB ( S_ADDR(1) << 10 )
#   define S_SIZE_KiB ( S_SIZE(1) << 10 )

#   if C_PLATFORM_32_BIT <= C_PLATFORM_N_BIT
#     define S_ADDR_MiB ( S_ADDR(1) << 20 )
#     define S_SIZE_MiB ( S_SIZE(1) << 20 )
#     define S_ADDR_GiB ( S_ADDR(1) << 30 )
#     define S_SIZE_GiB ( S_SIZE(1) << 30 )
#   endif

#   if C_PLATFORM_64_BIT <= C_PLATFORM_N_BIT
#     define S_ADDR_TiB ( S_ADDR(1) << 40 )
#     define S_SIZE_TiB ( S_SIZE(1) << 40 )
#     define S_ADDR_PiB ( S_ADDR(1) << 50 )
#     define S_SIZE_PiB ( S_SIZE(1) << 50 )
#     define S_ADDR_EiB ( S_ADDR(1) << 60 )
#     define S_SIZE_EiB ( S_SIZE(1) << 60 )
#   endif

#   if (                                                                       \
      defined(C_STANDARD_94) ||                                                \
      defined(C_STANDARD_90) || defined(C_STANDARD_89)                         \
    )
#     error: <stdatomic.h> is not implemented in C89/90/94.
#   else
#     include <stdatomic.h>
#   endif

typedef _Atomic(u_bool_t)  atomic_u_bool_t;
typedef _Atomic(s_bool_t)  atomic_s_bool_t;
typedef _Atomic(bool_t)    atomic_bool_t;
typedef _Atomic(u_byte_t)  atomic_u_byte_t;
typedef _Atomic(u_word_t)  atomic_u_word_t;
typedef _Atomic(u_dword_t) atomic_u_dword_t;
typedef _Atomic(u_qword_t) atomic_u_qword_t;
typedef _Atomic(s_byte_t)  atomic_s_byte_t;
typedef _Atomic(s_word_t)  atomic_s_word_t;
typedef _Atomic(s_dword_t) atomic_s_dword_t;
typedef _Atomic(s_qword_t) atomic_s_qword_t;
typedef _Atomic(u_char_t)  atomic_u_char_t;
typedef _Atomic(s_char_t)  atomic_s_char_t;
typedef _Atomic(char_t)    atomic_char_t;
typedef _Atomic(u_addr_t)  atomic_u_addr_t;
typedef _Atomic(u_size_t)  atomic_u_size_t;
typedef _Atomic(s_addr_t)  atomic_s_addr_t;
typedef _Atomic(s_size_t)  atomic_s_size_t;

#   if defined(__linux__) || defined(__linux) || defined(linux)
#     include <byteswap.h>
#     define c_byteswap_word(value)  bswap_16((value))
#     define c_byteswap_dword(value) bswap_32((value))
#     define c_byteswap_qword(value) bswap_64((value))
#   else
#     define c_byteswap_word(value)                                            \
  (                                                                            \
    ( ( (value) & U_WORD(0xFF00) ) >> 8 ) |                                    \
    ( ( (value) & U_WORD(0x00FF) ) << 8 )                                      \
  )
#     define c_byteswap_dword(value)                                           \
  (                                                                            \
    ( ( (value) & U_DWORD(0xFF000000) ) >> 24 ) |                              \
    ( ( (value) & U_DWORD(0x00FF0000) ) >>  8 ) |                              \
    ( ( (value) & U_DWORD(0x0000FF00) ) <<  8 ) |                              \
    ( ( (value) & U_DWORD(0x000000FF) ) << 24 )                                \
  )
#     define c_byteswap_qword(value)                                           \
  (                                                                            \
    ( ( (value) & U_QWORD(0xFF00000000000000) ) >> 56 ) |                      \
    ( ( (value) & U_QWORD(0x00FF000000000000) ) >> 40 ) |                      \
    ( ( (value) & U_QWORD(0x0000FF0000000000) ) >> 24 ) |                      \
    ( ( (value) & U_QWORD(0x000000FF00000000) ) >>  8 ) |                      \
    ( ( (value) & U_QWORD(0x00000000FF000000) ) <<  8 ) |                      \
    ( ( (value) & U_QWORD(0x0000000000FF0000) ) << 24 ) |                      \
    ( ( (value) & U_QWORD(0x000000000000FF00) ) << 40 ) |                      \
    ( ( (value) & U_QWORD(0x00000000000000FF) ) << 56 )                        \
  )
#   endif

#   define C_SIZE_LOG2_OF_BYTE  0
#   define C_SIZE_OF_BYTE       ( U_SIZE(1) << C_SIZE_LOG2_OF_BYTE  )
#   define C_SIZE_LOG2_OF_WORD  1
#   define C_SIZE_OF_WORD       ( U_SIZE(1) << C_SIZE_LOG2_OF_WORD  )
#   define C_SIZE_LOG2_OF_DWORD 2
#   define C_SIZE_OF_DWORD      ( U_SIZE(1) << C_SIZE_LOG2_OF_DWORD )
#   define C_SIZE_LOG2_OF_QWORD 3
#   define C_SIZE_OF_QWORD      ( U_SIZE(1) << C_SIZE_LOG2_OF_QWORD )

#   define c_bytes_of(value)    ( (u_size_t)sizeof(value) / C_SIZE_OF_BYTE  )
#   define c_words_of(value)    ( (u_size_t)sizeof(value) / C_SIZE_OF_WORD  )
#   define c_dwords_of(value)   ( (u_size_t)sizeof(value) / C_SIZE_OF_DWORD )
#   define c_qwords_of(value)   ( (u_size_t)sizeof(value) / C_SIZE_OF_QWORD )
#   define c_size_of(value)     ( (u_size_t)sizeof(value) )
#   define c_count_of(values)   ( c_size_of(values) / c_size_of(values[0]) )

#   include <stdlib.h>

#   define c_allocate(new_size)                                                \
  (                                                                            \
    malloc((new_size))                                                         \
  )
#   define c_reallocate(old_data, old_size, new_size)                          \
  (                                                                            \
    realloc((old_data), (new_size))                                            \
  )
#   define c_deallocate(old_data, old_size)                                    \
  (                                                                            \
    free((old_data))                                                           \
  )

/*
 * =========================================================================== *
 * Framework declarations and definitions                                      *
 * =========================================================================== *
 */

#   if defined(__EGO_STANDS_ALONE__)
#     define __EGO_PRIVATE__
#     define __EGO_PROTECT__
#     define __EGO_PUBLIC__
#   elif defined(__GNUC__) || defined(__clang__)
#     if defined(__EGO_BUILD__)
#       define __EGO_PRIVATE__ __attribute__((visibility("hidden")))
#       define __EGO_PROTECT__ C_DLL_EXPORT __attribute__((visibility("default")))
#       define __EGO_PUBLIC__  C_DLL_EXPORT __attribute__((visibility("default")))
#     else
#       define __EGO_PRIVATE__ __attribute__((visibility("hidden")))
#       define __EGO_PROTECT__ C_DLL_IMPORT __attribute__((visibility("default")))
#       define __EGO_PUBLIC__  C_DLL_IMPORT __attribute__((visibility("default")))
#     endif
#   else
#     define __EGO_PRIVATE__
#     define __EGO_PROTECT___

#     if defined(__EGO_BUILD__)
#       define __EGO_PUBLIC__ C_DLL_EXPORT
#     else
#       define __EGO_PUBLIC__ C_DLL_IMPORT
#     endif
#   endif

#   include "ego-version.h"

#   define __ego__ __EGO_VERSION_NUMBER__
#   define __EGO__ __EGO_VERSION_NUMBER__

/*
 * =========================================================================== *
 */

# endif /* __EGO_H__ */