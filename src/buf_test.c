/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <string.h>
#include "test.h"
#include "buf.h"

void
case_buf_clear()
{
    struct buf *buf1 = buf("test");
    struct buf *buf2 = buf(NULL);
    assert(!buf_isempty(buf1));
    assert(buf_isempty(buf2));
    buf_clear(buf1);
    buf_clear(buf2);
    assert(buf_isempty(buf1));
    assert(buf_isempty(buf2));
    buf_free(buf1);
    buf_free(buf2);
}

void
case_buf_put()
{
    struct buf *buf = buf(NULL);
    assert(buf_put(buf, "abc", 3) == BUF_OK);
    assert(strcmp(str(buf), "abc") == 0);
    assert(buf_put(buf, "efg", 3) == BUF_OK);
    assert(strcmp(str(buf), "abcefg") == 0);
    buf_free(buf);
}

void
case_buf_puts()
{
    struct buf *buf = buf(NULL);
    assert(buf_puts(buf, "abc") == BUF_OK);
    assert(strcmp(str(buf), "abc") == 0);
    assert(buf_puts(buf, "efg") == BUF_OK);
    assert(strcmp(str(buf), "abcefg") == 0);
    buf_free(buf);
}

void
case_buf_putc()
{
    struct buf *buf = buf(NULL);
    assert(buf_putc(buf, 'a') == BUF_OK);
    assert(buf_putc(buf, 'b') == BUF_OK);
    assert(buf_putc(buf, 'c') == BUF_OK);
    assert(buf_putc(buf, 'd') == BUF_OK);
    assert(strcmp(str(buf), "abcd") == 0);
    buf_free(buf);
}

void
case_buf_str()
{
    struct buf *buf = buf(NULL);
    assert(strcmp(str(buf), "") == 0);
    buf_puts(buf, "abcdef");
    assert(strcmp(str(buf), "abcdef") == 0);
    buf_free(buf);
}

void
case_buf_sprintf()
{
    struct buf *buf = buf(NULL);
    assert(buf_sprintf(buf, "%s %s!", "hello", "world") == BUF_OK);
    assert(strcmp(buf_str(buf), "hello world!") == 0);
    buf_free(buf);
}

void
case_buf_isempty()
{
    struct buf *buf1 = buf("test");
    struct buf *buf2 = buf(NULL);
    assert(!buf_isempty(buf1));
    assert(buf_isempty(buf2));
    buf_free(buf1);
    buf_free(buf2);
}
