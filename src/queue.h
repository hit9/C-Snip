/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * List based queue implementation.
 */

#ifndef _CW_QUEUE_H
#define _CW_QUEUE_H 1

#include <stdint.h>
#include "errors.h"

#define queue()  queue_new()

struct queue_node {
    void **data;              /* node data */
    struct queue_node *next;  /* next node */
};

struct queue {
    struct queue_node *head;  /* head node */
    struct queue_node *tail;  /* last node */
    size_t size;              /* queue size */
};

struct queue_node *queue_node_new(void *data);
void queue_node_free(struct queue_node *node);
struct queue *queue_new(void);
void queue_free(struct queue *queue);
void queue_clear(struct queue *queue);
error_t queue_push(struct queue *queue, void *data);
void *queue_pop(struct queue *queue);
void *queue_top(struct queue *queue);

#endif
