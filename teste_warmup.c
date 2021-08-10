#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "warmup.h"

int main(void) {
    size_t tamanho;
    printf("Qual a capacidade maxima do vetor a ser criado? ");
    scanf("%zu", &tamanho);

    int* vetor = cria(tamanho); // recebe a referencia para o vetor recem-criado
    int i, n;
    char opcao;
    for (i = 1; i <= tamanho/2; ++i) {
        printf("Digite um numero: ");
        scanf("%d", &n);

        printf("Adiciona no (I)nicio ou no (F)im do vetor (I/F)?" );
        do {
            scanf(" %c", &opcao);
            opcao = toupper(opcao);
        } while (opcao != 'I' && opcao != 'F');
        if (opcao == 'I') {
            insere(vetor, n, INICIO);
            puts("Valor adicionado no inicio!");
        } else {
            insere(vetor, n, FIM);
            puts("Valor adicionado no fim do vetor!");
        }
    }
    puts("Conteudo do vetor:");
    imprime(vetor);

    // Confere que o numero de elementos armazenados eh o esperado
    if (comprimento(vetor) == tamanho/2) {
        puts("Comprimento do vetor cf. esperado!");
    } else {
        puts("Vetor foi corrompido!");
    }

    // Confere que o vetor nao estah vazio
    if (vazio(vetor) == false) {
        puts("Vetor nao estah vazio cf. esperado!");
    } else {
        puts("Algo deu errado, vetor vazio!");
    }

    printf("Digite um numero para testar a busca: ");
    scanf("%d", &n);
    i = busca(vetor, n);
    if (i == -1) {
        puts("Numero nao foi encontrado!");
    } else {
        printf("Valor encontrado no indice %d\n", i);
    }

    printf("Deseja remover o valor do vetor (S/N)? ");
    do {
        scanf(" %c", &opcao);
        opcao = tolower(opcao);
    } while (opcao != 's' && opcao != 'n');
    if (opcao == 's') {
        retira(vetor, VALOR, n);
    }

    puts("Conteudo atualizado do vetor:");
    imprime(vetor);

    destroi(vetor); // libera a memoria que esse vetor ocupou durante o programa

    return EXIT_SUCCESS;
}