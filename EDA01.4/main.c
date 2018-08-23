#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

// Solucao do exercicio 4
void exclui(Pilha*, int);

int main(void) {
    Pilha* pilha = cria();
    
    int teste[] = { 0, 1, 1, 2, 3, 5, 8, 1, 13, 21, 1, 34, 55, 1, -1 };
    int i = 0;
    while (teste[i] >= 0 && !overflow(pilha)) {
        push(pilha, teste[i++]);
    }
    printf("Pilha original: ");
    imprime(pilha);
    putchar('\n');

    exclui(pilha, 1);

    printf("Pilha sem o elemento 1: ");
    imprime(pilha);
    putchar('\n');

    destroi(pilha);
    return EXIT_SUCCESS;
}

void exclui(Pilha* pilha, int valor) {
    Pilha* auxiliar = cria();
    while (!underflow(pilha)) {
        int i = pop(pilha);
        if (i != valor && !overflow(auxiliar)) {
            push(auxiliar, i);
        }
    }
    while (!underflow(auxiliar)) {
        push(pilha, pop(auxiliar));
    }
    destroi(auxiliar);
}

