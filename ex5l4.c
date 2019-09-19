#include <stdlib.h>
#include <stdio.h>

size_t num_digitos(unsigned);

int main(void) {
    unsigned numero;
    printf("Digite um numero maior ou igual a zero: ");
    scanf("%u", &numero);

    size_t digitos = num_digitos(numero);

    printf("O numero tem %zd digitos\n", digitos);

    return EXIT_SUCCESS;
}

size_t num_digitos(unsigned n) {
    if (n < 10) {
        return 1;
    }
    size_t digitos = 1 + num_digitos(n / 10);
    return digitos;
}

