/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Double-linked list implementation.
 */

#ifndef _CW_LIST_H
#define _CW_LIST_H 1

#include <stdint.h>
#include "errors.h"

#if defined(__cplusplus)
extern "C" {
#endif

struct list_node {
    struct list_node *prev;  /* prev node */
    struct list_node *next;  /* next node */
    void * data;             /* node data */
};

struct list {
    struct list node *head;  /* head node */
    struct list node *tail;  /* last node */
    size_t size;             /* list size */
};

struct list_node *list_node_new(void *data);
void list_node_free(struct list_node *node);
struct list *list_new(void);
void list_free(struct list *list);
void list_clear(struct list *list);
error_t list_lpush(struct list *list, void *data);
error_t list_rpush(struct list *list, void *data);
void *list_lpop(struct list *list);
void *list_rpop(struct list *list);
void *list_head(struct list *list);

#if defined(__cplusplus)
}
#endif

#endif
