/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>

#include "queue.h"

/* Create new queue node. */
struct queue_node *queue_node_new(void *data) {
    struct queue_node *node = malloc(sizeof(struct queue_node));

    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

/* Free a queue node. */
void queue_node_free(struct queue_node *node) {
    if (node != NULL) free(node);
}

/* Create a empty queue */
struct queue *queue_new(void) {
    struct queue *queue = malloc(sizeof(struct queue));
    if (queue != NULL) {
        queue->head = NULL;
        queue->tail = NULL;
        queue->len = 0;
    }
    return queue;
}

/* Free queue. */
void queue_free(struct queue *queue) {
    if (queue != NULL) {
        queue_clear(queue);
        free(queue);
    }
}

/* Clear a queue. */
void queue_clear(struct queue *queue) {
    assert(queue != NULL);

    while (queue_len(queue) != 0) queue_pop(queue);
}

/* Get queue length. */
size_t queue_len(struct queue *queue) {
    assert(queue != NULL);
    return queue->len;
}

/* Push an item into the queue. */
int queue_push(struct queue *queue, void *data) {
    assert(queue != NULL);

    struct queue_node *node = queue_node_new(data);
    if (node == NULL) return QUEUE_ENOMEM;

    if (queue->len == 0) {
        assert(queue->head == NULL && queue->tail == NULL);
        queue->head = node;
        queue->tail = node;
    } else {
        assert(queue->head != NULL && queue->tail != NULL);
        queue->tail->next = node;
        queue->tail = node;
    }

    queue->len += 1;
    return QUEUE_OK;
}

/* Pop an item from the queue, NULL on empty */
void *queue_pop(struct queue *queue) {
    assert(queue != NULL);

    if (queue->len == 0) {
        assert(queue->head == NULL && queue->tail == NULL);
        return NULL;
    }
    assert(queue->head != NULL && queue->tail != NULL);
    struct queue_node *head = queue->head;

    queue->head = head->next;
    queue->len -= 1;

    if (queue->head == NULL) {
        assert(queue->len == 0);
        queue->tail = NULL;
    }

    void *data = head->data;
    queue_node_free(head);
    return data;
}

/* Get an item from the top if the queue, NULL on empty. */
void *queue_top(struct queue *queue) {
    assert(queue != NULL);

    if (queue->len == 0) {
        assert(queue->head == NULL && queue->tail == NULL);
        return NULL;
    }
    assert(queue->head != NULL && queue->tail != NULL);
    return queue->head->data;
}
