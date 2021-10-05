/* Crie uma funcao recursiva para calcular a soma dos n primeiros itens armazenados num vetor de numeros inteiros v. */

#include <stdlib.h>
#include <stdio.h>

int i_soma(const int* v, size_t n) {
    int i, total;
    for (i = total = 0; i < n; ++i) {
        total += v[i]; // total += *(v + i);
    }
    return total;
}

int r_soma(const int* v, size_t n) {
    if (n == 0) { // Condicao terminal: vetor de tamanho nulo
        return 0;
    } else { // Fase ativa: soma do inicio do "vetor" com o restante dele
        return v[0] + r_soma(&v[1], n-1);
    }
}

#define TAMANHO 5

int main(void) {
    int vetor[TAMANHO] = { 65, -43, 6, 12, 78 };
    printf("A soma dos itens do vetor-exemplo eh %d\n",
           r_soma(vetor, TAMANHO));
    return EXIT_SUCCESS;
}