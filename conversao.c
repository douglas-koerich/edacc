#include <stdlib.h>
#include <stdio.h>
#include "base.h"

#define MAX 100

void converte(unsigned, unsigned, char []);

int main(void) {
    printf("Digite o numero na base decimal: ");
    unsigned numero;
    scanf("%u", &numero);

    puts("Escolha uma base de destino (2-37)");
    unsigned base;
    do {
        printf("Base: ");
        scanf("%u", &base);
    } while (base < 2 || base > 37);

    char valor[100];
    converte(numero, base, valor);
    printf("O numero %u na base %u eh %s\n", numero, base, valor);

    return EXIT_SUCCESS;
}

void converte(unsigned n, unsigned b, char v[]) {
    Stack* pilha = create(MAX);

    unsigned quoc = n;
    while (quoc > 0) {
        unsigned resto = quoc % b;
        if (resto <= 9) {
            push(pilha, resto + '0'); // caractere correspondente ao valor
        } else {
            resto -= 10;
            push(pilha, resto + 'A');
        }
        quoc = quoc / b;
    }

    int i = 0;
    while (!underflow(pilha)) {
        v[i++] = pop(pilha);
    }
    v[i] = '\0'; // "fecha" a string

    destroy(pilha);
}