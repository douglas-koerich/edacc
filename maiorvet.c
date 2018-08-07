/* Escreva uma funcao que retorne o maior valor dentro
 * de um vetor de numeros inteiros.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NUM_VALORES 10

int maior(int* vetor, int tam);

int main(void) {
    srand(time(NULL));
    int vetor[NUM_VALORES];

    int i;
    for (i=0; i<NUM_VALORES; ++i) {
        vetor[i] = rand() % 100;
        printf("%d ", vetor[i]);
    }
    putchar('\n');

    printf("O maior valor gerado foi %d.\n", maior(vetor, NUM_VALORES));

    return EXIT_SUCCESS;
}

#ifndef RECURSIVO
int maior(int* vetor, int tam) {
    int m = *vetor, i;
    for (i=0; i<tam; ++i, ++vetor) {
        if (*vetor > m) {
            m = *vetor;
        }
    }
    return m;
}
#else
int maior(int* vetor, int posicao) {
    int m = *(vetor + posicao - 1);
    if (posicao == 1) {
        return m;
    }
    int outro = maior(vetor, posicao-1);
    if (m > outro) {
        return m;
    } else {
        return outro;
    }
}
#endif

