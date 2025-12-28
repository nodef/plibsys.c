#ifndef PLIBSYS_HEADER_PLIBSYSCONFIG_H
#define PLIBSYS_HEADER_PLIBSYSCONFIG_H

/* Version information - set to a reasonable default */
#define PLIBSYS_VERSION_MAJOR 0
#define PLIBSYS_VERSION_MINOR 0
#define PLIBSYS_VERSION_PATCH 5
#define PLIBSYS_VERSION_STR "0.0.5"
#define PLIBSYS_VERSION                                                        \
  ((PLIBSYS_VERSION_MAJOR << 16) | (PLIBSYS_VERSION_MINOR << 8) |              \
   PLIBSYS_VERSION_PATCH)

/* Detect Windows platform */
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) ||                \
    defined(__WINDOWS__)
#define PLIBSYS_NEED_WINDOWS_H
#endif

/* Always need float.h and limits.h for standard constants */
#define PLIBSYS_NEED_FLOAT_H
#define PLIBSYS_NEED_LIMITS_H

/* Detect if we need values.h (mostly UNIX systems, but not all have it) */
#if defined(__unix__) || defined(__unix) || defined(unix)
#if !defined(__APPLE__) && !defined(__FreeBSD__) && !defined(__NetBSD__) &&    \
    !defined(__OpenBSD__) && !defined(__DragonFly__)
/* #  define PLIBSYS_NEED_VALUES_H */
#endif
#endif

/* Detect if we need pthread_np.h (FreeBSD, OpenBSD, NetBSD) */
#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) ||     \
    defined(__DragonFly__)
#define PLIBSYS_NEED_PTHREAD_NP_H
#endif

/* Detect endianness */
#if defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) &&                \
    __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define PLIBSYS_IS_BIGENDIAN
#elif defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) &&           \
    __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
/* Little endian - no need to define anything */
#elif defined(__BIG_ENDIAN__) || defined(__ARMEB__) || defined(__THUMBEB__) || \
    defined(__AARCH64EB__) || defined(_MIPSEB) || defined(__MIPSEB) ||         \
    defined(__MIPSEB__)
#define PLIBSYS_IS_BIGENDIAN
#elif defined(__sparc) || defined(__sparc__) || defined(__hppa) ||             \
    defined(__hppa__) || defined(_POWER) || defined(__powerpc__) ||            \
    defined(__ppc__) || defined(__PPC__)
#if !defined(__LITTLE_ENDIAN__)
#define PLIBSYS_IS_BIGENDIAN
#endif
#elif defined(__s390__) || defined(__s390x__) || defined(__zarch__)
#define PLIBSYS_IS_BIGENDIAN
#endif

/* Detect sa_family_t size (mostly 2 bytes on all platforms) */
#define PLIBSYS_SIZEOF_SAFAMILY_T 2

/* Detect va_copy - C99 standard */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define PLIBSYS_VA_COPY va_copy
#elif defined(__GNUC__)
#define PLIBSYS_VA_COPY __va_copy
#else
#define PLIBSYS_VA_COPY(dest, src) ((dest) = (src))
#endif

#define PLIBSYS_NTDDI_VERSION_FROM_WIN32_WINNT2(ver) ver##0000
#define PLIBSYS_NTDDI_VERSION_FROM_WIN32_WINNT(ver)                            \
  PLIBSYS_NTDDI_VERSION_FROM_WIN32_WINNT2(ver)

#ifdef PLIBSYS_NEED_WINDOWS_H
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x501
#endif
#ifndef NTDDI_VERSION
#define NTDDI_VERSION PLIBSYS_NTDDI_VERSION_FROM_WIN32_WINNT(_WIN32_WINNT)
#endif
// Include winsock2.h before windows.h to avoid redefinition of types
#include <winsock2.h>
#include <ws2tcpip.h>
// Now include windows.h
#include <windows.h>
#endif

#include <pmacros.h>

#ifdef PLIBSYS_NEED_FLOAT_H
#include <float.h>
#endif

#ifdef PLIBSYS_NEED_LIMITS_H
#include <limits.h>
#endif

#ifdef PLIBSYS_NEED_VALUES_H
#include <values.h>
#endif

P_BEGIN_DECLS

/* Define min/max constants using standard library headers */
#ifdef FLT_MIN
#define P_MINFLOAT FLT_MIN
#else
#define P_MINFLOAT ((float)1.17549435e-38F)
#endif

#ifdef FLT_MAX
#define P_MAXFLOAT FLT_MAX
#else
#define P_MAXFLOAT ((float)3.40282347e+38F)
#endif

#ifdef DBL_MIN
#define P_MINDOUBLE DBL_MIN
#else
#define P_MINDOUBLE ((double)2.2250738585072014e-308)
#endif

#ifdef DBL_MAX
#define P_MAXDOUBLE DBL_MAX
#else
#define P_MAXDOUBLE ((double)1.7976931348623157e+308)
#endif

#ifdef SHRT_MIN
#define P_MINSHORT SHRT_MIN
#else
#define P_MINSHORT ((short)-32768)
#endif

#ifdef SHRT_MAX
#define P_MAXSHORT SHRT_MAX
#else
#define P_MAXSHORT ((short)32767)
#endif

#ifdef USHRT_MAX
#define P_MAXUSHORT USHRT_MAX
#else
#define P_MAXUSHORT ((unsigned short)65535)
#endif

#ifdef INT_MIN
#define P_MININT INT_MIN
#else
#define P_MININT ((int)-2147483648)
#endif

#ifdef INT_MAX
#define P_MAXINT INT_MAX
#else
#define P_MAXINT ((int)2147483647)
#endif

#ifdef UINT_MAX
#define P_MAXUINT UINT_MAX
#else
#define P_MAXUINT ((unsigned int)4294967295U)
#endif

#ifdef LONG_MIN
#define P_MINLONG LONG_MIN
#else
#define P_MINLONG ((long)-2147483648L)
#endif

#ifdef LONG_MAX
#define P_MAXLONG LONG_MAX
#else
#define P_MAXLONG ((long)2147483647L)
#endif

#ifdef ULONG_MAX
#define P_MAXULONG ULONG_MAX
#else
#define P_MAXULONG ((unsigned long)4294967295UL)
#endif

/* Detect pointer size */
#if defined(__LP64__) || defined(_LP64) || defined(__64BIT__) ||               \
    defined(_WIN64) || defined(__x86_64__) || defined(__amd64__) ||            \
    defined(__aarch64__) || defined(__ia64__) || defined(__powerpc64__) ||     \
    defined(__s390x__) || defined(__sparc64__) || defined(__arch64__) ||       \
    defined(_M_X64) || defined(_M_AMD64) || defined(_M_IA64) ||                \
    defined(_M_ARM64)
#define PLIBSYS_SIZEOF_VOID_P 8
#else
#define PLIBSYS_SIZEOF_VOID_P 4
#endif

/* Detect size_t size (usually same as pointer size) */
#if PLIBSYS_SIZEOF_VOID_P == 8
#define PLIBSYS_SIZEOF_SIZE_T 8
#else
#define PLIBSYS_SIZEOF_SIZE_T 4
#endif

/* Detect long size */
#if defined(_WIN64) || defined(_WIN32)
/* On Windows, long is always 4 bytes even on 64-bit */
#define PLIBSYS_SIZEOF_LONG 4
#elif defined(__LP64__) || defined(_LP64)
/* LP64 model: long and pointers are 64-bit */
#define PLIBSYS_SIZEOF_LONG 8
#elif defined(__ILP32__)
/* ILP32 model: int, long, and pointers are 32-bit */
#define PLIBSYS_SIZEOF_LONG 4
#else
/* Default assumption based on pointer size for non-Windows */
#if PLIBSYS_SIZEOF_VOID_P == 8
#define PLIBSYS_SIZEOF_LONG 8
#else
#define PLIBSYS_SIZEOF_LONG 4
#endif
#endif

/* Define byte order */
#ifdef PLIBSYS_IS_BIGENDIAN
#define P_BYTE_ORDER P_BIG_ENDIAN
#else
#define P_BYTE_ORDER P_LITTLE_ENDIAN
#endif

P_END_DECLS

#endif /* PLIBSYS_HEADER_PLIBSYSCONFIG_H */
