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

#define list()                 list_new()
#define list_iterator(list)    list_iterator_new(list)
#define list_push(list, data)  list_rpush(list, data)
#define list_pop(list)         list_lpop(list)

struct list_node {
    struct list_node *prev;  /* prev node */
    struct list_node *next;  /* next node */
    void * data;             /* node data */
};

struct list {
    struct list_node *head;  /* head node */
    struct list_node *tail;  /* last node */
    size_t size;             /* list size */
};

struct list_iterator {
    struct list *list;
    struct list_node *node;
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
void *list_tail(struct list *list);
struct list_iterator *list_iterator_new(struct list *list);
void list_iterator_free(struct list_iterator *iterator);
void *list_iterator_next(struct list_iterator *iterator);
void *list_iterator_prev(struct list_iterator *iterator);
void list_iterator_seek_head(struct list_iterator *iterator);
void list_iterator_seek_tail(struct list_iterator *iterator);

#if defined(__cplusplus)
}
#endif

#endif
