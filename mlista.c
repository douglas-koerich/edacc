#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lista.h"

int main(void) {
    TipoChave chave = 1;
    srand(time(NULL));

    Lista* teste = cria();
    while (chave <= 10) {
        // Cria um registro randomico
        TipoReg reg;
        snprintf(reg.dado, sizeof(reg.dado), "%d", rand());
        if (chave % 3 == 0) {
            inserir(teste, chave, &reg, INICIO);
        } else {
            inserir(teste, chave, &reg, FIM);
        }
        imprime(teste); // para acompanhar a evolucao da lista
        ++chave;
    }
    TipoReg r = remover(teste, 0, INICIO); // Valor 0 porque nao vai ser remocao por VALOR
    printf("Removido registro '%s'\n", r.dado);
    imprime(teste);
    r = remover(teste, 0, FIM);
    printf("Removido '%s'\n", r.dado);
    imprime(teste);

    printf("Digite uma chave para buscar: ");
    scanf("%d", &chave);
    TipoReg* preg = busca(teste, chave);
    if (preg != NULL) {
        printf("Encontrei o registro '%s'\n", preg->dado);
    } else {
        puts("Chave nao existe na lista");
    }

    destroi(teste);

    return EXIT_SUCCESS;
}

