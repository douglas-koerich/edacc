#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "lista.h"

int main(void) {
    int vetor1[] = { 1, 2, 3, 4, 5, 2, 3, 6, -1 };
    int vetor2[] = { 4, 5, 6, 7, 8, 9, 7, 4, -1 };
    int vetor3[] = { 1, 2, 3, 4, 5, 6, -1 };

    ListaInt* l1 = cria();
    ListaInt* l2 = cria();
    ListaInt* l3 = cria();

    // Insere os itens de cada vetor na lista correspondente; a operacao
    // de insercao vai evitar a duplicata de valores vinda no vetor, se houver
    int i = 0;
    while (vetor1[i] >= 0) {
        insere_exclusivo(l1, vetor1[i++]);
    }
    printf("l1: "); imprime(l1); putchar('\n');
    i = 0;
    while (vetor2[i] >= 0) {
        insere_exclusivo(l2, vetor2[i++]);
    }
    printf("l2: "); imprime(l2); putchar('\n');
    i = 0;
    while (vetor3[i] >= 0) {
        insere_exclusivo(l3, vetor3[i++]);
    }
    printf("l3: "); imprime(l3); putchar('\n');

    // Apesar dos vetores 1 e 3 serem diferentes, as listas correspondentes
    // devem ser iguais
    assert(iguais(l1, l3)); // funcao assert() aborta se o parametro for falso!

    // Jah as listas 1 e 2 sao claramente diferentes, mesmo se tem o mesmo
    // tamanho
    assert(!iguais(l1, l2));

    // Concatena l2 no final de l1
    concatena_exclusivas(l1, l2);
    printf("l1: "); imprime(l1); putchar('\n');
    printf("l2: "); imprime(l2); putchar('\n');

    destroi(l1);
    destroi(l2);
    destroi(l3);

    return EXIT_SUCCESS;
}

