/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * List based queue implementation.
 * deps: None.
 */

#ifndef _CW_QUEUE_H
#define _CW_QUEUE_H 1

#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define queue()  queue_new()

enum {
    QUEUE_OK = 0,             /* operation is ok */
    QUEUE_ENOMEM = 1,         /* no memory error */
};

struct queue_node {
    void *data;               /* node data */
    struct queue_node *next;  /* next node */
};

struct queue {
    struct queue_node *head;  /* head node */
    struct queue_node *tail;  /* last node */
    size_t len;               /* queue length */
};

struct queue_node *queue_node_new(void *data);
void queue_node_free(struct queue_node *node);
struct queue *queue_new(void);
void queue_free(struct queue *queue);
void queue_clear(struct queue *queue);
size_t queue_len(struct queue *queue); /* O(1) */
int queue_push(struct queue *queue, void *data); /* O(1) */
void *queue_pop(struct queue *queue); /* O(1) */
void *queue_top(struct queue *queue); /* O(1) */

#if defined(__cplusplus)
}
#endif

#endif
