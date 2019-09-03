#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

int main(void) {
    char exemplo[] = { 'i', 'm', 'k', 'a', 'x' };
    int i;

    Fila* f = cria();

    for (i=0; i<sizeof(exemplo)/sizeof(char); ++i) {
        if (enqueue(f, exemplo[i])) {
            printf("Inserido o caractere %c\n", exemplo[i]);
        }
        printf("Tamanho da fila: %zd\n", size(f));
#ifdef DEBUG
        printf("Fila ATUAL"); imprime(f);
#endif
    }

    while (!underflow(f)) {
        char c;
        dequeue(f, &c);
        printf("Tamanho da fila: %zd\n", size(f));
    }

    destroi(f);

    return EXIT_SUCCESS;
}
