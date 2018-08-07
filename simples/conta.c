#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lista.h"

int main(void) {
    srand((unsigned) time(NULL));

    Lista* lista = cria();

    tipo valor;
    do {
        valor = rand() % 20;
        insereInicio(lista, valor);
    } while (valor > 0);

    printf("Digite o valor a contar na lista: ");
    tipo x;
    scanf("%d", &x);
    unsigned n = numOcorrencias(lista, x);

    printf("O valor %d aparece %u vezes na lista.\n", x, n);

    destroi(lista);
    return EXIT_SUCCESS;
}
