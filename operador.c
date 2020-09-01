#include <stdio.h>
#include <limits.h>
#include "base.h"

struct Stack_ {
    char* vector;
    size_t max_size;
    int stack_top;
};

Stack* create(size_t max_elements) {
    Stack* new_stack = malloc(sizeof(Stack));
    new_stack->max_size = max_elements;
    new_stack->stack_top = -1;
    new_stack->vector = malloc(max_elements * sizeof(char));
    return new_stack;
}

void destroy(Stack* stack) {
    free(stack->vector);
    free(stack);
}

bool push(Stack* stack, char operator) {
    if (stack->stack_top == stack->max_size - 1) {
        return false;
    }
    stack->vector[++stack->stack_top] = operator;
    return true;
}

char pop(Stack* stack) {
    if (underflow(stack)) {
        return CHAR_MIN;
    }
    return stack->vector[stack->stack_top--];
}

char top(const Stack* stack) {
    if (underflow(stack)) {
        return CHAR_MIN;
    }
    return stack->vector[stack->stack_top];
}

size_t size(const Stack* stack) {
    return stack->stack_top + 1;
}

bool underflow(const Stack* stack) {
    return stack->stack_top == -1;
}

void print(const Stack* stack) {
    int i = stack->stack_top;
    while (i >= 0) {
        printf("%c\n", stack->vector[i--]);
    }
}
