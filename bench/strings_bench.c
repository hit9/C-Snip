/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <stdio.h>

#include "bench.h"
#include "strings.h"

void case_strings_search(struct bench_ctx *ctx) {
    /* suite */
    int i;
    char strs[ctx->n][32];
    char subs[ctx->n][4];
    for (i = 0; i < ctx->n; i++) {
        sprintf(strs[i], "%d", i);
        sprintf(subs[i], "%d", i & 999);
    }
    /* bench */
    bench_ctx_reset_start_at(ctx);
    for (i = 0; i < ctx->n; i++) {
        strings_search(strs[i], subs[i], 0);
    }
    bench_ctx_reset_end_at(ctx);
}

void case_strings_replace(struct bench_ctx *ctx) {
    /* suite */
    int i;
    char strs[ctx->n][32];
    char subs[ctx->n][4];
    for (i = 0; i < ctx->n; i++) {
        sprintf(strs[i], "%d", i);
        sprintf(subs[i], "%d", i & 999);
    }
    /* bench */
    bench_ctx_reset_start_at(ctx);
    for (i = 0; i < ctx->n; i++) {
        char dst[100];
        strings_replace(dst, strs[i], subs[i], "rep");
    }
    bench_ctx_reset_end_at(ctx);
}

void case_strings_rand(struct bench_ctx *ctx) {
    int i;
    for (i = 0; i < ctx->n; i++) {
        char s[32];
        strings_rand(s, 32);
    }
}
