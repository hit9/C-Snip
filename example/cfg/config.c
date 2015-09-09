/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <stdio.h>
#include "buf.h"
#include "cfg.h"

#define READ_UNIT   1024

int
main(int argc, const char *argv[])
{

    struct buf *buf = buf_new(NULL);
    int nread;
    FILE *fp = fopen("config.cfg", "r");

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

    struct cfg cfg;

    cfg.data = buf->data;
    cfg.len = buf->len;

    int cfg_err;

    while ((cfg_err = cfg_get(&cfg)) == CFG_OK) {
        printf("%.*s => %.*s\n", (int)(cfg.key_len), cfg.key,
                (int)(cfg.val_len), cfg.val);
    }

    buf_free(buf);

    if (cfg_err == CFG_EBADFMT) {
        printf("bad format on line %d\n", cfg.lineno);
        return -1;
    }

    return 0;
}
