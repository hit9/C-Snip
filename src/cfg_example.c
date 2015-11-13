// cc cfg_example.c cfg.c buf.c

#include <assert.h>
#include <stdio.h>
#include "buf.h"
#include "cfg.h"

#define READ_UNIT   1024

int main(int argc, const char *argv[])
{
    /* Read file into buffer */
    struct buf *buf = buf_new(NULL);
    int nread;
    FILE *fp = fopen("cfg_example.cfg", "r");

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

    /* Parse config */
    struct cfg cfg;

    cfg.data = buf->data;   /* data to parse */
    cfg.len = buf->len;     /* data length to parse */
    cfg.lineno = 1;         /* initialize line number */

    int cfg_err;

    while ((cfg_err = cfg_get(&cfg)) == CFG_OK) {
        printf("%.*s => %.*s\n", (int)(cfg.key_len), cfg.key,
                (int)(cfg.val_len), cfg.val);
    }

    buf_free(buf);

    if (cfg_err == CFG_EBADFMT) {
        printf("bad format on line %ld\n", cfg.lineno);
        return -1;
    }

    return 0;
}
