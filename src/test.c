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
    { "bool true", &case_bool_true },
    { "bool false", &case_bool_false },
    { NULL, NULL },
};

/**
 * string_test
 */
void case_string_clear();
void case_string_put();
void case_string_puts();
void case_string_putc();
void case_string_concat();
void case_string_isempty();
void case_string_isspace();
void case_string_startswith();
void case_string_endswith();
void case_string_ncmp();
void case_string_cmp();
void case_string_equals();
void case_string_index();
void case_string_reverse();
void case_string_sprintf();
void case_string_search();
static struct test_case string_test_cases[] = {
    { "string_clear", &case_string_clear },
    { "string_put", &case_string_put },
    { "string_puts", &case_string_puts },
    { "string_putc", &case_string_putc },
    { "string_concat", &case_string_concat },
    { "string_isempty", &case_string_isempty },
    { "string_isspace", &case_string_isspace },
    { "string_startswith", &case_string_startswith },
    { "string_endswith", &case_string_endswith },
    { "string_ncmp", &case_string_ncmp },
    { "string_cmp", &case_string_cmp },
    { "string_equals", &case_string_equals },
    { "string_index", &case_string_index },
    { "string_reverse", &case_string_reverse },
    { "string_sprintf", &case_string_sprintf },
    { "string_search", &case_string_search },
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
    { "case_queue_push_pop_top", &case_queue_push_pop_top },
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
void case_list_iterator();
static struct test_case list_test_cases[] = {
    { "list_clear", &case_list_clear },
    { "list_lpush", &case_list_lpush },
    { "list_rpush", &case_list_rpush },
    { "list_lpop", &case_list_lpop },
    { "list_rpop", &case_list_rpop },
    { "list_iterator", &case_list_iterator },
    { NULL, NULL },
};

/**
 * dict_test.c
 */
void case_dict_set();
void case_dict_get();
void case_dict_pop();
void case_dict_has();
void case_dict_clear();
void case_dict_resize();
void case_dict_iterator();
static struct test_case dict_test_cases[] = {
    { "dict_set", &case_dict_set },
    { "dict_get", &case_dict_get },
    { "dict_pop", &case_dict_pop },
    { "dict_has", &case_dict_has },
    { "dict_clear", &case_dict_clear },
    { "dict_resize", &case_dict_resize },
    { "dict_iterator", &case_dict_iterator },
    { NULL, NULL },
};

int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif
    run_cases("bool_test", bool_test_cases);
    run_cases("string_test", string_test_cases);
    run_cases("stack_test", stack_test_cases);
    run_cases("queue_test", queue_test_cases);
    run_cases("list_test", list_test_cases);
    run_cases("dict_test", dict_test_cases);
    return 0;
}
