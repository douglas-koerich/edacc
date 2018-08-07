#include <stdlib.h>
#include <stdio.h>
#include "pilhaint.h"

int main(void) {
    unsigned num10;
    unsigned base;

    printf("Digite o numero em decimal a converter: ");
    scanf("%u", &num10);
    do {
        printf("Digite a base de destino (2-9): ");
        scanf("%u", &base);
    } while (base < 2 || base > 9);

    PilhaInt* restos = cria();
    unsigned quociente = num10;
    while (quociente > 0) {
        unsigned resto = quociente % base;
        if (overflow(restos)) {
            puts("ERRO! Pilha cheia!");
            destroi(restos);
            return EXIT_FAILURE;
        }
        push(restos, resto);
        quociente = quociente / base;
    }

    printf("Valor na base %u eh ", base);
    while (!underflow(restos)) {
        unsigned resto = pop(restos);
        putchar(resto + '0');
    }
    putchar('\n');

    destroi(restos);
    return EXIT_SUCCESS;
}

