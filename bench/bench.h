/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

struct bench_ctx {
    double start_at;  /* bench start_at */
    double end_at;    /* bench end_at */
    long n;           /* bench times */
};

struct bench_case {
    const char *name; /* bench case name */
    void (*fn)(struct bench_ctx *ctx); /* bench function */
    long n; /* bench times */
};

void bench_ctx_reset_start_at(struct bench_ctx *ctx);
void bench_ctx_reset_end_at(struct bench_ctx *ctx);
