/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Simple configuration reader.
 * deps: None.
 *
 * example cfg string:
 *
 *     # proxy port
 *     port 8125
 *     # proxy backend nodes
 *     node 127.0.0.1:8126
 *     node 127.0.0.1:8127
 *     node 127.0.0.1:8128
 *
 * example usage:
 *
 *     struct cfg cfg;
 *     int err;
 *
 *     cfg.data = buf->data;
 *     cfg.len = buf->len;
 *     cfg.lineno = 0;
 *
 *     while ((err = cfg_get(&cfg)) == CFG_OK)
 *         printf("%.*s => %.*s\n", cfg.key_len, cfg.key
 *                     cfg.val_len, cfg.val);
 *
 *     if (err == CFG_EBADFMT)
 *         printf("bad format at line %ld", cfg.lineno);
 */

#ifndef _CW_CFG_H
#define _CW_CFG_H 1

#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

enum {
    CFG_OK = 0,      /* operation is ok */
    CFG_EOF = 1,     /* EOF reached */
    CFG_EBADFMT = 2, /* invalid format */
};

struct cfg {
    char *data;      /* currnt cfg data */
    size_t len;      /* currnt cfg data length */
    char *key;       /* current key */
    size_t key_len;  /* current key length */
    char *val;       /* current val */
    size_t val_len;  /* current val length */
    size_t lineno;   /* cfg lineno */
};

int cfg_get(struct cfg *cfg);

#if defined(__cplusplus)
}
#endif

#endif
