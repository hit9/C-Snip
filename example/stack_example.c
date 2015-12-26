// cc stack_example.c stack.c

#include <assert.h>
#include <stdio.h>
#include "stack.h"

int main(int argc, const char *argv[])
{
    /* allocate a new empty stack with memory capacity 1 */
    struct stack *stack = stack(1);
    /* push data to stack */
    char *val1 = "val1";
    char *val2 = "val2";
    char *val3 = "val3";
    assert(stack_push(stack, val1) == STACK_OK);
    assert(stack_push(stack, val2) == STACK_OK);
    assert(stack_push(stack, val3) == STACK_OK);
    /* current stack capacity (or allocated memory) */
    printf("current stack allocated memory: %zu\n", stack_cap(stack));
    /* get stack len */
    printf("current stack length: %zu\n", stack_len(stack));
    /* pop data from stack, the order is invse with push */
    void *data;
    while ((data = stack_pop(stack)) != NULL)
        printf("pop data: %s\n", (char *)data);
    /* free stack */
    stack_free(stack);
    return 0;
}
