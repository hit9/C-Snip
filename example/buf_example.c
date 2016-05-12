// cc buf_example.c buf.c

#include <assert.h>
#include <stdio.h>
#include "buf.h"

int main(int argc, const char *argv[]) {
    struct buf *buf = buf("example");
    /* test if buffer is empty or NULL */
    assert(buf != NULL && !buf_isempty(buf));
    /* put string to buffer */
    assert(buf_puts(buf, "abc") == BUF_OK);
    /* put char to buffer */
    assert(buf_putc(buf, 'd') == BUF_OK);
    /* format data into buffer */
    assert(buf_sprintf(buf, "%s%d", "efg", 123) == BUF_OK);
    /* print buffer, should be "exampleabcdefg123" */
    printf("%s\n", str(buf));
    /* get buffer length */
    printf("current buffer length is %zu, capacity is %zu\n", buf_len(buf),
           buf_cap(buf));
    /* free buffer */
    buf_free(buf);
    return 0;
}
