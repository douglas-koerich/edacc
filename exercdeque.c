#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "deque.h"

void maior_menor(IDeque*, int*, int*);

int main() {
    srand((unsigned) time(NULL));

    IDeque* deque = cria();
    printf("Deque apos a criacao: ");
    print(deque);
    putchar('\n');

    int x;
    while (!overflow(deque) && (x=rand() % 100) % 19 != 0) {
        insere(deque, x, rand()%2==0? ESQ: DIR);
    }
    printf("Depois da geracao do conteudo: ");
    print(deque);
    putchar('\n');

    int maior, menor;
    maior_menor(deque, &maior, &menor);
    printf("O maior e o menor numero no deque sao, respectivamente: %d e %d.\n",
           maior, menor);

    printf("Deque apos a inspecao: ");
    print(deque);
    putchar('\n');

    destroi(deque);
    return EXIT_SUCCESS;
}

void maior_menor(IDeque* d, int* M, int* m) {
    IDeque* auxiliar = cria();
    Lado lado_original = ESQ, lado_auxiliar = DIR;
    unsigned contador = 0;
    while (!underflow(d)) {
        int num = remove_(d, lado_original);
        if (contador == 0) {
            *M = *m = num;
        }
        else {
            if (num > *M) {
                *M = num;
            }
            if (num < *m) {
                *m = num;
            }
        }
        insere(auxiliar, num, lado_auxiliar);
        ++contador;
    }
    while (!underflow(auxiliar)) {
        insere(d, remove_(auxiliar, lado_auxiliar), lado_original);
    }
    destroi(auxiliar);
}
