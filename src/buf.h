/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Dynamic buffer implementation.
 */

#ifndef _CW_BUF_H
#define _CW_BUF_H       1

#include <stdint.h>
#include <stdlib.h>
#include "bool.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define BUF_CAP_MAX    16*1024*1024   /* max buffer capacity: 16mb */
#define BUF_UNIT_MIN   1              /* min buffer realloc unit: 1 */
#define BUF_UNIT_MAX   1024*1024      /* max buffer realloc unit: 1mb */

#define buf(s)  buf_new(s)
#define str(b)  buf_str(b)

enum {
    BUF_OK = 0,       /* operation is ok */
    BUF_ENOMEM = 1,   /* no memory error */
    BUF_EFAILED = 2,  /* operation is failed */
};

struct buf {
    size_t len;  /* buffer length */
    size_t cap;  /* buffer capacity */
    char *data;  /* real buffer pointer */
};

struct buf *buf_new(const char *s);
struct buf *buf_empty(void);
void buf_free(struct buf *buf);
void buf_clear(struct buf *buf);
int buf_grow(struct buf *buf, size_t cap);
int buf_put(struct buf *buf, char *data, size_t len);
int buf_puts(struct buf *buf, const char *s);
int buf_putc(struct buf *buf, char ch);
char *buf_str(struct buf *buf);
bool buf_isempty(struct buf *buf);
int buf_sprintf(struct buf *buf, const char *fmt, ...);
void buf_lrm(struct buf *buf, size_t len);
size_t buf_len(struct buf *buf);
size_t buf_cap(struct buf *buf);

#if defined(__cplusplus)
}
#endif

#endif
