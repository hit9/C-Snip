/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <execinfo.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <signal.h>

#include "log.h"

static struct logger logger;

static void
on_sigsegv(int signal)
{
    if (signal == SIGSEGV) {
        log_trace();
        exit(1);
    }
}

/* Open global logger, if `filename` is NULL, use stderr.
 * The `rotate_size` only works when logging to a file,
 * and `rotate_size==0` means no rotation. */
int
log_open(char *name, char *filename, size_t rotate_size)
{
    assert(name != NULL);

    struct logger *l = &logger;

    l->name = name;
    l->level = LOG_INFO;
    l->filename = NULL;

    if (filename == NULL) {
        l->fd = STDERR_FILENO;
        l->rotate_size = 0;
        l->fsize = 0;
    } else {
        assert(strlen(filename) <= LOG_FILENAME_LEN_MAX);
        l->filename = filename;
        l->rotate_size = rotate_size;
        l->fd = open(filename, LOG_FILE_PERM, LOG_FILE_MODE);

        if (l->fd < 0) {
            return LOG_EOPEN;
        }

        struct stat st;
        if (fstat(l->fd, &st) != 0)
            return LOG_ESTAT;
        l->fsize = st.st_size;
    }

    // register traceback handler on segmentation fault
    struct sigaction signal_action;
    sigemptyset(&signal_action.sa_mask);
    signal_action.sa_flags = 0;
    signal_action.sa_handler = &on_sigsegv;
    sigaction(SIGSEGV, &signal_action, NULL);

    if (LOG_THREAD_SAFE)
        pthread_mutex_init(&(l->lock), NULL);
    return LOG_OK;
}

/* Close global logger. */
void
log_close(void)
{
    struct logger *l = &logger;

    if (LOG_THREAD_SAFE)
        pthread_mutex_destroy(&(l->lock));

    if (l->fd < 0 || l->fd == STDERR_FILENO)
        return;
    close(l->fd);
}

/* Reopen logging file. */
int
log_reopen(void)
{
    struct logger *l = &logger;

    if (l->fd < 0 || l->fd == STDERR_FILENO)
        return LOG_OK;

    close(l->fd);

    assert(l->filename != NULL);

    l->fd = open(l->filename, LOG_FILE_PERM, LOG_FILE_MODE);

    if (l->fd < 0)
        return LOG_EOPEN;
    return LOG_OK;
}

/* Set logger's level. */
void
log_setlevel(int level)
{
    struct logger *l = &logger;

    if (level > LOG_CRITICAL) {
        l->level = LOG_CRITICAL;
    } else if (level < LOG_DEBUG) {
        l->level = LOG_DEBUG;
    } else {
        l->level = level;
    }
}

/* Rotate log file. */
int
log_rotate(void) {
    struct logger *l = &logger;

    assert(l->name != NULL);
    assert(l->fd > 0 && l->fd != STDERR_FILENO);
    assert(l->filename != NULL);

    char buf[LOG_FILENAME_LEN_MAX];
    time_t sec;
    struct timeval tv;
    struct tm *tm;
    gettimeofday(&tv, NULL);
    sec = tv.tv_sec;
    tm = localtime(&sec);
    sprintf(buf, "%s.%04d%02d%02d-%02d%02d%03d",
            l->filename,
            tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
            tm->tm_hour, tm->tm_min, tm->tm_sec);

    if (rename(l->filename, buf))
        return LOG_ERENAME;
    l->fsize = 0;
    return log_reopen();
}

/* Format logging message to file/stderr. */
int
log_log(int level, char * levelname, const char *fmt, ...)
{
    struct logger *l = &logger;

    assert(levelname != NULL);
    assert(l->name != NULL);
    assert(l->fd == STDERR_FILENO || l->fd > 0);

    if (level < l->level)
        return LOG_OK;

    int len = 0, size = LOG_LINE_LEN_MAX;

    char buf[size + 1];

    // readable time with ms
    struct timeval tv;
    gettimeofday(&tv, NULL);

    len += strftime(buf + len, size - len, "%Y-%m-%d %H:%M:%S.", localtime(&tv.tv_sec));
    len += snprintf(buf + len, size - len, "%03ld", (long)tv.tv_usec/1000);
    // level
    len += snprintf(buf + len, size - len, " %s", levelname);
    // name and pid and tid
#ifdef __linux__
    /* using syacall to get tid, or `pid` on system view */
    long pid = (long)syscall(SYS_gettid);
#else
    /* I can't find a way to get tid from system view, only print the pid */
    long pid = getpid();
#endif
    len += snprintf(buf + len, size - len, " %s[%ld] ", l->name, pid);

    va_list args;
    va_start(args, fmt);
    len += vsnprintf(buf + len, size - len, fmt, args);
    va_end(args);

    if (len > LOG_LINE_LEN_MAX) {
        log_error("the log is too large");
        return LOG_ELINESIZE;
    }

    buf[len++] = '\n';

    if (LOG_THREAD_SAFE)
        pthread_mutex_lock(&(l->lock));

    if (write(l->fd, buf, len) < 0) {
        return LOG_EWRITE;
    } else if (l->filename != NULL) {
        l->fsize += len;
        if (l->rotate_size != 0) {
            if (l->fsize > l->rotate_size)
                log_rotate();
        }
    }

    if (LOG_THREAD_SAFE)
        pthread_mutex_unlock(&(l->lock));
    return LOG_OK;
}

void
log_trace(void)
{
    void *buf[32];
    size_t size = backtrace(buf, 32);
    char **symbols = backtrace_symbols(buf, size);

    if (symbols == NULL || size <= 0)
        return;

    size_t len_max = 1024 * size;
    char msg[len_max];
    size_t len = 0, i;

    for (i = 0; i < size; i++) {
        len += snprintf(msg + len, 1024, "  [%zu] %s", i, symbols[i]);
        if (i + 1 !=  size)
            msg[len++] = '\n';
    }
    log_error("trace:\n%.*s", len, msg);
    free(symbols);
}
