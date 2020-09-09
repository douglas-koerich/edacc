#include <stdio.h>
#include <limits.h>
#include "stack.h"

struct Stack_ {
    unsigned* vector;
    size_t max_size;
    int stack_top;
};

Stack* create_s(size_t max_elements) {
    Stack* new_stack = malloc(sizeof(Stack));
    new_stack->max_size = max_elements;
    new_stack->stack_top = -1;
    new_stack->vector = malloc(max_elements * sizeof(unsigned));
    return new_stack;
}

void destroy_s(Stack* stack) {
    free(stack->vector);
    free(stack);
}

bool push(Stack* stack, unsigned element) {
    if (stack->stack_top == stack->max_size - 1) {
        return false;
    }
    stack->vector[++stack->stack_top] = element;
    return true;
}

unsigned pop(Stack* stack) {
    if (underflow_s(stack)) {
        return UINT_MAX;
    }
    return stack->vector[stack->stack_top--];
}

unsigned top(const Stack* stack) {
    if (underflow_s(stack)) {
        return UINT_MAX;
    }
    return stack->vector[stack->stack_top];
}

size_t size_s(const Stack* stack) {
    return stack->stack_top + 1;
}

bool underflow_s(const Stack* stack) {
    return stack->stack_top == -1;
}

void print_s(const Stack* stack) {
    int i = stack->stack_top;
    while (i >= 0) {
        printf("%u\n", stack->vector[i--]);
    }
}
