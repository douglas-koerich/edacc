#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lista.h"

int main(void) {
    Lista* teste = cria();

    srand(time(NULL));

    TipoChave chave = 1;
    while (chave <= 10) {
        TipoReg reg;
        snprintf(reg.dado, sizeof(reg.dado), "%d", rand() % 1000);
        if (chave % 3 == 0) {
            inserir(teste, chave, &reg, INICIO);
        } else {
            inserir(teste, chave, &reg, FIM);
        }
        imprime(teste); // para acompanhar a evolucao da lista
        printf("A lista tem agora %zd elementos.\n", tamanho(teste));
        ++chave;
    }

    destroi(teste);

    return EXIT_SUCCESS;
}

