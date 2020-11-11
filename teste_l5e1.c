#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "l5e1.h"

#define NUM_ITENS 3

int main(void) {
    srand((unsigned) time(NULL));

    List* lista = create();

    int i;
    for (i = 1; i <= NUM_ITENS; ++i) {
        Record registro = { rand() % 100 + 1, rand() % 26 + 'A' };
        insert(lista, &registro);
    }

    puts("Conteudo da lista ANTES da ordenacao:");
    print(lista);
    putchar('\n');

    sort(lista);

    puts("Conteudo da lista DEPOIS da ordenacao:");
    print(lista);
    putchar('\n');

    destroy(lista);

    return EXIT_SUCCESS;
}