#include "cstack.h"
#include <stddef.h>
#include <string.h>

#define UNUSED(VAR) (void)(VAR)
#define MAX_STACKS 10
#define MAX_STACK_SIZE 100
#define MAX_DATA_SIZE 512

typedef struct {
    unsigned char data[MAX_DATA_SIZE];
} StackElement;

typedef struct {
    StackElement elements[MAX_STACK_SIZE];
    size_t top;
    int initialized;
} StaticStack;

StaticStack stacks[MAX_STACKS];

hstack_t stack_new(void)
{
    for (int i = 0; i < MAX_STACKS; i++) {
        if (stacks[i].initialized == 0) {
            stacks[i].initialized = 1;
            stacks[i].top = 0;
            return i;
        }
    }
    return -1;
}

void stack_free(const hstack_t stack)
{
    if (stack >= 0 && stack < MAX_STACKS) {
        stacks[stack].top = 0;
        stacks[stack].initialized = 0;
    }
}

int stack_valid_handler(const hstack_t stack)
{
    return (stack >= 0 && stack < MAX_STACKS && stacks[stack].initialized == 1) ? 0 : 1;
}

unsigned int stack_size(const hstack_t stack)
{
    return (stack_valid_handler(stack) == 0) ? (unsigned int)stacks[stack].top : 0;
}

void stack_push(const hstack_t stack, const void* data_in, const unsigned int size)
{
    if (stack_valid_handler(stack) == 0 && stacks[stack].top < MAX_STACK_SIZE && size > 0 && size <= MAX_DATA_SIZE && data_in != NULL) {
        memcpy(stacks[stack].elements[stacks[stack].top].data, data_in, size);
        stacks[stack].top++;
    }
}

unsigned int stack_pop(const hstack_t stack, void* data_out, const unsigned int size)
{
    if (stack_valid_handler(stack) == 0 && stacks[stack].top > 0) {
        stacks[stack].top--;
        unsigned int copy_size = size < MAX_DATA_SIZE ? size : MAX_DATA_SIZE;
        memcpy(data_out, stacks[stack].elements[stacks[stack].top].data, copy_size);
        return copy_size;
    }
    return 0;
}