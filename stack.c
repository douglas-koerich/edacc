#include <stdio.h>
#include "stack.h"

// Definicao concreta (implementacao) da estrutura Stack_
struct Stack_ {
    char** vector; // (char*)* vector; <==> char* vector[]; (um vetor de ponteiros)
    size_t max_size;
    int stack_top; // indice do topo da pilha no vetor (fornece a contagem de forma indireta)
};

Stack* create(size_t max_elements) {
    Stack* new_stack = malloc(sizeof(Stack));
    new_stack->max_size = max_elements;
    new_stack->stack_top = -1; // nenhuma posicao do vetor ocupada ainda (nem a 0!)
    new_stack->vector = malloc(max_elements * sizeof(char*));
    return new_stack;
}

void destroy(Stack* stack) {
    free(stack->vector); // na ordem inversa do que foi criado
    free(stack);
}

bool push(Stack* stack, const char* element); // pilha de strings
char* pop(Stack* stack); // deve chamar free() para a string retornada apos o uso

const char* top(const Stack* stack) {
    if (underflow(stack)) {
        return NULL; // nao ha string a ser consultada
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
        puts(stack->vector[i--]);   // -- DEPOIS de i significa decrementar DEPOIS de usar o valor de i
    }
}
