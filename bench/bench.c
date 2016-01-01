/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdio.h>
#include "bench.h"
#include "datetime.h"

/**
 * buf_bench
 */
void case_buf_puts(struct bench_ctx *ctx);
static struct bench_case buf_bench_cases[] = {
    { "buf_puts", &case_buf_puts, 1000000 },
    { NULL, NULL, 0},
};

/**
 * dict_bench
 */
void case_dict_set(struct bench_ctx *ctx);
void case_dict_get(struct bench_ctx *ctx);
void case_dict_pop(struct bench_ctx *ctx);
static struct bench_case dict_bench_cases[] = {
    { "dict_set", &case_dict_set, 1000000 },
    { "dict_get", &case_dict_get, 1000000 },
    { "dict_pop", &case_dict_pop, 1000000 },
    { NULL, NULL, 0 },
};

/**
 * heap_bench
 */
void case_heap_push(struct bench_ctx *ctx);
void case_heap_pop(struct bench_ctx *ctx);
void case_heap_top(struct bench_ctx *ctx);
static struct bench_case heap_bench_cases[] = {
    { "heap_push", &case_heap_push, 1000000 },
    { "heap_pop", &case_heap_pop, 1000000 },
    { "heap_top", &case_heap_top, 1000000 },
    { NULL, NULL, 0 },
};

/**
 * log_bench
 */
void case_log_devnull(struct bench_ctx *ctx);
static struct bench_case log_bench_cases[] = {
    { "log_devnull", &case_log_devnull, 1000000 },
    { NULL, NULL, 0 },
};

/**
 * map_bench
 */
void case_map_set(struct bench_ctx *ctx);
void case_map_get(struct bench_ctx *ctx);
void case_map_pop(struct bench_ctx *ctx);
static struct bench_case map_bench_cases[] = {
    { "map_set", &case_map_set, 1000000 },
    { "map_get", &case_map_get, 1000000 },
    { "map_pop", &case_map_pop, 1000000 },
    { NULL, NULL, 0 },
};

/**
 * skiplist_bench
 */
void case_skiplist_push(struct bench_ctx *ctx);
void case_skiplist_get(struct bench_ctx *ctx);
void case_skiplist_pop(struct bench_ctx *ctx);
void case_skiplist_popfirst(struct bench_ctx *ctx);
void case_skiplist_first(struct bench_ctx *ctx);
static struct bench_case skiplist_bench_cases[] = {
    { "skiplist_push", &case_skiplist_push, 1000000 },
    { "skiplist_get", &case_skiplist_get, 1000000 },
    { "skiplist_pop", &case_skiplist_pop, 1000000 },
    { "skiplist_first", &case_skiplist_first, 1000000 },
    { NULL, NULL, 0 },
};

/**
 * strings_bench
 */
void case_strings_search(struct bench_ctx *ctx);
void case_strings_replace(struct bench_ctx *ctx);
void case_strings_rand(struct bench_ctx *ctx);
static struct bench_case strings_bench_cases[] = {
    { "strings_search", &case_strings_search, 1000000 },
    { "strings_replace", &case_strings_replace, 1000000 },
    { "strings_rand", &case_strings_rand, 1000000 },
    { NULL, NULL, 0 },
};

/**
 * bench
 */
void
bench_ctx_reset_start_at(struct bench_ctx *ctx)
{
    assert(ctx != NULL);
    ctx->start_at = datetime_stamp_now();
}

void
bench_ctx_reset_end_at(struct bench_ctx *ctx)
{
    assert(ctx != NULL);
    ctx->end_at = datetime_stamp_now();
}

static void
run_cases(const char *name, struct bench_case cases[])
{
    int idx = 0;

    while (1) {
        struct bench_case c = cases[idx];
        if (c.name == NULL || c.fn == NULL)
            break;
        fprintf(stderr, "%-17s %-27s ", name, c.name);
        struct bench_ctx ctx = {datetime_stamp_now(), -1, c.n};
        (c.fn)(&ctx);
        double start_at = ctx.start_at;
        double end_at = ctx.end_at;
        if (end_at < 0) end_at = datetime_stamp_now();
        idx += 1;
        fprintf(stderr, "%-17ld%17ldns/op\n", c.n,
                (long)(1000000.0*(end_at-start_at)/(double)c.n));
    }
}

int main(int argc, const char *argv[])
{
    run_cases("buf_bench", buf_bench_cases);
    run_cases("dict_bench", dict_bench_cases);
    run_cases("heap_bench", heap_bench_cases);
    run_cases("log_stderr", log_bench_cases);
    run_cases("map_bench", map_bench_cases);
    run_cases("skiplist_bench", skiplist_bench_cases);
    run_cases("strings_bench", strings_bench_cases);
    return 0;
}
