/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#include "log.h"
#include "utils.h"

static struct logger logger;

/* Open global logger, if `filename` is NULL, use stderr. */
int
log_open(char *name, char *filename)
{
    assert(name != NULL);

    struct logger *l = &logger;

    l->name = name;
    l->level = LOG_INFO;
    l->filename = NULL;

    if (filename == NULL) {
        l->fd = STDERR_FILENO;
    } else {
        l->filename = filename;
        l->fd = open(filename, LOG_FILE_PERM, LOG_FILE_MODE);

        if (l->fd < 0) {
            return LOG_EOPEN;
        }
    }

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
;
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
    l->level = MAX(MIN(LOG_CRITICAL, level), LOG_DEBUG);
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
    len += _scnprintf(buf + len, size - len, "%03ld", tv.tv_usec/1000);
    // level
    len += _scnprintf(buf + len, size - len, " %s", levelname);
    // name and pid and tid
    len += _scnprintf(buf + len, size - len, " %s[%ld/%ld] ", l->name, getpid(), pthread_self());

    va_list args;
    va_start(args, fmt);
    len += _vscnprintf(buf + len, size - len, fmt, args);
    va_end(args);

    buf[len++] = '\n';

    if (LOG_THREAD_SAFE)
        pthread_mutex_lock(&(l->lock));

    if (write(l->fd, buf, len) < 0) {
        return LOG_EWRITE;
    }

    if (LOG_THREAD_SAFE)
        pthread_mutex_unlock(&(l->lock));
    return LOG_OK;
}
