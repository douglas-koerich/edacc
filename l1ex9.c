#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

void remove_menores(fila*, unsigned);

#define NUM_ELEMENTOS 50

int main(void) {
    fila* exemplo = create(NUM_ELEMENTOS);
    unsigned num;
    do {
        printf("Digite um numero natural ou 0 (zero) para terminar: ");
        scanf("%u", &num);

        if (num > 0) {
            insert(exemplo, num);
        }
    } while (num != 0);

    puts("Conteudo da fila:");
    print(exemplo);
    putchar('\n');

    unsigned referencia;
    printf("Digite um numero natural de referencia: ");
    scanf("%u", &referencia);

    remove_menores(exemplo, referencia);

    puts("Conteudo da fila apos remocao:");
    print(exemplo);
    putchar('\n');

    destroy(exemplo);

    return EXIT_SUCCESS;
}

void remove_menores(fila* f, unsigned r) {
    if (f == NULL) {
        return;
    }
    fila* auxiliar = create(NUM_ELEMENTOS); // recebe os elementos nao removidos
    while (underflow(f) == false) {
        unsigned v = extract(f);
        if (v >= r) { // nao eh menor que a referencia?
            insert(auxiliar, v);
        }
    }
    while (underflow(auxiliar) == false) {
        insert(f, extract(auxiliar));
    }
    destroy(auxiliar);
}
