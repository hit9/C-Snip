/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Double-linked list implementation.
 */

#ifndef _CW_LIST_H
#define _CW_LIST_H 1

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define list()                 list_new()
#define list_iter(list)        list_iter_new(list)
#define list_push(list, data)  list_rpush(list, data)
#define list_pop(list)         list_lpop(list)

enum {
    LIST_OK = 0,             /* operation is ok */
    LIST_ENOMEM = 1,         /* no memory error */
};

struct list_node {
    struct list_node *prev;  /* prev node */
    struct list_node *next;  /* next node */
    void * data;             /* node data */
};

struct list {
    struct list_node *head;  /* head node */
    struct list_node *tail;  /* last node */
    size_t len;              /* list length */
};

struct list_iter {
    struct list *list;       /* list to iterate */
    struct list_node *node;  /* current list node */
};

struct list_node *list_node_new(void *data);
void list_node_free(struct list_node *node);
struct list *list_new(void);
void list_free(struct list *list);
void list_clear(struct list *list);
size_t list_len(struct list *list); /* O(1) */
int list_lpush(struct list *list, void *data); /* O(1) */
int list_rpush(struct list *list, void *data); /* O(1) */
void *list_lpop(struct list *list); /* O(1) */
void *list_rpop(struct list *list); /* O(1) */
void *list_head(struct list *list); /* O(1) */
void *list_tail(struct list *list); /* O(1) */
struct list_iter *list_iter_new(struct list *list);
void list_iter_free(struct list_iter *iter);
void *list_iter_next(struct list_iter *iter);
void *list_iter_prev(struct list_iter *iter);
void list_iter_seek_head(struct list_iter *iter);
void list_iter_seek_tail(struct list_iter *iter);

#if defined(__cplusplus)
}
#endif

#endif
