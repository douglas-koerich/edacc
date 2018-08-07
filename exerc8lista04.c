#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TAMANHO 6

int maior(int [*], int, int);

int main(void) {
    srand((unsigned) time(NULL));
    int A[TAMANHO];

    printf("Vetor: ");
    int i;
    for (i=0; i<TAMANHO; ++i) {
        A[i] = rand() % 1000 + 1;
        printf("%d ", A[i]);
    }
    putchar('\n');
    printf("O maior elemento do vetor eh %d.\n", maior(A, 0, TAMANHO-1));
    return EXIT_SUCCESS;
}

int maior(int vetor[], int ind_esq, int ind_dir) {
    if (ind_esq == ind_dir) {   // se a recursividade levou-nos a um nivel de divisao onde existe um segmento unitario
        return vetor[ind_esq];  // retorna o maior que eh ao mesmo tempo o unico
    }
    else {
        int ind_meio = (ind_esq + ind_dir) / 2;
        int maior_esq = maior(vetor, ind_esq, ind_meio);
        int maior_dir = maior(vetor, ind_meio+1, ind_dir);
        return (maior_esq > maior_dir)? maior_esq : maior_dir;
    }
}
