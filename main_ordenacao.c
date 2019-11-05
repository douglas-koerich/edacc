#include <stdlib.h>
#include <stdio.h>
#include "registro.h"
#include "alg_ordenacao.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        puts("Numero insuficiente de parametros");
        printf("Use: %s <tamanho-do-banco-de-dados> <semente>\n", argv[0]);
        return EXIT_FAILURE;
    }
    srand(atoi(argv[2]));

    size_t tamanho = atoi(argv[1]);
    Reg* database = malloc(sizeof(Reg) * tamanho);

    int i;
    puts("Banco de dados original:");
    for (i = 0; i < tamanho; ++i) {
        database[i].chave = rand() % 10000 + 1;
        database[i].dado = i + 'a'; // 'a' no [0], 'b' no [1]...
        printf("(%u,%c) ", database[i].chave, database[i].dado);
    }
    putchar('\n');

    /* Algoritmos simples - passam tamanho como parametro */
    // bolha(database, tamanho);
    // selecao(database, tamanho);
    // insercao(database, tamanho);
    // shellsort(database, tamanho);
    // radixsort(database, tamanho);

    /* Algoritmos eficientes - passam extremidades como parametro */
    // mergesort(database, 0, tamanho-1);
    quicksort(database, 0, tamanho-1);

    puts("Banco de dados ordenado pela chave:");
    for (i = 0; i < tamanho; ++i) {
        printf("(%u,%c) ", database[i].chave, database[i].dado);
    }
    putchar('\n');

    free(database);
    return EXIT_SUCCESS;
}

