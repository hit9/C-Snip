/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include "queue.h"

void
case_queue_clear()
{
    struct queue *queue = queue();
    queue_push(queue, "a");
    queue_push(queue, "a");
    queue_clear(queue);
    assert(queue->head == NULL);
    assert(queue->tail == NULL);
    assert(queue_len(queue) == 0);
    queue_free(queue);
}

void
case_queue_push_pop_top()
{
    struct queue *queue = queue();
    char *s1 = "a", *s2 = "b", *s3 = "c";
    assert(queue_push(queue, s1) == QUEUE_OK);
    assert(queue_push(queue, s2) == QUEUE_OK);
    assert(queue_push(queue, s3) == QUEUE_OK);
    assert(queue_len(queue) == 3);
    assert(queue_top(queue) == s1);
    assert(queue_pop(queue) == s1);
    assert(queue_top(queue) == s2);
    assert(queue_pop(queue) == s2);
    assert(queue_top(queue) == s3);
    assert(queue_pop(queue) == s3);
    assert(queue_len(queue) == 0);
    queue_free(queue);
}
