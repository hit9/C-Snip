/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <stdio.h>
#include "bench.h"
#include "dict.h"

void
case_dict_set(struct bench_ctx *ctx)
{
    struct dict *dict = dict();
    /* keys suite */
    int i;
    char keys[ctx->n][4];
    for (i = 0; i < ctx->n; i++)
        sprintf(keys[i], "%d", i & 999);
    /* bench */
    bench_ctx_reset_start_at(ctx);
    for (i = 0; i < ctx->n; i++) {
        dict_set(dict, keys[i], "val");
    }
    bench_ctx_reset_end_at(ctx);
    dict_free(dict);
}

void
case_dict_get(struct bench_ctx *ctx)
{
    struct dict *dict = dict();
    /* suite */
    int i;
    char keys[ctx->n][4];
    for (i = 0; i < ctx->n; i++) {
        sprintf(keys[i], "%d", i & 999);
        dict_set(dict, keys[i], "val");
    }
    /* bench */
    bench_ctx_reset_start_at(ctx);
    for (i = 0; i < ctx->n; i++) {
        dict_get(dict, keys[i]);
    }
    bench_ctx_reset_end_at(ctx);
    dict_free(dict);
}

void
case_dict_pop(struct bench_ctx *ctx)
{
    struct dict *dict = dict();
    /* suite */
    int i;
    char keys[ctx->n][4];
    for (i = 0; i < ctx->n; i++) {
        sprintf(keys[i], "%d", i & 999);
        dict_set(dict, keys[i], "val");
    }
    /* bench */
    bench_ctx_reset_start_at(ctx);
    for (i = 0; i < ctx->n; i++) {
        dict_pop(dict, keys[i]);
    }
    bench_ctx_reset_end_at(ctx);
    dict_free(dict);
}
