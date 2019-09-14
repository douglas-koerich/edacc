#include <stdlib.h>
#include <stdio.h>

#include "lista.h"

int main(void) {
    char exemplo[] = { 'i', 'm', 'k', 'a', 'x' };
    int i;

    Lista* L = criar();

    for (i=1; i<sizeof(exemplo)/sizeof(char); ++i) { // divisao para calcular
                                                     // num. elementos do vetor
        inserir(L, exemplo[i], CABECA, 0);
        printf("Adicionado o caractere %c na lista\n", exemplo[i]);
    }
    inserir(L, exemplo[0], CAUDA, 0);

#ifdef DEBUG
    printf("Conteudo da lista: ");
    imprimir(L);
#endif
/*
    inverter(L); // teste do exercicio 8

#ifdef DEBUG
    printf("Depois da inversao: ");
    imprimir(L);
#endif
*/
    char ch;
    remover(L, &ch, CABECA, 0);
    printf("Removido o caractere %c da lista\n", ch);
    remover(L, &ch, CAUDA, 0);
    printf("Removido tambem o caractere %c da lista\n", ch);

#ifdef DEBUG
    printf("Conteudo atualizado da lista: ");
    imprimir(L);
#endif

    printf("Digite um caractere para ser pesquisado: ");
    scanf(" %c", &ch);
    if (buscar(L, ch)) {
        puts("Encontrado!");
    } else {
        puts("NAO encontrado!");
    }

    destruir(L);

    L = criar(); // cria outra lista, pra ser preenchida agora em ordem crescente
    for (i=0; i<sizeof(exemplo)/sizeof(char); ++i) {
        inserir(L, exemplo[i], CRESCENTE, 0);
        printf("Adicionado o caractere %c na lista\n", exemplo[i]);
    }
#ifdef DEBUG
    printf("Conteudo da lista: ");
    imprimir(L);
#endif
    puts("Inserindo 'b' na terceira posicao da lista...");
    inserir(L, 'b', FIXA, 3);
#ifdef DEBUG
    printf("Conteudo da lista: ");
    imprimir(L);
#endif
    puts("Inserindo 'c' na centesima(?) posicao da lista...");
    inserir(L, 'c', FIXA, 100);
#ifdef DEBUG
    printf("Conteudo da lista: ");
    imprimir(L);
#endif

    printf("Digite um caractere para ser removido: ");
    scanf(" %c", &ch);
    remover_v(L, ch);
#ifdef DEBUG
    printf("Conteudo da lista: ");
    imprimir(L);
#endif
    puts("Removendo o terceiro elemento da lista...");
    remover(L, &ch, FIXA, 3);
#ifdef DEBUG
    printf("Conteudo da lista: ");
    imprimir(L);
#endif
    printf("Removido o caractere %c\n", ch);

    destruir(L);

    L = criar(); // cria outra lista, pra ser preenchida agora em decrescente
    for (i=0; i<sizeof(exemplo)/sizeof(char); ++i) {
        inserir(L, exemplo[i], DECRESCENTE, 0);
        printf("Adicionado o caractere %c na lista\n", exemplo[i]);
    }
#ifdef DEBUG
    printf("Conteudo da lista: ");
    imprimir(L);
#endif
    destruir(L);

    return EXIT_SUCCESS;
}

