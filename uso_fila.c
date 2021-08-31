#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "fila.h"

int main(void) {
    const char NOME_ARQUIVO[] = "/tmp/fila.bin";
    char opcao;
    fila* f = NULL;

    do {
        printf("(S)alvar ou (R)ecuperar a fila? ");
        scanf(" %c", &opcao);
        opcao = toupper(opcao);
    } while (opcao != 'S' && opcao != 'R');

    if (opcao == 'S') {
        const size_t MAX_FILA = 100;
        f = create(MAX_FILA);

        puts("Digite uma sequencia de numeros, terminando com um numero negativo:");
        int numero;
        do {
            scanf("%d", &numero);
            if (numero >= 0) {
                insert(f, numero);
            }
        } while (numero >= 0 && size(f) <= MAX_FILA);

        puts("Conteudo da fila:");
        print(f);
        putchar('\n');
        save(f, NOME_ARQUIVO);
    } else {
        f = restore(NOME_ARQUIVO);
        if (f == NULL) {
            return EXIT_FAILURE;
        }
        puts("Conteudo da fila:");
        print(f);
        putchar('\n');

        puts("Sequencia em que os valores foram digitados anteriormente:");
        while (!underflow(f)) {
            printf("%d ", extract(f));
        }
        putchar('\n');
    }

    destroy(f);

    return EXIT_SUCCESS;
}