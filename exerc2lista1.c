#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tad_pilha_inteiros.h"

void transfere(PilhaInt* destino, PilhaInt* origem) {
    PilhaInt* auxiliar = cria_pilha();
    while (!underflow(origem)) {
        push(auxiliar, pop(origem));
    }
    while (!underflow(auxiliar)) {
        push(destino, pop(auxiliar));
    }
    destroi_pilha(auxiliar);
}

int main() {
    srand((unsigned) time(NULL));

    PilhaInt* S1 = cria_pilha();
    PilhaInt* S2 = cria_pilha();

    // Preenchendo a pilha S1 com numeros aleatorios
    int num;
    do {
        num = rand() % 100;
        push(S1, num);
    } while (num < 90);

    puts("Pilha S1:");
    imprime_pilha(S1);
    puts("Pilha S2:");
    imprime_pilha(S2);

    transfere(S2, S1);

    puts("Pilha S1:");
    imprime_pilha(S1);
    puts("Pilha S2:");
    imprime_pilha(S2);

    destroi_pilha(S1);
    destroi_pilha(S2);

    return EXIT_SUCCESS;
}
