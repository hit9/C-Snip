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

#define skiplist()            skiplist_new()
#define skiplist_height(sl)   skiplist_level(sl)

enum {
    SKIPLIST_OK = 0,        /* operation is ok */
    SKIPLIST_ENOMEM = 1,    /* no memory error */
};

struct skiplist_node {
    unsigned long score;             /* node score */
    void *data;                      /* node data */
    struct skiplist_node **forwards; /* node forward links */
    struct skiplist_node *backward;  /* node backward link */
};

struct skiplist {
    size_t len;                 /* skiplist length */
    int level;                  /* skiplist level */
    struct skiplist_node *head; /* skiplist head */
    struct skiplist_node *tail; /* skiplist tail */
};

struct skiplist_node *skiplist_node_new(int level, unsigned long score, void *data);
void skiplist_node_free(struct skiplist_node *node);
struct skiplist *skiplist_new(void);
void skiplist_free(struct skiplist *skiplist);
void skiplist_clear(struct skiplist *skiplist);
size_t skiplist_len(struct skiplist *skiplist); /* O(1) */
int skiplist_level(struct skiplist *skiplist); /* O(1) */
int skiplist_push(struct skiplist *skiplist, unsigned long score, void *data); /* O(logN) */
void *skiplist_search(struct skiplist *skiplist, unsigned long score); /* O(logN) */
void *skiplist_pop(struct skiplist *skiplist, unsigned long score); /* O(logN) */
void *skiplist_popfirst(struct skiplist *skiplist); /* O(1) */
void *skiplist_poplast(struct skiplist *skiplist); /* O(logN) */
struct skiplist_node *skiplist_first(struct skiplist *skiplist); /* O(1) */
struct skiplist_node *skiplist_last(struct skiplist *skiplist); /* O(1) */
void skiplist_print(struct skiplist *skiplist);

#if defined(__cplusplus)
}
#endif

#endif
