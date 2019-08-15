#include <stdlib.h>
#include <stdio.h>

#include "pilha.h"

void transfere(Pilha* destino, Pilha* origem);

int main(void) {
    char exemplo[] = { 'i', 'm', 'k', 'a', 'x' };
    int i;

    Pilha* S1 = cria();
    Pilha* S2 = cria();

    for (i=0; i<sizeof(exemplo)/sizeof(char); ++i) { // divisao para calcular
                                                     // num. elementos do vetor
        if (push(S1, exemplo[i])) {
            printf("Empilhado o caractere %c\n", exemplo[i]);
        }
    }

#ifdef DEBUG
    printf("S1"); imprime(S1);
    printf("S2"); imprime(S2);
#endif

    transfere(S2, S1);

#ifdef DEBUG
    printf("S1"); imprime(S1);
    printf("S2"); imprime(S2);
#endif

    destroi(S1);
    destroi(S2);

    return EXIT_SUCCESS;
}

void transfere(Pilha* S2, Pilha* S1) {
    Pilha* aux = cria();
    char c;

    while (!underflow(S1)) {
        pop(S1, &c);
        push(aux, c);
    }

    while (!underflow(aux)) {
        pop(aux, &c);
        push(S2, c);
    }

    destroi(aux);
}

