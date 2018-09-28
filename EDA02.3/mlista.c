#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "lista.h"

int main(void) {
    const char* strings[] = {
        "Batatinha",
        "quando",
        "nasce",
        "espalha",
        "rama",
        "pelo",
        "chao",
        ""
    };
    Lista* teste = cria();
    int i = 0;
    while (strlen(strings[i]) > 0) {
        inserir(teste, strings[i], FIM);
        imprime(teste);
        ++i;
    }
    remover(teste, NULL, INICIO);
    imprime(teste);
    remover(teste, NULL, FIM);
    imprime(teste);

    printf("Digite uma string para buscar: ");
    char s[80];
    gets(s);
    if (busca(teste, s)) {
        puts("Encontrei a string");
    } else {
        puts("String nao existe na lista");
    }

    puts("\nFazendo a ordenacao decrescente:");
    bubblesort_decrescente(teste);
    imprime(teste);

    destroi(teste);

    return EXIT_SUCCESS;
}

