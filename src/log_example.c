// cc log_example.c log.c -rdynamic

#include "log.h"

void
make_segmentfault()
{
    char *s = NULL;
    char ch = s[1]; // segment fault
}

int main(int argc, const char *argv[])
{
    /* open global logger to stderr (by setting filename to NULL) */
    log_open("example", NULL, 0);
    /* set log level to info, also the default level */
    log_setlevel(LOG_INFO);
    /* debug mesage won't be seen */
    log_debug("debug message");
    /* but info and warn, error message can be seen */
    log_info("info message");
    log_warn("warn message");
    log_error("error message");
    /* will log trace back on segmentfault automatically */
    make_segmentfault();
    return 0;
}
