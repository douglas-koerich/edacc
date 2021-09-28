#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

/* Implemente um algoritmo que encontre o maior e o menor valor armazenados em
uma lista de numeros inteiros */

// Prototipo da funcao
void minmax(const int* lista, size_t tamanho, int* menor, int* maior);

int main(void) {
    srand((unsigned) time(NULL));

    const size_t TAMANHO = 20;
    int vetor[TAMANHO], i;

    for (i = 0; i < TAMANHO; ++i) {
        vetor[i] = rand() % 99 + 1;
        printf("%d ", vetor[i]);
    }
    putchar('\n');

    int m, M;
    minmax(vetor, TAMANHO, &m, &M);
    printf("O menor valor eh %d e o maior eh %d\n", m, M);

    return EXIT_SUCCESS;
}

/*
// Versao iterativa ("convencional")
void minmax(const int* lista, size_t tamanho, int* menor, int* maior) {
    if (lista == NULL) {
        *menor = INT_MIN, *maior = INT_MAX;
        return;
    }
    *menor = *maior = lista[0];
    int i;
    for (i = 1; i < tamanho; ++i) {
        if (lista[i] < *menor) {
            *menor = lista[i];
        }
        if (lista[i] > *maior) {
            *maior = lista[i];
        }
    }
}
*/

// Versao recursiva
void minmax(const int* lista, size_t tamanho, int* menor, int* maior) {
    // (...)
    minmax(/*...*/, menor, maior);
    if (lista[0] < *menor) {
        *menor = lista[0];
    }
    if (lista[0] > *maior) {
        *maior = lista[0];
    }
}