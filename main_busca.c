#include <stdlib.h>
#include <stdio.h>
#include "registro.h"
#include "alg_ordenacao.h"
#include "alg_busca.h"

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

    // Usa qualquer dos algoritmos para ordenar o vetor de registros
    // (a ordenacao eh condicao para a busca!)
    quicksort(database, 0, tamanho-1);

    puts("Banco de dados ordenado pela chave:");
    for (i = 0; i < tamanho; ++i) {
        printf("(%u,%c) ", database[i].chave, database[i].dado);
    }
    putchar('\n');

    unsigned chave;
    printf("Digite uma chave para ser localizada no vetor: ");
    scanf("%u", &chave);

    // int local = binaria(database, 0, tamanho-1, chave);
    int local = interpolacao(database, 0, tamanho-1, chave);
    if (local == -1) {
        puts("Chave nao foi encontrada no vetor!");
    } else {
        printf("Chave encontrada no indice %d.\n", local);
    }

    free(database);
    return EXIT_SUCCESS;
}

