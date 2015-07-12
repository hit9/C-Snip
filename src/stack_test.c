/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include "test.h"
#include "stack.h"

void
case_stack_clear()
{
    struct stack *stack = stack(5);
    stack_push(stack, "hello");
    stack_clear(stack);
    assert(stack->data == NULL);
    assert(stack->size == 0);
    assert(stack->cap == 0);
    stack_free(stack);
}

void
case_stack_push()
{
    struct stack *stack = stack(1);
    char *s1 = "a", *s2 = "b";
    assert(stack_push(stack, s1) == STACK_OK);
    assert(stack_push(stack, s2) == STACK_OK);
    assert(stack->size == 2);
    assert(stack->cap == 2);
    assert(stack_pop(stack) == s2);
    assert(stack->size == 1);
    assert(stack->cap == 2);
    assert(stack_pop(stack) == s1);
    stack_free(stack);
}

void
case_stack_pop()
{
    struct stack *stack = stack(3);
    char *s1 = "a", *s2 = "b";
    assert(stack_push(stack, s1) == STACK_OK);
    assert(stack_push(stack, s2) == STACK_OK);
    assert(stack->size == 2);
    assert(stack->cap == 3);
    assert(stack_pop(stack) == s2);
    assert(stack_pop(stack) == s1);
    assert(stack->size == 0);
    assert(stack->cap == 3);
    stack_free(stack);
}

void
case_stack_top()
{
    struct stack *stack = stack(3);
    char *s1 = "a", *s2 = "b", *s3 = "c";
    assert(stack_push(stack, s1) == STACK_OK);
    assert(stack_top(stack) == s1);
    assert(stack_push(stack, s2) == STACK_OK);
    assert(stack_top(stack) == s2);
    assert(stack_push(stack, s3) == STACK_OK);
    assert(stack_top(stack) == s3);
    assert(stack->size == 3);
    assert(stack->cap == 3);
    stack_free(stack);
}
