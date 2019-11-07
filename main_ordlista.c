#include <stdlib.h>
#include <stdio.h>
#include "registro.h"
#include "lista_reg.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        puts("Numero insuficiente de parametros");
        printf("Use: %s <tamanho-do-banco-de-dados> <semente>\n", argv[0]);
        return EXIT_FAILURE;
    }
    srand(atoi(argv[2]));

    size_t tamanho = atoi(argv[1]);
    Lista* database = criar();

    int i;
    puts("Banco de dados original:");
    for (i = 0; i < tamanho; ++i) {
        Reg registro;

        registro.chave = rand() % 10000 + 1;
        registro.dado = i + 'a'; // 'a' na cabeca, 'b' no segundo noh, ...
        printf("(%u,%c) ", registro.chave, registro.dado);

        inserir(database, &registro, CAUDA, 0);
    }
    putchar('\n');

    puts("Lista ANTES da ordenacao:");
    imprimir(database);

    ordenar(database); // implementa um dos algoritmos na lista de nohs/
                       // registros

    puts("Lista DEPOIS da ordenacao:");
    imprimir(database);

    destruir(database);
    return EXIT_SUCCESS;
}

