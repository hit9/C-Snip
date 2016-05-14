/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Util functions for C native strings.
 * deps: None.
 */

#ifndef __STRINGS_H__
#define __STRINGS_H__

#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {
#endif

size_t strings_search(char *s, char *sub,
                      size_t start);     /* best O(N/M), worst O(M*N) */
char *strings_rand(char *s, size_t len); /* O(N) */
char *strings_replace(char *dst, char *src, char *sub,
                      char *rep); /* best O(N), worst O(N*N) */

#if defined(__cplusplus)
}
#endif

#endif
