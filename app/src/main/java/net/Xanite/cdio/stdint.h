/* stdint.h - Standard integer types */

/*
 * Copyright (C) 1988-2019 Free Software Foundation, Inc.
 *
 * This file is part of the GNU C Library.
 *
 * The GNU C Library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The GNU C Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with the GNU C Library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _STDINT_H
#define _STDINT_H 1

#include <cdio/limits.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Types for integer types of fixed width. */

typedef signed char            int8_t;
typedef short int              int16_t;
typedef int                    int32_t;
typedef long long int         int64_t;

typedef unsigned char          uint8_t;
typedef unsigned short int     uint16_t;
typedef unsigned int           uint32_t;
typedef unsigned long long int uint64_t;

/* Types for smallest integer types of specified width. */

typedef int8_t                 int_least8_t;
typedef int16_t                int_least16_t;
typedef int32_t                int_least32_t;
typedef int64_t                int_least64_t;

typedef uint8_t                uint_least8_t;
typedef uint16_t               uint_least16_t;
typedef uint32_t               uint_least32_t;
typedef uint64_t               uint_least64_t;

/* Types for fastest integer types of specified width. */

typedef int8_t                 int_fast8_t;
typedef int16_t                int_fast16_t;
typedef int32_t                int_fast32_t;
typedef int64_t                int_fast64_t;

typedef uint8_t                uint_fast8_t;
typedef uint16_t               uint_fast16_t;
typedef uint32_t               uint_fast32_t;
typedef uint64_t               uint_fast64_t;

/* Types for integer types capable of holding pointers. */

typedef intptr_t               intptr_t;
typedef uintptr_t              uintptr_t;

/* Limits of exact-width integer types. */

#define INT8_MIN       (-128)
#define INT8_MAX       (127)
#define UINT8_MAX      (255)

#define INT16_MIN      (-32768)
#define INT16_MAX      (32767)
#define UINT16_MAX     (65535)

#define INT32_MIN      (-2147483648)
#define INT32_MAX      (2147483647)
#define UINT32_MAX     (4294967295U)

#define INT64_MIN      (-9223372036854775808LL)
#define INT64_MAX      (9223372036854775807LL)
#define UINT64_MAX     (18446744073709551615ULL)

#define INT_LEAST8_MIN  INT8_MIN
#define INT_LEAST8_MAX  INT8_MAX
#define UINT_LEAST8_MAX UINT8_MAX

#define INT_LEAST16_MIN INT16_MIN
#define INT_LEAST16_MAX INT16_MAX
#define UINT_LEAST16_MAX UINT16_MAX

#define INT_LEAST32_MIN INT32_MIN
#define INT_LEAST32_MAX INT32_MAX
#define UINT_LEAST32_MAX UINT32_MAX

#define INT_LEAST64_MIN INT64_MIN
#define INT_LEAST64_MAX INT64_MAX
#define UINT_LEAST64_MAX UINT64_MAX

#define INT_FAST8_MIN   INT8_MIN
#define INT_FAST8_MAX   INT8_MAX
#define UINT_FAST8_MAX  UINT8_MAX

#define INT_FAST16_MIN  INT16_MIN
#define INT_FAST16_MAX  INT16_MAX
#define UINT_FAST16_MAX UINT16_MAX

#define INT_FAST32_MIN  INT32_MIN
#define INT_FAST32_MAX  INT32_MAX
#define UINT_FAST32_MAX UINT32_MAX

#define INT_FAST64_MIN  INT64_MIN
#define INT_FAST64_MAX  INT64_MAX
#define UINT_FAST64_MAX UINT64_MAX

/* Limits of pointer types. */

#define INTPTR_MIN     (-INT64_MAX-1)
#define INTPTR_MAX     INT64_MAX
#define UINTPTR_MAX    UINT64_MAX

/* Other macros. */

#define PTRDIFF_MIN    (-INTPTR_MAX - 1)
#define PTRDIFF_MAX    INTPTR_MAX

#define SIZE_MAX       (UINTPTR_MAX)
#define WCHAR_MIN      (0)
#define WCHAR_MAX      (65535)
#define WINT_MIN       (0)
#define WINT_MAX       (65535)

#ifdef __cplusplus
}
#endif

#endif /* _STDINT_H */