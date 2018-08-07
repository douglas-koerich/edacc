#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "registro.h"
#include "hash.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de parametros");
        printf("Use: %s <tamanho-tab-hashing>\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t tamanho = atoi(argv[1]);
    hash* h = cria_h(tamanho);

    // Gera 10 vezes mais chaves do que o tamanho da tabela hashing
    srand((unsigned) time(NULL));
    int contador = 0;
    while (contador <= 10 * tamanho) {
        registro aleatorio = {
            .chave = rand() % 1001,
            .valor = rand()
        };
        inserir_h(h, &aleatorio);
        ++contador;
    }
    // Imprime a tabela hashing
    printf("Tabela hashing com %zd posicoes:\n", tamanho);
    imprime_h(h);

    // Busca algumas chaves na tabela
    unsigned short x;
    do {
        printf("Digite uma chave para busca (0 para interromper): ");
        scanf("%hu", &x);

        if (x > 0) {
            registro* r = busca_h(h, x);
            if (r == NULL) {
                puts("Chave NAO encontrada!");
            } else {
                printf("Chave encontrada no registro %p com valor %d.\n", r, r->valor);
            }
        }
    } while (x > 0);

    destroi_h(h);

    return EXIT_SUCCESS;
}
