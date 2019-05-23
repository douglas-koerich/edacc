#include <stdlib.h>
#include <stdio.h>

int fib(int);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de parametros!");
        printf("Digite: %s <ordem>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int ordem = atoi(argv[1]);
    printf("O numero de ordem %d eh %d.\n", ordem, fib(ordem));
    return EXIT_SUCCESS;
}

int fib(int ordem) {
    if (ordem == 0 || ordem == 1) {
        return 1;
    } else {
        return fib(ordem-1) + fib(ordem-2);
    }
}

