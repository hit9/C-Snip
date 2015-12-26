/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include "log.h"

void
case_log_open_close()
{
    assert(log_open("test", NULL, 0) == LOG_OK);
    assert(log_open("test", "test.log", 0) == LOG_OK);
    assert(log_open("test", "test.log", 0) == LOG_OK);
    assert(log_open("test", "test.log", 1024) == LOG_OK);
    log_close();
}

void
case_log_log()
{
    assert(log_open("test", "test.log", 0) == LOG_OK);
    log_debug("test message debug");
    log_info("test message info");
    log_warn("test message warn");
    log_error("test message error");
    log_critical("test message critical");
    log_close();
}

void
case_log_rotate()
{
    assert(log_open("test", "test.log", 1024) == LOG_OK);
    int i;

    for (i = 0; i < 10; i++)
        log_info("test message");
}
