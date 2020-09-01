#ifndef STACK_H
#define STACK_H

struct Stack_;
typedef struct Stack_ Stack;

#include <stdbool.h>
#include <stdlib.h>

Stack* create(size_t max_elements);
void destroy(Stack* stack);
bool push(Stack* stack, char operator); // pilha de caracteres
char pop(Stack* stack);
char top(const Stack* stack);
size_t size(const Stack* stack);
bool underflow(const Stack* stack);
void print(const Stack* stack);

#endif // STACK_H
