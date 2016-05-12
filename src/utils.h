/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 * deps: None.
 */

#ifndef _CW_UTILS_H
#define _CW_UTILS_H 1

#include <stdarg.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * MIN and MAX
 */
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * OS Platforms
 */
#ifdef __linux__
#define OSPLAT_LINUX 1
#endif

#if defined(__APPLE__)
#define OSPLAT_OSX 1
#endif

#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
#define OSPLAT_BSD 1
#endif

#ifdef __sun
#define OSPLAT_SUN 1
#endif

#if defined(__cplusplus)
}
#endif

#endif
