// cc datetime_example.c datetime.c

#include <stdio.h>
#include "datetime.h"

int main(int argc, const char *argv[])
{
    /* get current timstamp (in milliseconds) */
    printf("timstamp (ms) for now is: %.3f ms\n", datetime_stamp_now());
    return 0;
}
