#include <stdlib.h>
#include <stdio.h>
#include <math.h>

size_t num_algarismos_r(unsigned, size_t);

size_t num_algarismos(unsigned numero) {
    return num_algarismos_r(numero, 1);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de parametros!");
        printf("Use: %s <numero>\n", argv[0]);
        return EXIT_FAILURE;
    }
    unsigned numero = atoi(argv[1]);
    size_t digitos = num_algarismos(numero);
    printf("O numero de algarismos do numero %u eh %zd.\n", numero, digitos);
    return EXIT_SUCCESS;
}

size_t num_algarismos_r(unsigned numero, size_t grandeza) {
    if (numero < pow(10, grandeza)) {
        return grandeza;
    }
    return num_algarismos_r(numero, grandeza+1);
}

