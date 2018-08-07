#include <stdlib.h>
#include <stdio.h>

int comprimento(unsigned);

int main(void) {
    unsigned num;
    printf("Digite um numero: ");
    scanf("%u", &num);

    int digitos = comprimento(num);

    printf("O comprimento de %d em digitos eh %d.\n", num, digitos);

    return EXIT_SUCCESS;
}

int comprimento(unsigned num) {
    if (num < 10) {
        return 1;
    }
    return 1 + comprimento(num / 10);
}
