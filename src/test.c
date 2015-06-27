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
void case_string_isempty();
void case_string_isspace();
void case_string_startswith();
void case_string_endswith();
void case_string_ncmp();
void case_string_cmp();
void case_string_equals();
void case_string_index();
static struct test_case string_test_cases[] = {
    { "string_clear", &case_string_clear },
    { "string_put", &case_string_put },
    { "string_puts", &case_string_puts },
    { "string_putc", &case_string_putc },
    { "string_isempty", &case_string_isempty },
    { "string_isspace", &case_string_isspace },
    { "string_startswith", &case_string_startswith },
    { "string_endswith", &case_string_endswith },
    { "string_ncmp", &case_string_ncmp },
    { "string_cmp", &case_string_cmp },
    { "string_equals", &case_string_equals },
    { "string_index", &case_string_index },
    { NULL, NULL },
};

int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif
    run_cases("bool_test", bool_test_cases);
    run_cases("string_test", string_test_cases);
    return 0;
}
