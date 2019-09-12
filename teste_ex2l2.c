#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

void poe_na_lista(Lista*, const char*);

int main(void) {
    char str1[] = "amor";
    char str2[] = "amora";
    char str3[] = "amOr";

    Lista* l0 = criar();
    Lista* l1 = NULL;

    if (compara(l0, l1) == true) {
        puts("Teste 1: resultado inesperado, listas l0 e l1 sao iguais(?)");
        return EXIT_FAILURE;
    }
    puts("Teste 1: resultado OK, l0 vazia e l1 inexistente sao diferentes");

    l1 = criar();
    if (compara(l0, l1) == false) {
        puts("Teste 2: resultado inesperado, listas l0 e l1 diferentes(?)");
        return EXIT_FAILURE;
    }
    puts("Teste 2: resultado OK, l0 e l1 sao igualmente vazias");

    poe_na_lista(l1, str1);
    if (compara(l0, l1) == true) {
        puts("Teste 3: resultado inesperado, listas l0 e l1 sao iguais(?)");
        return EXIT_FAILURE;
    }
    puts("Teste 3: resultado OK, l0 vazia e l1 nao vazia");

    poe_na_lista(l0, str1);
    if (compara(l0, l1) == false) {
        puts("Teste 4: resultado inesperado, listas l0 e l1 diferentes(?)");
        return EXIT_FAILURE;
    }
    puts("Teste 4: resultado OK, l0 e l1 tem o mesmo conteudo");

    Lista* l2 = NULL;
    if (compara(l1, l2) == true) {
        puts("Teste 5: resultado inesperado, listas l1 e l2 sao iguais(?)");
        return EXIT_FAILURE;
    }
    puts("Teste 5: resultado OK, l1 nao vazia e l2 inexistente sao diferentes");

    l2 = criar();
    poe_na_lista(l2, str2);
    if (compara(l1, l2) == true) {
        puts("Teste 6: resultado inesperado, listas l1 e l2 sao iguais(?)");
        return EXIT_FAILURE;
    }
    puts("Teste 6: resultado OK, l1 menor do que l2");

    Lista* l3 = criar();
    poe_na_lista(l3, str3);
    if (compara(l1, l3) == true) {
        puts("Teste 7: resultado inesperado, listas l1 e l3 sao iguais(?)");
        return EXIT_FAILURE;
    }
    puts("Teste 7: resultado OK, l1 diferente de l3");

    destruir(l0);
    destruir(l1);
    destruir(l2);
    destruir(l3);

    return EXIT_SUCCESS;
}

void poe_na_lista(Lista* l, const char* str) {
    if (l == NULL || str == NULL) {
        return;
    }
    if (!underflow(l)) { // nao faz nada se a lista jah tem conteudo
        return;
    }
    int i = 0;
    while (str[i] != '\0') {
        inserir(l, str[i], FIM, 0);
        ++i;
    }
#ifdef DEBUG
    printf("Lista: ");
    imprimir(l);
#endif
}

