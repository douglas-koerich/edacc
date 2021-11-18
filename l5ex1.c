#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "lista.h"

int main(void) {
    srand(20211118);
    list* conjunto = l_create();
    const size_t TAMANHO = 20;
    int i = 1;
    while (i++ <= TAMANHO) {
        l_insert(conjunto, rand() % 100, HEAD, 0);
    }
    puts("ANTES DA ORDENACAO");
    l_print(conjunto);
    putchar('\n');

    l_ascending_sort(conjunto);

    puts("DEPOIS DA ORDENACAO");
    l_print(conjunto);
    putchar('\n');

    l_destroy(conjunto);

    return EXIT_SUCCESS;
}