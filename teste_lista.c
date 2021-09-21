#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "lista.h"

int main(void) {
    list* conjunto = l_create();
    int n;
    char opcao;
    do {
        printf("Digite um numero ou 0 (zero) pra finalizar: ");
        scanf("%d", &n);
        if (n != 0) {
            printf("Adiciona no (I)nicio ou no (F)im do conjunto (I/F)? ");
            do {
                scanf(" %c", &opcao);
                opcao = toupper(opcao);
            } while (opcao != 'I' && opcao != 'F');
            if (opcao == 'I') {
                l_insert(conjunto, n, HEAD, 0);
                puts("Valor adicionado no inicio!");
            } else {
                l_insert(conjunto, n, TAIL, 0);
                puts("Valor adicionado no fim do conjunto!");
            }

        }
    } while (n != 0);

    puts("Conteudo do conjunto:");
    l_print(conjunto);
    putchar('\n');

    // Confere que o numero de elementos armazenados eh o esperado
    printf("Tamanho do conjunto: %zd\n", l_size(conjunto));

    // Confere que o conjunto nao estah vazio
    if (l_underflow(conjunto) == false) {
        puts("Conjunto nao estah vazio cf. esperado!");
    } else {
        puts("Algo deu errado, conjunto vazio!");
    }

    printf("Digite um numero para testar a busca: ");
    scanf("%d", &n);
    if (l_search(conjunto, n)) {
        puts("Numero foi encontrado!");
    } else {
        puts("Numero NAO foi encontrado!");
    }

    puts("Inserindo um numero (10) como terceiro noh da lista");
    l_insert(conjunto, 10, POSN, 3);
    l_print(conjunto);
    putchar('\n');

    puts("Removendo dos extremos do conjunto...");
    l_extract(conjunto, HEAD, 0);
    l_extract(conjunto, TAIL, 0);

    puts("Conteudo atualizado do conjunto:");
    l_print(conjunto);
    putchar('\n');

    puts("Removendo o segundo noh da lista");
    l_extract(conjunto, POSN, 2);
    l_print(conjunto);
    putchar('\n');

    l_destroy(conjunto);

    return EXIT_SUCCESS;
}