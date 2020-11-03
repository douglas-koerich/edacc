#include <stdlib.h>
#include <stdio.h>
#include "record.h"
#include "sort.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de parametros");
        printf("Uso: %s <tamanho-vetor>\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t n = atoi(argv[1]);
    Record* vetor = malloc(n * sizeof(Record));

    const unsigned SEMENTE = 20201027;
    srand(SEMENTE);
    
    int i;

    // Gera um conjunto de n registros com chaves aleatorias (e campos tambem)
    puts("Vetor gerado:");
    for (i = 0; i < n; ++i) {
        vetor[i].key = rand() % 500;
        printf("%d ", vetor[i].key);

        vetor[i].value = rand() % 26 + 'A';
    }
    putchar('\n');

    // Ordenacao por um dos metodos/algoritmos
    // bubble(vetor, n);
    // selection(vetor, n);
    // insertion(vetor, n);
    // shell(vetor, n);
    // radix(vetor, n);
    // merge(vetor, 0, n - 1);
    quick(vetor, 0, n - 1);

    // Impressao do conjunto apos ordenacao
    puts("\nVetor ordenado:");
    for (i = 0; i < n; ++i) {
        printf("%d ", vetor[i].key);
    }
    putchar('\n');

    free(vetor);

    return EXIT_SUCCESS;
}