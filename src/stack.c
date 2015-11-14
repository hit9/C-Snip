/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include <stdlib.h>

#include "stack.h"

/* Create new stack with an initialized capacity. */
struct stack *
stack_new(size_t cap)
{
    struct stack *stack = malloc(sizeof(struct stack));

    if (stack != NULL) {
        stack->data = NULL;
        stack->len = 0;
        stack->cap = 0;

        if (cap > 0 && stack_grow(stack, cap) != STACK_OK)
            return NULL;
    }

    return stack;
}

/* Free stack and its data. */
void
stack_free(struct stack *stack)
{
    if (stack != NULL) {
        if (stack->data != NULL)
            free(stack->data);
        free(stack);
    }
}

/* Clear stack data to NULL and clean its len and cap to zero. */
void
stack_clear(struct stack *stack)
{
    assert(stack != NULL);

    if (stack->data != NULL) {
        free(stack->data);
        stack->data = NULL;
    }

    stack->cap = 0;
    stack->len = 0;
}

/* Get stack length */
size_t
stack_len(struct stack *stack)
{
    assert(stack != NULL);
    return stack->len;
}

/* Get stack capacity */
size_t
stack_cap(struct stack *stack)
{
    assert(stack != NULL);
    return stack->cap;
}

/* Grow a stack's memory capacity to given cap. */
int
stack_grow(struct stack *stack, size_t cap)
{
    assert(stack != NULL);

    if (cap > STACK_CAP_MAX)
        return STACK_ENOMEM;

    if (cap <= stack->cap)
        return STACK_OK;

    size_t unit = stack->cap;

    if (unit > STACK_UNIT_MAX)
        unit = STACK_UNIT_MAX;

    if (unit < STACK_UNIT_MIN)
        unit = STACK_UNIT_MIN;

    size_t new_cap = stack->cap + unit;
    while (new_cap < cap)
        new_cap += unit;

    void **data = realloc(stack->data, new_cap * sizeof(void *));
    if (data == NULL)
        return STACK_ENOMEM;

    stack->data = data;
    stack->cap = new_cap;

    if (stack->len > new_cap)
        stack->len = new_cap;
    return STACK_OK;
}

/* Push an item on the top of the stack. */
int
stack_push(struct stack *stack, void *data)
{
    assert(stack != NULL);

    if (stack->len <= stack->cap &&
            stack_grow(stack, stack->len + 1) != STACK_OK)
        return STACK_ENOMEM;

    stack->data[stack->len++] = data;
    return STACK_OK;
}

/* Pop an item from the top of the stack, NULL on empty. */
void *
stack_pop(struct stack *stack)
{
    assert(stack != NULL);

    if (stack->len == 0 || stack->data == NULL)
        return NULL;

    return stack->data[--stack->len];
}

/* Get an item from the top of the stack, NULL on empty. */
void *
stack_top(struct stack *stack)
{
    assert(stack != NULL);

    if (stack->len == 0 || stack->data == NULL)
        return NULL;

    return stack->data[stack->len - 1];
}
