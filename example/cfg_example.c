// cc cfg_example.c cfg.c buf.c

#include <assert.h>
#include <stdio.h>
#include "buf.h"
#include "cfg.h"

#define READ_UNIT   1024

int read_file_into_buffer(const char *filename, struct buf *buf);

int main(int argc, const char *argv[])
{
    /* Read file into buffer */
    struct buf *buf = buf_new(NULL);
    if (read_file_into_buffer("cfg_example.cfg", buf) != BUF_OK)
        return -1;

    /* Parse config */
    struct cfg cfg = {buf->data, buf->len, 1};
    int err = 0;
    cfg_each(cfg, err) {
        printf("%.*s => %.*s\n", (int)(cfg.key_len), cfg.key,
                (int)(cfg.val_len), cfg.val);
    }

    if (err == CFG_EBADFMT) {
        printf("bad format on line %ld\n", cfg.lineno);
        return -2;
    }

    buf_free(buf);
    return 0;
}

int
read_file_into_buffer(const char *filename, struct buf *buf)
{
    int nread;
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
        return -1;

    while (1) {
        if (buf_grow(buf, buf->len + READ_UNIT) != BUF_OK)
            return BUF_ENOMEM;

        if ((nread = fread(buf->data + buf->len, sizeof(char),
                    buf->cap - buf->len, fp)) <= 0)
            break;

        buf->len += nread;
    }
    return BUF_OK;
}
