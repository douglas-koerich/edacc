#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lista.h"

int main(void) {
    srand((unsigned) time(NULL));

    Lista* lista = cria();

    tipo valor;
    do {
        valor = rand() % 3;
        insereInicio(lista, valor);
    } while (valor > 0);

    size_t n = tamanho(lista);

    printf("A lista tem %zu elementos.\n", n);

    destroi(lista);
    return EXIT_SUCCESS;
}
