/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include "bench.h"
#include "buf.h"

void
case_buf_puts(struct bench_ctx *ctx)
{
    struct buf *buf = buf(NULL);
    int i;
    bench_ctx_reset_start_at(ctx);
    for (i = 0; i < ctx->n; i++) {
        buf_puts(buf, "abcdefg");
    }
    bench_ctx_reset_end_at(ctx);
    buf_free(buf);
}
