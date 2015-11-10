/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#ifdef __linux
#include <mcheck.h>
#endif

#include "test.h"

/**
 * bool_test
 */
void case_bool_true();
void case_bool_false();
static struct test_case bool_test_cases[] = {
    { "bool_true", &case_bool_true },
    { "bool_false", &case_bool_false },
    { NULL, NULL },
};

/**
 * buf_test
 */
void case_buf_clear();
void case_buf_put();
void case_buf_puts();
void case_buf_putc();
void case_buf_str();
void case_buf_isempty();
void case_buf_sprintf();
void case_buf_lrm();
static struct test_case buf_test_cases[] = {
    { "buf_clear", &case_buf_clear },
    { "buf_put", &case_buf_put },
    { "buf_puts", &case_buf_puts },
    { "buf_putc", &case_buf_putc },
    { "buf_str", &case_buf_str },
    { "buf_isempty", &case_buf_isempty },
    { "buf_sprintf", &case_buf_sprintf },
    { "buf_lrm", &case_buf_lrm },
    { NULL, NULL },
};

/**
 * stack_test
 */
void case_stack_clear();
void case_stack_push();
void case_stack_pop();
void case_stack_top();
static struct test_case stack_test_cases[] = {
    { "stack_clear", &case_stack_clear },
    { "stack_push", &case_stack_push },
    { "stack_pop", &case_stack_pop },
    { "stack_top", &case_stack_top },
    { NULL, NULL },
};

/**
 * queue_test
 */
void case_queue_clear();
void case_queue_push_pop_top();
static struct test_case queue_test_cases[] = {
    { "queue_clear", &case_queue_clear },
    { "queue_push_pop_top", &case_queue_push_pop_top },
    { NULL, NULL },
};

/**
 * list_test
 */
void case_list_clear();
void case_list_lpush();
void case_list_rpush();
void case_list_lpop();
void case_list_rpop();
void case_list_iter();
static struct test_case list_test_cases[] = {
    { "list_clear", &case_list_clear },
    { "list_lpush", &case_list_lpush },
    { "list_rpush", &case_list_rpush },
    { "list_lpop", &case_list_lpop },
    { "list_rpop", &case_list_rpop },
    { "list_iter", &case_list_iter },
    { NULL, NULL },
};

/**
 * dict_test
 */
void case_dict_set();
void case_dict_get();
void case_dict_pop();
void case_dict_has();
void case_dict_clear();
void case_dict_resize();
void case_dict_iter();
static struct test_case dict_test_cases[] = {
    { "dict_set", &case_dict_set },
    { "dict_get", &case_dict_get },
    { "dict_pop", &case_dict_pop },
    { "dict_has", &case_dict_has },
    { "dict_clear", &case_dict_clear },
    { "dict_resize", &case_dict_resize },
    { "dict_iter", &case_dict_iter },
    { NULL, NULL },
};

/**
 * utils_test
 */
void case_utils_bm_search();
static struct test_case utils_test_cases[] = {
    { "bm_search", &case_utils_bm_search},
    { NULL, NULL },
};

/**
 * event_test
 */
void case_event_simple();
static struct test_case event_test_cases[] = {
    { "event_simple", &case_event_simple },
    { NULL, NULL },
};

/**
 * ketama_test
 */
void case_ketama_balance();
void case_ketama_consistence();
static struct test_case ketama_test_cases[] = {
    { "ketama_balance", &case_ketama_balance },
    { "ketama_consistence", &case_ketama_consistence },
    { NULL, NULL },
};

/**
 * cfg_test
 */
void case_cfg_get();
static struct test_case cfg_test_cases[] = {
    { "cfg_get", &case_cfg_get },
    { NULL, NULL },
};

/**
 * log_test
 */
void case_log_open_close();
void case_log_log();
void case_log_rotate();
static struct test_case log_test_cases[] = {
    { "log_open_close", &case_log_open_close },
    { "log_log", &case_log_log },
    { "log_rotate", &case_log_rotate},
    { NULL, NULL },
};


int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif
    printf("=========== test start ========\n");
    run_cases("bool_test", bool_test_cases);
    run_cases("buf_test", buf_test_cases);
    run_cases("stack_test", stack_test_cases);
    run_cases("queue_test", queue_test_cases);
    run_cases("list_test", list_test_cases);
    run_cases("dict_test", dict_test_cases);
    run_cases("utils_test", utils_test_cases);
    run_cases("event_test", event_test_cases);
    run_cases("ketama_test", ketama_test_cases);
    run_cases("cfg_get", cfg_test_cases);
    run_cases("log_test", log_test_cases);
    printf("=========== test end ========\n");
    return 0;
}
