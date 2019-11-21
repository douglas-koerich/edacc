#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "registro.h"
#include "hashing.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        puts("Numero insuficiente de parametros");
        printf("Use: %s <tamanho-do-banco-de-dados> <semente>\n", argv[0]);
        return EXIT_FAILURE;
    }
    srand(atoi(argv[2]));

    size_t tamanho_tabela = atoi(argv[1]);
    Hash* database = h_criar(tamanho_tabela);

    int i;
    for (i = 0; i < tamanho_tabela * 2; ++i) { // ocupa dobro da tabela
        Reg rasc = {
            .chave = rand() % 10000 + 1,
            .dado = i + 'a'
        };
        h_inserir(database, &rasc);
    }
    printf("Tabela de hashing jah ocupada com %zu elementos:\n",
           h_tamanho(database));
    h_imprimir(database);

    unsigned chave;
    printf("Digite uma chave para ser localizada no vetor: ");
    scanf("%u", &chave);

    Reg* r = h_buscar(database, chave);
    if (r == NULL) {
        puts("Chave nao foi encontrada!");
    } else {
        puts("Chave encontrada!");

        char resposta;
        do {
            printf("Deseja remover esse registro (S/N)? ");
            scanf(" %c", &resposta);
            resposta = toupper(resposta);
        } while (resposta != 'S' && resposta != 'N');

        if (resposta == 'S') {
            h_remover(database, chave);
            puts("Tabela de hashing apos a remocao:");
            h_imprimir(database);
        }
    }

    h_destruir(database);
    return EXIT_SUCCESS;
}

