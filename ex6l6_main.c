#include <stdlib.h>
#include <stdio.h>
#include "ex6l6.h"

#define TAMANHO 10

int main(void) {
    struct TabelaHashing* tab = cria(TAMANHO);

    Registro reg;
    do {
        printf("Digite uma chave de registro para ser incluida na tabela (<0 para interromper): ");
        scanf("%d", &reg.chave);
        if (reg.chave >= 0) {
            insere(tab, &reg);
        }
    } while (reg.chave >= 0);

    imprime(tab);

    int chave;
    do {
        printf("Digite uma chave para localizar na tabela (<0 para interromper): ");
        scanf("%d", &chave);
        if (chave >= 0) {
            if (busca(tab, chave) == NULL) {
                puts("Chave NAO encontrada!");
            }
            else {
                puts("Chave encontrada com sucesso!");
            }
        }
    } while (chave >= 0);

    destroi(tab);

    return EXIT_SUCCESS;
}
