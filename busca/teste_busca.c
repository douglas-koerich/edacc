#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "registro.h"
#include "ordenacao.h"
#include "busca.h"

void imprime_chaves(R [*], size_t);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero invalido de parametros");
        printf("Uso: %s <tamanho-inicial>\n", argv[0]);
        return EXIT_FAILURE;
    }
    srand(time(NULL));

    size_t n = atoi(argv[1]);
    R* vetor = malloc(sizeof(R) * n);
    int i;
    for (i=0; i<n; ++i) {
        vetor[i].chave = rand() % 1000 + 1;
    }
    printf("Antes da ordenacao: ");
    imprime_chaves(vetor, n);
    ordena(vetor, n);

    printf("\nDepois da ordenacao: ");
    imprime_chaves(vetor, n);
    putchar('\n');

    printf("Digite uma chave para busca: ");
    unsigned x;
    scanf("%u", &x);

    int indice = busca(vetor, 0, n-1, x);
    if (indice == INVALIDO) {
        puts("Chave nao encontrada");
    } else {
        printf("Chave encontrada no indice %d.\n", indice);
    }

    free(vetor);
    return EXIT_SUCCESS;
}

void imprime_chaves(R v[], size_t t) {
    int i;
    for (i=0; i<t; ++i) {
        printf("%u ", v[i].chave);
    }
}
