#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "exerc4lista05.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de parametros");
        printf("Uso: %s <numero-de-nos>\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t tamanho = atoi(argv[1]);

    ListaInt* demo = criar();

    srand((unsigned) time(NULL));
    while (tamanho > 0) {
        inserir_cabeca(demo, rand() % 10000);
        --tamanho;
    }

    puts("Lista antes da ordenacao:");
    imprimir(demo);

    // Ordena a lista de forma crescente...
    coqueteleira(demo);

    puts("\nLista depois da ordenacao:");
    imprimir(demo);
    putchar('\n');

    destruir(demo);

    return EXIT_SUCCESS;
}

