/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <stdio.h>
#include "bench.h"
#include "log.h"

void case_log_devnull(struct bench_ctx *ctx) {
    log_open("bench", "/dev/null", 0);
    bench_ctx_reset_start_at(ctx);
    int i;
    for (i = 0; i < ctx->n; i++) {
        log_info("hello %s", "world");
    }
    bench_ctx_reset_end_at(ctx);
}
