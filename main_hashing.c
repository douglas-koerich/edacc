#include <stdlib.h>
#include <stdio.h>
#include "registro.h"
#include "hashing.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        puts("Numero insuficiente de parametros");
        printf("Use: %s <tamanho-do-banco-de-dados> <semente>\n", argv[0]);
        return EXIT_FAILURE;
    }
    srand(atoi(argv[2]));

    size_t tamanho = atoi(argv[1]);
    Hash* database = criar(tamanho);

    int i;
    for (i = 0; i < tamanho / 2; ++i) { // ocupa metade da tabela
        Reg rasc = {
            .chave = rand() % 10000 + 1,
            .dado = i + 'a'
        };
        inserir(database, &rasc);
    }
    puts("Tabela de hashing jah ocupada:");
    imprimir(database);

    /*
    unsigned chave;
    printf("Digite uma chave para ser localizada no vetor: ");
    scanf("%u", &chave);

    Reg* r = buscar(database, chave);
    if (r == NULL) {
        puts("Chave nao foi encontrada!");
    } else {
        puts("Chave encontrada!");
    }
    */

    destruir(database);
    return EXIT_SUCCESS;
}

