/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buf.h"

/* Create new buffer and init it with a C null-terminated
 * string if `s` is not NULL.
 */
struct buf *
buf_new(const char *s)
{
    struct buf *buf = malloc(sizeof(struct buf));

    if (buf != NULL) {
        buf->len = 0;
        buf->cap = 0;
        buf->data = NULL;

        if (s != NULL) {
            if (buf_puts(buf, s) != BUF_OK)
                return NULL;
        }
    }
    return buf;
}

/* Create empty buffer */
struct buf *
buf_empty(void)
{
    return buf_new(NULL);
}

/* Free a buffer and its data, no operation is performed
 * if the buffer is NULL. */
void
buf_free(struct buf *buf)
{
    if (buf != NULL) {
        if (buf->data != NULL)
            free(buf->data);
        free(buf);
    }
}

/* Clear a buffer and the data memory will also be freed. */
void
buf_clear(struct buf *buf)
{
    assert(buf != NULL);

    if (buf->data != NULL)
        free(buf->data);
    buf->data = NULL;
    buf->len = 0;
    buf->cap = 0;
}

/* Grow a buffer's capacity to given size, the new capacity is
 * calculated like k*unit>=cap, by default, the unit is current cap,
 * if the unit is large enough, use BUF_UNIT_MAX instead. */
int
buf_grow(struct buf *buf, size_t cap)
{
    assert(buf != NULL);

    if (cap > BUF_CAP_MAX)
        return BUF_ENOMEM;

    if (cap <= buf->cap)
        return BUF_OK;

    size_t unit = buf->cap;

    if (unit > BUF_UNIT_MAX)
        unit = BUF_UNIT_MAX;

    if (unit < BUF_UNIT_MIN)
        unit = BUF_UNIT_MIN;

    size_t new_cap = buf->cap + unit;
    while (new_cap < cap)
        new_cap += unit;

    char *data= realloc(buf->data, new_cap * sizeof(char));

    if (data == NULL)
        return BUF_ENOMEM;

    buf->data = data;
    buf->cap = new_cap;
    return BUF_OK;
}

/* Put chars on the end of a buffer */
int
buf_put(struct buf *buf, char *data, size_t len)
{
    int error = buf_grow(buf, buf->len + len);

    if (error == BUF_OK) {
        memcpy(buf->data + buf->len, data, len);
        buf->len += len;
    }
    return error;
}

/* Put null-terminated chars to the end of a buffer. */
int
buf_puts(struct buf *buf, const char *s)
{
    return buf_put(buf, (char *)s, strlen(s));
}

/* Put a single char to the end of a buffer. */
int
buf_putc(struct buf *buf, char ch)
{
    int error = buf_grow(buf, buf->len + 1);

    if (error == BUF_OK) {
        buf->data[buf->len] = ch;
        buf->len += 1;
    }
    return error;
}

/* Get buffer data as null-terminated chars */
char *
buf_str(struct buf *buf)
{
    assert(buf != NULL);

    if (buf->len < buf->cap && buf->data[buf->len] == '\0')
        return buf->data;

    if (buf->len + 1 <= buf->cap ||
            buf_grow(buf, buf->len + 1) == BUF_OK) {
        buf->data[buf->len] = '\0';
        return buf->data;
    }

    return NULL;
}

/* Return true if a buffer is empty */
bool
buf_isempty(struct buf *buf)
{
    assert(buf != NULL);
    if (buf->len == 0)
        return true;
    return false;
}

/* Formatted printing to a buffer. */
int
buf_sprintf(struct buf *buf, const char *fmt, ...)
{
    assert(buf != NULL);

    if (buf->len >= buf->cap &&
            buf_grow(buf, buf->len + 1) != BUF_OK)
        return BUF_ENOMEM;

    va_list ap;
    int num;

    va_start(ap, fmt);
    num = vsnprintf(buf->data + buf->len, buf->cap - buf->len, fmt, ap);
    va_end(ap);

    if (num < 0)
        return BUF_EFAILED;

    size_t size = (size_t)num;

    if (size >= buf->cap - buf->len) {
        if (buf_grow(buf, buf->len + size + 1) != BUF_OK)
            return BUF_ENOMEM;
        va_start(ap, fmt);
        num = vsnprintf(buf->data + buf->len,
                buf->cap - buf->len, fmt, ap);
        va_end(ap);
    }

    if (num < 0)
        return BUF_EFAILED;

    buf->len += num;
    return BUF_OK;
}

/* Romve part of buf on the left. */
void
buf_lrm(struct buf *buf, size_t len)
{
    assert(buf != NULL);

    if (len > buf->len) {
        buf->len = 0;
        return;
    }

    buf->len -= len;
    memmove(buf->data, buf->data + len, buf->len);
}
