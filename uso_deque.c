#include <stdlib.h>
#include <stdio.h>
#include "deque.h"

int main(void) {
    int sequencia[] = { 1, 2, 3, 5, 8, 13, 21, 34, -1 };

    // Cria deque para amostra
    deque* d = d_create(20);

    // Numeros impares sao inseridos no inicio, e numeros pares no fim do deque
    int i = 0;
    while (sequencia[i] != -1) {
        if (sequencia[i] % 2 == 0) {
            d_insert(d, sequencia[i], REAR);
        } else {
            d_insert(d, sequencia[i], FRONT);
        }
        ++i;
    }
    puts("Conteudo do deque apos insercoes:");
    d_print(d);
    putchar('\n');

    // Remove um elemento de cada extremidade
    d_extract(d, REAR);
    d_extract(d, FRONT);

    puts("Conteudo do deque apos remocoes:");
    d_print(d);
    putchar('\n');

    d_destroy(d);

    return EXIT_SUCCESS;
}