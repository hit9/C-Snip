// cc queue_example.c queue.c

#include <assert.h>
#include <stdio.h>
#include "queue.h"

int main(int argc, const char *argv[])
{
    /* allocate a new empty queue */
    struct queue *queue = queue();
    /* push data to queue */
    char *val1 = "val1";
    char *val2 = "val2";
    char *val3 = "val3";
    assert(queue_push(queue, val1) == QUEUE_OK);
    assert(queue_push(queue, val2) == QUEUE_OK);
    assert(queue_push(queue, val3) == QUEUE_OK);
    /* get queue len */
    printf("current queue length: %zu\n", queue_len(queue));
    /* pop data from queue, the order is the same with push */
    void *data;
    while ((data = queue_pop(queue)) != NULL)
        printf("pop data: %s\n", (char *)data);
    /* free queue */
    queue_free(queue);
    return 0;
}
