/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Skiplist implementation.
 * deps: None.
 */

#ifndef _CW_SKIPLIST_H
#define _CW_SKIPLIST_H 1


#if defined(__cplusplus)
extern "C" {
#endif

#define SKIPLIST_LEVEL_MAX    12   /* max skiplist level (0~11) */
#define SKIPLIST_FACTOR_P     0.25

#define skiplist(cmp)         skiplist_new(cmp)

/* skiplist node comparator type, return negative if arg#0 < arg#1 */
typedef int (*skiplist_cmp_t)(void *, void *);

enum {
    SKIPLIST_OK = 0,     /* operation is ok */
    SKIPLIST_ENOMEM = 1, /* no memory error */
};

struct skiplist_node {
    void *data;                      /* node data */
    struct skiplist_node **forwards; /* node links */
};

struct skiplist {
    size_t len;                 /* skiplist length */
    int level;                  /* skiplist level */
    struct skiplist_node *head; /* skiplist head */
    skiplist_cmp_t cmp;         /* node data comparator */
};

struct skiplist_node *skiplist_node_new(int level, void *data);
void skiplist_node_free(struct skiplist_node *node);
struct skiplist *skiplist_new(skiplist_cmp_t cmp);
void skiplist_free(struct skiplist *skiplist);
void skiplist_clear(struct skiplist *skiplist);
size_t skiplist_len(struct skiplist *skiplist); /* O(1) */
int skiplist_push(struct skiplist *skiplist, void *data); /* O(logN) */
void *skiplist_top(struct skiplist *skiplist); /* O(1) */
void *skiplist_pop(struct skiplist *skiplist); /* O(1) */

#if defined(__cplusplus)
}
#endif

#endif
