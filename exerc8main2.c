#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "exerc8lista2.h"

int main() {
    srand((unsigned) time(0));

    struct Lista* l = cria();

    int i;
    for (i=1; i<=10; ++i) {
        int n = rand() % 1000;
        inserirFim(l, n);
    }
    imprime(l);
    inverte(l);
    imprime(l);

    destroi(l);

    return 0;
}

