#ifndef _LIMITS_H_
#define _LIMITS_H_

/* Number of bits in a byte. */
#define CHAR_BIT 8

/* Minimum and maximum values for signed char. */
#define SCHAR_MIN (-128)
#define SCHAR_MAX 127

/* Minimum and maximum values for unsigned char. */
#define UCHAR_MAX 255

/* Minimum and maximum values for short. */
#define SHRT_MIN (-32768)
#define SHRT_MAX 32767

/* Maximum value for unsigned short. */
#define USHRT_MAX 65535

/* Minimum and maximum values for int. */
#define INT_MIN (-2147483648)
#define INT_MAX 2147483647

/* Maximum value for unsigned int. */
#define UINT_MAX 4294967295

/* Minimum and maximum values for long. */
#define LONG_MIN (-2147483648L)
#define LONG_MAX 2147483647L

/* Maximum value for unsigned long. */
#define ULONG_MAX 4294967295UL

/* Minimum and maximum values for long long. */
#define LLONG_MIN (-9223372036854775808LL)
#define LLONG_MAX 9223372036854775807LL

/* Maximum value for unsigned long long. */
#define ULLONG_MAX 18446744073709551615ULL

/* Some implementations may define these macros for specific sizes. */
#define SIZE_MAX 18446744073709551615ULL  /* Maximum size_t */
#define WCHAR_MAX 65535  /* Maximum value for wchar_t */
#define WCHAR_MIN 0      /* Minimum value for wchar_t */

/* Char types. */
#define CHAR_MIN (-128)
#define CHAR_MAX 127

#endif /* _LIMITS_H_ */