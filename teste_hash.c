#include <stdlib.h>
#include <stdio.h>
#include "item.h"
#include "hash.h"

int main(void) {
    const size_t TAMANHO = 20;
    hash* tabela = create(TAMANHO);

    int i;
    srand(20211125);
    for (i = 1; i <= TAMANHO / 2; ++i) {
        item novo = { .chave = rand() % 1000 + 1, .valor = 'a' + (i-1) };
        insert(tabela, &novo);
    }
    print(tabela);
    putchar('\n');

    int x;
    printf("Digite um valor de chave para busca: ");
    scanf("%d", &x);

    item* j = search(tabela, x);
    if (j != NULL) {
        printf("Encontrado o registro com valor '%c'\n", j->valor);
        item removido;
        extract(tabela, &removido, x);

        print(tabela);
        putchar('\n');
    } else {
        puts("Chave nao encontrada na tabela!");
    }

    destroy(tabela);
    return EXIT_SUCCESS;
} 