#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        puts("Numero insuficiente de argumentos");
        printf("Uso: %s <numero-em-decimal> <base-destino>\n", argv[0]);
        puts("Onde: 'numero-em-decimal' eh um valor inteiro e positivo");
        puts("      'base-destino' eh um valor entre 2 e 36");
        return EXIT_FAILURE;
    }
    unsigned numero = atoi(argv[1]); // parametro 'numero-em-decimal'
    unsigned base = atoi(argv[2]); // parametro 'base-destino'
    if (base < 2 || base > 36) {
        puts("Base escolhida eh invalida (2-36)");
        return EXIT_FAILURE;
    }
    Pilha* apoio = create();
    while (numero > 0) {
        /*
        int quociente = numero / base;
        int resto = numero % base;
        push(apoio, resto);
        numero = quociente;
        */
        push(apoio, numero % base);
        numero /= base;
    }
    printf("O numero convertido para a base %u eh ", base);
    while (underflow(apoio) == false) { // !underflow
        int resto = pop(apoio);
        if (resto < 10) { // pode usar o algarismo arabico
            putchar(resto + 0x30); // v. aula de Arquitetura de Computadores
                                   // v. Progr. Estruturada: resto + '0'
        } else {
            putchar(resto - 10 + 'A');
        }
    }
    putchar('\n');
    destroy(apoio);

    return EXIT_SUCCESS;
}