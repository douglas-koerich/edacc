#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include "hash.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de parametros");
        printf("Uso: %s <tamanho>\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t tam = atoi(argv[1]);
    Hash* h = criar(tam);

    // Para demonstracao, vamos gerar um numero de registros que
    // com o mesmo tamanho da tabela hash
    int r;
    // srand((unsigned) time(NULL));
    for (r = 0; r < tam; ++r) {
        Registro reg;
        reg.chave = rand() % 1000;
        char c;
        do {
            c = rand() % 128;
        } while (!isgraph(c));
        reg.dado = c;
        if (inserir(h, &reg) == false) {
            puts("Nao foi possivel inserir nova chave");
        } else {
            printf("(%d,%c) ", reg.chave, reg.dado);
        }
    }
    putchar('\n');
    imprimir(h);

    int x;
    printf("Teste de busca: digite uma chave PRESENTE acima -> ");
    scanf("%d", &x);
    Registro* reg = buscar(h, x);
    if (reg == NULL) {
        puts("Chave nao encontrada!");
    } else {
        printf("Dado da chave: %c.\n", reg->dado);
    }
    printf("Teste de busca: digite uma chave AUSENTE acima -> ");
    scanf("%d", &x);
    reg = buscar(h, x);
    if (reg == NULL) {
        puts("Chave nao encontrada!");
    } else {
        printf("Dado da chave: %c.\n", reg->dado);
    }

    destruir(h);
    return EXIT_SUCCESS;
}
