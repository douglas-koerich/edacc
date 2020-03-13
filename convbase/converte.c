/* Este programa converte qualquer numero decimal inteiro positivo
 * em um outro numero nas bases 2 a 37 */
#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

#define MAX_DIGITOS 512

int main(int argc, char* argv[]) {
    // 1o. argumento deve ser o numero decimal positivo
    // 2o. argumento deve ser a base-alvo (2 a 37)
    if (argc < 3) {
        puts("Numero insuficiente de parametros");
        printf("Uso: %s <num-dec-positivo> <base>, onde:\n", argv[0]);
        puts("     <base> 2-37");
        return EXIT_FAILURE;
    }
    int numero = atoi(argv[1]);
    if (numero < 0) {
        puts("Parametro invalido: numero negativo");
        return EXIT_FAILURE;
    }
    int base = atoi(argv[2]);
    if (base < 2 || base > 37) {
        puts("Parametro invalido: base fora da faixa");
        return EXIT_FAILURE;
    }
    char convertido[MAX_DIGITOS] = ""; // inicializada com vazio

    Pilha* aux = cria(MAX_DIGITOS);
    int resto, quociente = numero;
    while (quociente > 0) {
        resto = quociente % base;
        quociente /= base; // divisao inteira
        push(aux, resto);
    }
    int i = 0;
    while (!underflow(aux)) {
        resto = pop(aux);
        if (resto < 10) {
            convertido[i] = resto + '0';
        } else {
            convertido[i] = (resto - 10) + 'A';
        }
        ++i;
    }
    convertido[i] = '\0'; // marca o fim da string
    printf("O numero %d na base %d eh %s\n", numero, base, convertido);

    destroi(aux);
    return EXIT_SUCCESS;
}

