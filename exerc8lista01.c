#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tad_fila_inteiros.h"

int main(void) {
    srand(time(NULL));

    FilaInt* fila = cria_fila();
    int num;
    while (!foverflow(fila)) {   // enquanto nao enche a fila...
        num = rand() % 30;
        if (num > 25) {
            break;  // ... ou nao encontra um numero > 25...
        }
        enqueue(fila, num); // ... vai salvando na fila.
    }
    puts("Fila gerada:");
    imprime_fila(fila);
    putchar('\n');

    inverte(fila);

    puts("Fila invertida:");
    imprime_fila(fila);
    putchar('\n');

    destroi_fila(fila);

    return EXIT_SUCCESS;
}
