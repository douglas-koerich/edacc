#include <stdlib.h>
#include <stdio.h>
#include <time.h>

size_t num_ocorrencias(const int*, size_t, int);

#define TAM 15

int main(void) {
    int vetor[TAM];
    srand((unsigned) time(NULL));
    
    int i;
    for (i=0; i<TAM; ++i) {
        vetor[i] = rand() % 20;
        printf("%d ", vetor[i]);
    }

    printf("\nDigite um numero para buscar no conjunto acima: ");
    int num;
    scanf("%d", &num);

    size_t qtde = num_ocorrencias(vetor, TAM, num);

    printf("O numero %d ocorre %zd vezes no vetor.\n", num, qtde);

    return EXIT_SUCCESS;
}

size_t num_ocorrencias(const int* v, size_t t, int x) {
    /* Versao 1, parecida com a busca pelo maior feita no exercicio
     * anterior...
    if (t == 1) {
        return *v == x; // retorna true (1) ou false (0)
    }
    size_t q, m = t / 2;
    q = num_ocorrencias(v, m, x);
    q += num_ocorrencias(v+m, t-m, x);
    return q;
    */

    // Versao 2
    if (t == 0) {
        return 0;
    }
    int q = *v == x? 1: 0;
    q += num_ocorrencias(v+1, t-1, x);
    return q;
}

