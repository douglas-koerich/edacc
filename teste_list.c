#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "list.h"

bool vogal(char c) {
    if (!isalpha(c)) {
        return false;
    }
    c = toupper(c);
    return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y';
}

int main(void) {
    List* lista = create();

    char letra;
    for (letra = 'A'; letra <= 'Z'; ++letra) {
        Record registro = { letra, letra }; // key = codigo ASCII (numero) do caractere
        if (vogal(letra)) {
            insert(lista, &registro, REAR); // vogais inseridas no fim da lista
        } else {
            insert(lista, &registro, FRONT); // consoantes no inicio
        }
    }

    // Testes de conteudo da lista
    printf("Comprimento (numero de elementos) da lista: %zu\n", size(lista));
    printf("Conteudo da lista: ");
    print(lista);
    putchar('\n');

    // Teste de busca na lista
    char teste;
    do {
        printf("Digite um caractere (ou # para terminar): ");
        scanf(" %c", &teste);
        if (find(lista, teste) == NULL) {
            puts("Caractere (chave de busca) nao encontrado");
        } else {
            puts("Caractere (chave) encontrado");
        }
    } while (teste != '#');

    // Teste de remocao da lista
    free(discard(lista, FRONT, -1)); // o valor -1 nao eh usado porque a remocao nao eh por KEY
                                     // chamou free() sobre o retorno porque 'discard' aloca o registro
                                     // que eh devolvido; quem recebe (aqui) deve libera-lo da memoria
    free(discard(lista, REAR, -1));
    printf("Conteudo da lista apos as remocoes: ");
    print(lista);
    putchar('\n');
    printf("Comprimento (numero de elementos) da lista: %zu\n", size(lista));

    destroy(lista);

    return EXIT_SUCCESS;
}