#include <stdio.h>
#include <string.h>
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
    // Precisa liberar a copia das strings alocadas dinamicamente que ainda estiverem
    // na pilha
    int i;
    for (i = 0; i <= stack->stack_top; ++i) {
        free(stack->vector[i]); // libera a memoria alocada por strdup()
    }
    free(stack->vector); // na ordem inversa do que foi criado
    free(stack);
}

bool push(Stack* stack, const char* element) {
    if (stack->stack_top == stack->max_size - 1) { // vetor estah cheio?
        return false;
    }
    char* copy = strdup(element); // duplicata alocada dinamicamente
    /*
    ++stack->stack_top; // avanca para a proxima posicao livre no vetor (novo topo)
    stack->vector[stack->stack_top] = copy;
    */
    stack->vector[++stack->stack_top] = copy; // incrementa o indice antes de usar na expressao
    return true;
}

char* pop(Stack* stack) {
    if (underflow(stack)) { // se a pilha esta vazia...
        return NULL; // ...nao existe elemento (string) a ser removido
    }
    /*
    char* element = stack->vector[stack->stack_top];
    --stack->stack_top;
    return element;
    */
   return stack->vector[stack->stack_top--]; // decrementa o indice depois de recuperar o conteudo
}

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
