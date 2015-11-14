// cc log_example.c log.c

#include "log.h"

int main(int argc, const char *argv[])
{
    log_open("example", NULL, 0);
    /* set log level to info, also the default level */
    log_setlevel(LOG_INFO);
    /* debug mesage won't be seen */
    log_debug("debug message");
    /* but info and warn message can be seen */
    log_info("info message");
    log_warn("warn message");
    return 0;
}
