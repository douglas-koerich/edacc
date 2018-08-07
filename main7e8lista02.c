#include <stdlib.h>
#include <stdio.h>
#include "exerc7e8lista02.h"

int main(void) {
    int vetor[] = { 1, 2, 3, 4, 5, 6, 7, -1 };

    ListaInt* lista = criar();
    printf("Lista: "); imprimir(lista); putchar('\n');

    int* pi = vetor;
    while (*pi > 0) {
        inserir_cabeca(lista, *pi);
        ++pi;
    }
    printf("Lista: "); imprimir(lista); putchar('\n');

    printf("O comprimento (numero de elementos) da lista eh %zu.\n", tamanho(lista));

    inverter(lista);
    printf("Lista: "); imprimir(lista); putchar('\n');

    destruir(lista);

    return EXIT_SUCCESS;
}
