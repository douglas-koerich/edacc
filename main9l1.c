#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "ex9l1.h"

#define MAX_FILA   20

void retira(IFila* f, int limite_inferior);

int main() {
    srand((unsigned) time(0));

    IFila* f = cria(MAX_FILA);

    int i;
    for (i=0; i<MAX_FILA/2; ++i) {
        if (!overflow(f)) {
            enqueue(f, rand() % 100);
        }
    }
    printf("Fila antes da remocao: ");
    print(f);
    
    int limite;
    printf("\nDigite o valor abaixo do qual a fila deve ser limpa: ");
    scanf("%d", &limite);

    retira(f, limite);

    printf("Fila apos a remocao: ");
    print(f);
    putchar('\n');

    destroi(f);

    return EXIT_SUCCESS;
}

void retira(IFila* f, int limite_inferior) {
    IFila* aux = cria(MAX_FILA);

    // Cria uma copia na fila auxiliar
    while (!underflow(f)) {
        enqueue(aux, dequeue(f));
    }

    // Ao devolver para fila original, nao inclui os menores que o
    // limite
    while (!underflow(aux)) {
        int i = dequeue(aux);
        if (i >= limite_inferior) {
            enqueue(f, i);
        }
    }

    destroi(aux);
}

