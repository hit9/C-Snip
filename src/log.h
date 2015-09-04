/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Logging implementation.
 */

#ifndef _CW_LOG_H
#define _CW_LOG_H 1

#include <fcntl.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define LOG_LINE_LEN_MAX    256
#define LOG_FILE_MODE       0644
#define LOG_FILE_PERM       O_WRONLY | O_APPEND | O_CREAT

enum {
    LOG_DEBUG = 10,
    LOG_INFO = 20,
    LOG_WARN = 30,
    LOG_ERROR = 40,
    LOG_CRITICAL = 50,
};

enum {
    LOG_OK = 0,     /* operation is ok */
    LOG_EOPEN = 1,  /* failed to open file */
    LOG_EWRITE = 2, /* failed to write to file */
};

struct logger {
    char *name;       /* logger name */
    char *filename;   /* filename to log */
    int level;        /* logging level */
    int fd;           /* fd to write */
};

#define log_debug(...)      log_log(LOG_DEBUG, __VA_ARGS__)
#define log_info(...)       log_log(LOG_INFO, __VA_ARGS__)
#define log_warn(...)       log_log(LOG_WARN, __VA_ARGS__)
#define log_error(...)      log_log(LOG_ERROR, __VA_ARGS__)
#define log_critical(...)   log_log(LOG_CRITICAL, __VA_ARGS__)

int log_open(char *name, char *filename);
void log_close(void);
int log_reopen(void);
void log_setlevel(int level);
int log_log(int level, const char *fmt, ...);

#if defined(__cplusplus)
}
#endif

#endif
