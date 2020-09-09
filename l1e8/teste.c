#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "queue.h"
#include "stack.h"

#define MAX 8

void inverte(Queue*);

int main(void) {
    // Cria uma fila para teste
    Queue* fila = create_q(MAX);

    // Gera uma sequencia aleatoria de numeros inteiros e insere-os na fila
    srand((unsigned) time(NULL));
    int i;
    for (i = 0; i < MAX; ++i) {
        enqueue(fila, rand() % 60 + 1); // sua proxima aposta na Mega Sena
    }

    // Condicao (ordem) atual da fila
    puts("Fila antes da operacao: ");
    print_q(fila);
    putchar('\n');

    // Inverte o conteudo da fila
    inverte(fila);

    // Condicao (ordem) modificada da fila
    puts("Fila depois da operacao: ");
    print_q(fila);
    putchar('\n');

    // Retira a fila da memoria do programa
    destroy_q(fila);

    return EXIT_SUCCESS;
}

void inverte(Queue* fila) {
    Stack* apoio = create_s(MAX);

    while (!underflow_q(fila)) {
        push(apoio, dequeue(fila)); // tira da fila e poe na pilha
    }

    // Verificacao: conteudo da pilha
    puts("Conteudo da pilha de apoio:");
    print_s(apoio);

    while (!underflow_s(apoio)) {
        enqueue(fila, pop(apoio)); // tira da pilha e poe na fila
    }

    destroy_s(apoio);
}