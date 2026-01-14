#ifndef OPIUM_INCLUDE_H
#define OPIUM_INCLUDE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

#include <search.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <assert.h>
#include <limits.h>
#include <float.h>

int opium_is_little_endian(void);
size_t opium_round_of_two(size_t x);
size_t opium_log2(size_t x);

#endif /* OPIUM_INCLUDE_H */
