#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "tad_pilha_inteiros.h"

char* converte_para_base_N(uint64_t num, uint8_t base) {
    char* str = (char*) calloc(80, sizeof(char));   // usando calloc() memoria eh zerada (\0)
    PilhaInt* auxiliar = cria_pilha();
    uint64_t quociente = num;
    while (quociente > 0) {
        int resto = quociente % base;
        push(auxiliar, resto);
        quociente = quociente / base;
    }
    int pos_string = 0;
    while (underflow(auxiliar) == false) {
        int resto = pop(auxiliar);
        str[pos_string++] = resto + '0';  // converte pra algarismo em char/ASCII
    }
    destroi_pilha(auxiliar);
    return str;
}

int main() {
    printf("Digite o numero na base decimal: ");
    uint64_t numero;
    scanf("%lu", &numero);

    uint8_t base;
    do {
        printf("Digite a base de destino da conversao: ");
        scanf("%hhu", &base);
    } while (base < 2 || base > 9);

    char* string = converte_para_base_N(numero, base);
    printf("O numero %lu na base %hhu eh %s.\n", numero, base, string);

    free(string);

    return EXIT_SUCCESS;
}
