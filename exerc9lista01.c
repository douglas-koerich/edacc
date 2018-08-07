#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "fila_num.h"

void remove_menores(Fila_num*, unsigned);

int main(void) {
    srand((unsigned) time(NULL));
    Fila_num* fila = cria();
    int i;
    for (i=1; i<=15; ++i) {
        if (!overflow(fila)) {
            enqueue(fila, rand() % 50 + 1);
        }
    }
    printf("Digite um valor de corte para a fila: ");
    unsigned corte;
    scanf("%u", &corte);

    printf("Antes da remocao: ");
    imprime(fila);
    remove_menores(fila, corte);
    printf("Depois da remocao: ");
    imprime(fila);

    destroi(fila);
}

void remove_menores(Fila_num* original, unsigned valor) {
    Fila_num* auxiliar = cria();
    while (!underflow(original)) {
        unsigned num = dequeue(original);
        if (num >= valor && !overflow(auxiliar)) {
            enqueue(auxiliar, num);
        }
    }
    while (!underflow(auxiliar)) {
        enqueue(original, dequeue(auxiliar));
    }
    destroi(auxiliar);
}
