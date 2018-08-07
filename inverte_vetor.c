#include <stdlib.h>
#include <stdio.h>

// Inverter um vetor sem o uso de uma pilha:

void inverte_vetor_i(int [*], size_t);
void inverte_vetor_r(int [*], int, int);

#define NUM_ELEMENTOS   14

int main(void) {
    int vetor[NUM_ELEMENTOS] = {
        1, 2, 3, 5, 7, 11, 13,
        17, 19, 23, 29, 31, 37, 43
    };
    printf("Antes da inversao: ");
    int i;
    for (i = 0; i < NUM_ELEMENTOS; ++i) {
        printf("%d ", vetor[i]);
    }
    putchar('\n');

    inverte_vetor_i(vetor, NUM_ELEMENTOS);

    printf("Depois da inversao: ");
    for (i = 0; i < NUM_ELEMENTOS; ++i) {
        printf("%d ", vetor[i]);
    }
    putchar('\n');

    inverte_vetor_r(vetor, 0, NUM_ELEMENTOS-1);

    printf("Depois da re-inversao: ");
    for (i = 0; i < NUM_ELEMENTOS; ++i) {
        printf("%d ", vetor[i]);
    }
    putchar('\n');

    return EXIT_SUCCESS;
}

void inverte_vetor_i(int v[], size_t t) {
    int inicio = 0, fim = t-1;
    while (inicio < fim) {
        int aux = v[inicio];
        v[inicio] = v[fim];
        v[fim] = aux;
        ++inicio, --fim;
    }
}

void inverte_vetor_r(int v[], int esq, int dir) {
    if (dir < esq) {
        return;
    }
    int aux = v[esq];
    v[esq] = v[dir];
    v[dir] = aux;
    inverte_vetor_r(v, ++esq, --dir);
}

