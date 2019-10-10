#include <stdlib.h>
#include <stdio.h>
#include <time.h>

unsigned conta_ocorrencias(int*, int, int, int);

#define TAM_VETOR 20

int main(void) {
    srand((unsigned) time(NULL));
    int i, vetor[TAM_VETOR];

    puts("Vetor gerado randomicamente:");
    for (i = 0; i < TAM_VETOR; ++i) {
        vetor[i] = rand() % 20 + 1;
        printf("%d ", vetor[i]);
    }

    int valor;
    printf("\nDigite um valor para buscar: ");
    scanf("%d", &valor);

    unsigned num_ocorrencias = conta_ocorrencias(vetor, 0, TAM_VETOR-1, valor);

    printf("O numero de ocorrencias de %d no vetor eh %u.\n", valor,
           num_ocorrencias);
    return EXIT_SUCCESS;
}

unsigned conta_ocorrencias(int* vet, int inf, int sup, int val) {
    if (inf == sup) { // recebeu um segmento de vetor de tamanho unitario
        return vet[inf] == val; // retorna 1 se for igual (e assim conta-o)
    }
    int med = (inf + sup) / 2;
    unsigned cont_inf = conta_ocorrencias(vet, inf, med, val);
    unsigned cont_sup = conta_ocorrencias(vet, med+1, sup, val);
    return cont_inf + cont_sup;
}


