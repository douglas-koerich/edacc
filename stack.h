#ifndef STACK_H
#define STACK_H

// Definicao ABSTRATA do tipo pilha
struct Stack_;
typedef struct Stack_ Stack;
// Obs: referencias ao tipo Stack serao indiretas atraves de ponteiro

#include <stdbool.h>
#include <stdlib.h>

// Interface de operacoes do TAD pilha
Stack* create(size_t max_elements);
void destroy(Stack* stack);
bool push(Stack* stack, const char* element); // pilha de strings
char* pop(Stack* stack); // deve chamar free() para a string retornada apos o uso
const char* top(const Stack* stack); // consulta somente-leitura da string no topo da pilha
size_t size(const Stack* stack);
bool underflow(const Stack* stack);
void print(const Stack* stack);

#endif // STACK_H