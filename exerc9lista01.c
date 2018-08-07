#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tad_fila_inteiros.h"

void remove_menores(FilaInt* f, int n) {
    FilaInt* aux = cria_fila();
    while (!underflow(f)) {
        int i = dequeue(f);
        if (i >= n) {
            enqueue(aux, i);
        }
    }
    while (!underflow(aux)) {
        enqueue(f, dequeue(aux));
    }
    destroi_fila(aux);
}

int main(void) {
    srand(time(NULL));

    FilaInt* fila = cria_fila();
    int num;
    while (!overflow(fila)) {   // enquanto nao enche a fila...
        num = rand() % 30;
        if (num > 25) {
            break;  // ... ou nao encontra um numero > 25...
        }
        enqueue(fila, num); // ... vai salvando na fila.
    }
    puts("Fila gerada:");
    imprime_fila(fila);
    putchar('\n');

    printf("Digite um numero de referencia: ");
    scanf("%d", &num);
    remove_menores(fila, num);

    puts("Fila atualizada:");
    imprime_fila(fila);
    putchar('\n');

    destroi_fila(fila);

    return EXIT_SUCCESS;
}
