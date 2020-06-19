#include <stdlib.h>
#include <stdio.h>
#include "registro.h"
#include "hash.h"

#define NUM_REGISTROS 50

int main(void) {
    Hash* h = criar();

    puts("Antes das insercoes dos registros");
    imprimir(h);
    putchar('\n');

    unsigned i;
    for (i = 0; i < NUM_REGISTROS; ++i) {
        R r = { i, i };
        inserir(h, &r);
        
        printf("Apos a insercao do registro com chave %u:\n", i);
        imprimir(h);
        putchar('\n');
    }

    printf("Digite uma chave na tabela: ");
    unsigned x;
    scanf("%u", &x);

    if (buscar(h, x) == NULL) {
        puts("A chave nao foi encontrada");
    } else {
        puts("A chave foi encontrada");
    }

    destruir(h);

    return EXIT_SUCCESS;
}

