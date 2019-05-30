#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "hash.h"

int main(void) {
    size_t tam;
    printf("Digite o tamanho da tabela de hashing: ");
    scanf("%zd", &tam);

    Hash* hash = cria(tam);

    // Gera um conjunto de registros "meio" aleatorios
    srand(2019); // para vermos sempre a mesma sequencia de chaves
    int i;
    for (i=0; i<3*tam; ++i) {
        R fake = { rand() % 1000 + 1, rand() };
        inserir(hash, &fake);
    }

    // Breve inspecao na tabela de hashing
    debug(hash);

    // Exemplo de busca
    unsigned x;
    printf("Digite uma chave para busca: ");
    scanf("%u", &x);

    i = busca(hash, x);
    if (i == -1) {
        puts("Chave nao encontrada");
    } else {
        printf("Chave encontrada no indice %d\n", i);

        R useless;
        assert(remover(hash, &useless, x)); // eu "agarantchio" que vai remover
    }

    // Inspeciona pra ver a chave removida
    debug(hash);

    destroi(hash);
    return EXIT_SUCCESS;
}

