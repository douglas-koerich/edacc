#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

int main(int argc, char* argv[]) {
    Lista* exemplo = cria(); // cria uma nova lista para ilustrar o funcionamento

    printf("Conteudo da lista apos a criacao:");
    imprime(exemplo);
    putchar('\n');

    int tipo;
    do {
        puts("Escolha o tipo de lista a ser criada:");
        puts("1 - Ordenada (crescente)");
        puts("2 - Livre");
        printf("?> ");
        scanf("%d", &tipo);
    } while (tipo != 1 && tipo != 2);

    // Insercoes
    while (true) {
        printf("Digite um novo numero para adicionar a lista, ou 0 para encerrar: ");
        int num;
        scanf("%d", &num);

        if (num == 0) {
            break;
        }

        if (tipo == 1) { // ordenada
            insere(exemplo, num, ORDEM);
        } else {
            int pos;
            do {
                printf("Insere no inicio (1) ou no fim (9) da lista? ");
                scanf("%d", &pos);
            } while (pos != 1 && pos != 9);

            if (pos == 1) {
                insere(exemplo, num, CABECA);
            } else {
                insere(exemplo, num, CAUDA);
            }
        }
        printf("Conteudo da lista apos a insercao:");
        imprime(exemplo);
        putchar('\n');
    }

    destroi(exemplo);
    return EXIT_SUCCESS;
}

