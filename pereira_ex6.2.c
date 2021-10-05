/* Crie uma funcao recursiva para calcular a soma 1 + 2 + 3 +...+ n,
   sendo n um numero natural. */

#include <stdlib.h>
#include <stdio.h>

unsigned i_soma(unsigned n) {
    unsigned total = 0, parcela = 1;
    while (parcela <= n) {
        total += parcela;
        ++parcela;
    }
    return total;
}

unsigned r_soma(unsigned n) {
    // Teste da condicao terminal:
    if (n == 0) {
        return 0;
    } else { // fase ativa da recursao:
        return n + r_soma(n - 1);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de argumentos");
        return EXIT_FAILURE;
    }
    unsigned num = atoi(argv[1]);
    printf("A soma dos %u termos eh %u\n", num, r_soma(num));
    return EXIT_SUCCESS;
}