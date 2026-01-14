#ifndef OPIUM_INCLUDE_H
#define OPIUM_INCLUDE_H

#include <search.h>      // bsearch(), qsort()
#include <stdlib.h>      // rand(), srand(), abs()
#include <math.h>        // sqrt(), pow(), sin(), cos()
#include <string.h>      // memcpy(), memset(), memcmp()
#include <ctype.h>       // isalpha(), isdigit(), toupper()
#include <stddef.h>      // size_t, NULL, offsetof()
#include <stdint.h>      // uint8_t, int32_t и т.д.
#include <stdbool.h>     // bool, true, false
#include <stdarg.h>      // va_list, va_start(), va_arg()
#include <stdio.h>       // printf(), sprintf(), FILE
#include <time.h>        // time(), clock(), struct tm
#include <errno.h>       // errno, perror()
#include <assert.h>      // assert()
#include <limits.h>      // INT_MAX, CHAR_BIT
#include <float.h>       // FLT_MAX, DBL_EPSILON
#include <math.h>
#include <string.h>

#if defined (__linux)
#include "os/unix/opium_lib.h"
#endif

int opium_is_little_endian(void);
size_t opium_round_of_two(size_t x);
size_t opium_log2(size_t x);

void opium_debug_point(void);

#endif /* OPIUM_INCLUDE_H */
