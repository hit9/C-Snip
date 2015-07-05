/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Array based stack implementation.
 */

#ifndef _CW_STACK_H
#define _CW_STACK_H 1

#include <stdint.h>
#include "errors.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define STACK_MAX_CAPACITY_SIZE  16*1024*1024   /* max stack capacity: 16mb */

#define stack(size)              stack_new(size)

struct stack {
    size_t  size;  /* stack size */
    size_t  cap;   /* stack capacity */
    void ** data;  /* stack data */
};

struct stack *stack_new(size_t size);
void stack_free(struct stack *stack);
void stack_clear(struct stack *stack);
void *stack_pop(struct stack *stack);
void *stack_top(struct stack *stack);
error_t stack_push(struct stack *stack, void *item);
error_t stack_grow(struct stack *stack, size_t size);

#if defined(__cplusplus)
}
#endif

#endif
