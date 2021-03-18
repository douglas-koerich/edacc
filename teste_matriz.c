#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"

int main(void) {
    Matriz* nova_matriz = criar(2, 2); // cria matriz 2x2

    atribuir(nova_matriz, 1, 1, 3.14);
    atribuir(nova_matriz, 2, 1, 2.718281828);

    imprimir(nova_matriz);

    destruir(nova_matriz);

    return EXIT_SUCCESS;
}