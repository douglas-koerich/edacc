#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "ex2l1.h"

#define MAX_PILHA   10

void copy(IPilha* q, IPilha* p);

int main() {
    srand((unsigned) time(0));

    IPilha* p1 = cria(MAX_PILHA);
    IPilha* p2 = cria(MAX_PILHA);

    int i;
    for (i=0; i<MAX_PILHA/2; ++i) {
        if (!overflow(p1)) {
            push(p1, rand() % 100);
        }
    }

    copy(p2, p1);

    destroi(p1);
    destroi(p2);

    return EXIT_SUCCESS;
}

void copy(IPilha* q, IPilha* p) {
    IPilha* aux = cria(MAX_PILHA);

    printf("Pilha 1: ");
    print(p);
    printf("\nPilha 2: ");
    print(q);

    while (!underflow(p)) {
        push(aux, pop(p));
    }

    printf("\n\nAuxiliar: ");
    print(aux);
    printf("\nPilha 1: ");
    print(p);
    printf("\nPilha 2: ");
    print(q);

    while (!underflow(aux)) {
        int i = pop(aux);
        push(q, i);
        push(p, i);  // restaura a pilha original
    }

    printf("\n\nAuxiliar: ");
    print(aux);
    printf("\nPilha 1: ");
    print(p);
    printf("\nPilha 2: ");
    print(q);
    putchar('\n');

    destroi(aux);
}

