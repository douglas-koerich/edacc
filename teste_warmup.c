#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "warmup.h"

int main(void) {
    size_t tamanho;
    printf("Qual a capacidade maxima do conjunto a ser criado? ");
    scanf("%zu", &tamanho);

    lista* conjunto = cria(tamanho);
    int i, n;
    char opcao;
    for (i = 1; i <= tamanho/2; ++i) {
        printf("Digite um numero: ");
        scanf("%d", &n);

        printf("Adiciona no (I)nicio ou no (F)im do conjunto (I/F)? ");
        do {
            scanf(" %c", &opcao);
            opcao = toupper(opcao);
        } while (opcao != 'I' && opcao != 'F');
        if (opcao == 'I') {
            insere(conjunto, n, INICIO);
            puts("Valor adicionado no inicio!");
        } else {
            insere(conjunto, n, FIM);
            puts("Valor adicionado no fim do conjunto!");
        }
    }
    puts("Conteudo do conjunto:");
    imprime(conjunto);
    putchar('\n');

    // Confere que o numero de elementos armazenados eh o esperado
    if (comprimento(conjunto) == tamanho/2) {
        puts("Comprimento do conjunto cf. esperado!");
    } else {
        puts("Conjunto foi corrompido!");
    }

    // Confere que o conjunto nao estah vazio
    if (vazio(conjunto) == false) {
        puts("Conjunto nao estah vazio cf. esperado!");
    } else {
        puts("Algo deu errado, conjunto vazio!");
    }

    printf("Digite um numero para testar a busca: ");
    scanf("%d", &n);
    i = busca(conjunto, n);
    if (i == -1) {
        puts("Numero nao foi encontrado!");
    } else {
        printf("Valor encontrado na posicao %d\n", i);
    }

    printf("Deseja remover o valor do conjunto (S/N)? ");
    do {
        scanf(" %c", &opcao);
        opcao = tolower(opcao);
    } while (opcao != 's' && opcao != 'n');
    if (opcao == 's') {
        retira(conjunto, VALOR, n);
    }

    puts("Conteudo atualizado do conjunto:");
    imprime(conjunto);
    putchar('\n');

    destroi(conjunto); // libera a memoria que esse conjunto ocupou durante o programa

    return EXIT_SUCCESS;
}