#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lista.h"

int main(void) {
    int i = 1;
    srand(time(NULL));

    Lista* teste = cria();
    while (i <= 10) {
        inserir(teste, rand(), INICIO);
        imprime(teste);
        ++i;
    }
    remover(teste, 0, INICIO);
    imprime(teste);
    remover(teste, 0, FIM);
    imprime(teste);

    inverte(teste);
    imprime(teste);

    destroi(teste);

    return EXIT_SUCCESS;
}

