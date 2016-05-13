/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <stdio.h>

#include "bench.h"
#include "map.h"

void case_map_set(struct bench_ctx *ctx) {
    struct map *m = map();
    /* keys suite */
    int i;
    char keys[ctx->n][4];
    for (i = 0; i < ctx->n; i++) sprintf(keys[i], "%d", i & 999);
    /* bench */
    bench_ctx_reset_start_at(ctx);
    for (i = 0; i < ctx->n; i++) {
        map_set(m, keys[i], "val");
    }
    bench_ctx_reset_end_at(ctx);
    map_free(m);
}

void case_map_get(struct bench_ctx *ctx) {
    struct map *m = map();
    /* suite */
    int i;
    char keys[ctx->n][4];
    for (i = 0; i < ctx->n; i++) {
        sprintf(keys[i], "%d", i & 999);
        map_set(m, keys[i], "val");
    }
    /* bench */
    bench_ctx_reset_start_at(ctx);
    for (i = 0; i < ctx->n; i++) {
        map_get(m, keys[i]);
    }
    bench_ctx_reset_end_at(ctx);
    map_free(m);
}

void case_map_pop(struct bench_ctx *ctx) {
    struct map *m = map();
    /* suite */
    int i;
    char keys[ctx->n][4];
    for (i = 0; i < ctx->n; i++) {
        sprintf(keys[i], "%d", i & 999);
        map_set(m, keys[i], "val");
    }
    /* bench */
    bench_ctx_reset_start_at(ctx);
    for (i = 0; i < ctx->n; i++) {
        map_pop(m, keys[i]);
    }
    bench_ctx_reset_end_at(ctx);
    map_free(m);
}
