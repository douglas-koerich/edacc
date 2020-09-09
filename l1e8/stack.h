#ifndef STACK_H
#define STACK_H

struct Stack_;
typedef struct Stack_ Stack;

#include <stdbool.h>
#include <stdlib.h>

Stack* create_s(size_t max_elements);
void destroy_s(Stack* stack);
bool push(Stack* stack, unsigned element); // pilha de inteiros sem sinal
unsigned pop(Stack* stack);
unsigned top(const Stack* stack);
size_t size_s(const Stack* stack);
bool underflow_s(const Stack* stack);
void print_s(const Stack* stack);

#endif // STACK_H