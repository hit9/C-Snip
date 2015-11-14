/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Util functions for C native strings.
 */

#ifndef _CW_STRINGS_H
#define _CW_STRINGS_H  1

#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {
#endif

size_t strings_search(char *s, char *sub, size_t start); /* best O(N/M), worst O(M*N) */
char *strings_rand(char *s, size_t len); /* O(N) */

#if defined(__cplusplus)
}
#endif

#endif
