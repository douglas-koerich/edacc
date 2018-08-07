#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista_int.h"

int main(int argc, char* argv[]) {
    int i[] = { 1, 2, 3, 5, 7, 11, 13, 17, 19, -1 };

    Lista* l = NULL;    // lista nao existe (ainda)!
    l = cria();

    if (underflow(l)) {
        puts("Lista vazia, como esperado...");
    } else {
        puts("Vixi, deu xabu...");
        destroi(l);
        return EXIT_FAILURE;
    }

    // Insere o caractere no fim
    int j = 0;
    while (i[j] >= 0) {
        insere(l, FIM, i[j]);
        ++j;
    }
    // Imprime a lista
    imprime(l);
    putchar('\n');

    // Imprime o tamanho calculado
    printf("Comprimento da lista: %zd.\n", tamanho(l));

    destroi(l);

    EXIT_SUCCESS;
}

