#include <stdlib.h>
#include <stdio.h>
#include "registro.h"
#include "hash.h"

#define TAM_HASH 7
#define NUM_REGISTROS 16

int main(void) {
    Reg teste[NUM_REGISTROS] = {
        { "tuiuti", 10, 100 },
        { "positivo", 5, 50 },
        { "catolica", 30, 8 },
        { "federal", 20, 10 },
        { "utfpr", 15, 12 },
        { "unicuritiba", 18, 23 },
        { "unibrasil", 8, 14 },
        { "usp", 1, 1 },
        { "uel", 2, 2 },
        { "uem", 3, 3 },
        { "unioeste", 4, 4 },
        { "ufrj", 5, 5 },
        { "ufsc", 6, 6 },
        { "mit", 100, 100 },
        { "columbia", 200, 200 },
        { "harvard", 300, 300 }
    };

    HashReg* hash = cria(TAM_HASH);

    puts(">>> Hash vazio <<<");
    imprime(hash);

    int r;
    for (r=0; r<NUM_REGISTROS; ++r) {
        insere(hash, teste+r);
    }

    puts(">>> Hash preenchido com todas os registros <<<");
    imprime(hash);

    char chave[MAX_TAM_CHAVE];
    printf("Digite uma chave para buscar na tabela hash: ");
    scanf(" %s", chave);
    const Reg* reg = busca(hash, chave);
    if (reg == NULL) {
        puts("Chave NAO encontrada!");
    } else {
        printf("Dados do registro: matricula = %d, codigo = %d.\n", reg->matricula, reg->codigo);
    }

    printf("Digite uma chave para remover da tabela hash: ");
    scanf(" %s", chave);
    exclui(hash, chave);

    puts(">>> Hash apos a exclusao da chave digitada <<<");
    imprime(hash);

    destroi(hash);

    return EXIT_SUCCESS;
}

