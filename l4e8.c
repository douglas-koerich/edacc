#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TAMANHO 15

int maior_valor(int [*], int, int);

int main(void) {
    srand((unsigned) time(NULL));
    
    int A[TAMANHO], i;
    for (i = 0; i < TAMANHO; ++i) {
        A[i] = rand() % 1000;
        printf("%d ", A[i]);
    }
    putchar('\n');

    int maior = maior_valor(A, 0, TAMANHO-1); // passa os indices de inicio e fim do vetor

    printf("O maior valor do vetor eh %d\n", maior);
    
    return EXIT_SUCCESS;
}

// Cada chamada recursiva recebe como indices 'inicio' e 'fim' os indices das extremidades
// do segmento de vetor daquele momento (naquele nivel de chamada recursiva)
int maior_valor(int vetor[], int inicio, int fim) {
    if (inicio == fim) { // segmento de tamanho unitario?
        // Condicao terminal, o "maior" valor eh o unico
        return vetor[inicio]; // ou vetor[fim];
    }
    int meio = (inicio + fim) / 2;
    int maior_metade_inicial = maior_valor(vetor, inicio, meio);
    int maior_metade_final = maior_valor(vetor, meio+1, fim);
    if (maior_metade_inicial > maior_metade_final) {
        return maior_metade_inicial;
    } else {
        return maior_metade_final;
    }
}