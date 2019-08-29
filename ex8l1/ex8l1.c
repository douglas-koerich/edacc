#include <stdlib.h>
#include <stdio.h>
#include "fila.h"
#include "pilha.h"

void inverte_fila(Fila*);

int main(void) {
    char exemplo[] = { 'i', 'm', 'k', 'a', 'x' };
    int i;

    Fila* f = cria_f();

    for (i=0; i<sizeof(exemplo)/sizeof(char); ++i) {
        if (enqueue_f(f, exemplo[i])) {
            printf("Inserido o caractere %c\n", exemplo[i]);
        }
    }

#ifdef DEBUG
    printf("Fila ANTES"); imprime_f(f);
#endif

    inverte_fila(f);

#ifdef DEBUG
    printf("Fila DEPOIS"); imprime_f(f);
#endif

    destroi_f(f);

    return EXIT_SUCCESS;
}

void inverte_fila(Fila* f) {
    Pilha* apoio = cria_p();

    char c;
    while (!underflow_f(f)) {
        dequeue_f(f, &c);
        push(apoio, c);
    }
    while (!underflow_p(apoio)) {
        pop(apoio, &c);
        enqueue_f(f, c);
    }

    destroi_p(apoio);
}

