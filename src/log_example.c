// cc log_example.c log.c utils.c

#include "log.h"

int main(int argc, const char *argv[])
{
    log_open("example", NULL, 0);
    log_info("info message");
    log_warn("warn message");
    return 0;
}
