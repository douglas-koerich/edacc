#include <stdlib.h>
#include <stdio.h>
#include "exerc1lista02.h"

void imprime_dupla(ListaInt* l1, ListaInt* l2) {
    printf("Lista1: "); imprimir(l1); putchar('\n');
    printf("Lista2: "); imprimir(l2); putchar('\n');
}

void preenche_lista(ListaInt* l, int* vetor) {
    int* pi = vetor;
    while (*pi > 0) {
        if (*pi % 2 == 0) {
            inserir_cabeca(l, *pi);
        } else {
            inserir_cauda(l, *pi);
        }
        ++pi;
    }
}

int main(void) {
    int vetor1[] = { 1, 2, 3, 4, 1, 5, 3, -1 };
    int vetor2[] = { 7, 9, 2, 8, 6, 4, 9, 7, 1, -1 };
	
    ListaInt* lista1 = criar();
    ListaInt* lista2 = criar();
    imprime_dupla(lista1, lista2);

    preenche_lista(lista1, vetor1);
    preenche_lista(lista2, vetor2);
    imprime_dupla(lista1, lista2);

    concatenar(lista1, lista2);
    printf("Lista1: "); imprimir(lista1); putchar('\n');

    destruir(lista1);

    return EXIT_SUCCESS;
}
