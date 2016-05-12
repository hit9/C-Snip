/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdio.h>
#include "bench.h"
#include "skiplist.h"

void case_skiplist_push(struct bench_ctx *ctx) {
    struct skiplist *sl = skiplist(NULL);

    int i;
    bench_ctx_reset_start_at(ctx);
    for (i = 0; i < ctx->n; i++) {
        skiplist_push(sl, i, "v");
    }
    bench_ctx_reset_end_at(ctx);
    skiplist_free(sl);
}

void case_skiplist_get(struct bench_ctx *ctx) {
    struct skiplist *sl = skiplist(NULL);

    int i;
    for (i = 0; i < ctx->n; i++) {
        skiplist_push(sl, i, "v");
    }
    bench_ctx_reset_start_at(ctx);
    for (i = 0; i < ctx->n; i++) {
        skiplist_get(sl, i);
    }
    bench_ctx_reset_end_at(ctx);
    skiplist_free(sl);
}

void case_skiplist_pop(struct bench_ctx *ctx) {
    struct skiplist *sl = skiplist(NULL);

    int i;
    for (i = 0; i < ctx->n; i++) {
        skiplist_push(sl, i, "v");
    }
    bench_ctx_reset_start_at(ctx);
    for (i = 0; i < ctx->n; i++) {
        skiplist_pop(sl, i);
    }
    bench_ctx_reset_end_at(ctx);
    skiplist_free(sl);
}

void case_skiplist_popfirst(struct bench_ctx *ctx) {
    struct skiplist *sl = skiplist(NULL);

    int i;
    for (i = 0; i < ctx->n; i++) {
        skiplist_push(sl, i, "v");
    }
    bench_ctx_reset_start_at(ctx);
    for (i = 0; i < ctx->n; i++) {
        skiplist_popfirst(sl);
    }
    bench_ctx_reset_end_at(ctx);
    skiplist_free(sl);
}

void case_skiplist_first(struct bench_ctx *ctx) {
    struct skiplist *sl = skiplist(NULL);

    int i;
    for (i = 0; i < ctx->n; i++) {
        skiplist_push(sl, i, "v");
    }
    bench_ctx_reset_start_at(ctx);
    for (i = 0; i < ctx->n; i++) {
        skiplist_first(sl);
    }
    bench_ctx_reset_end_at(ctx);
    skiplist_free(sl);
}
