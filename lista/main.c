#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

int main(void) {
    // Cria uma lista encadeada vazia
    struct Lista* lista = cria();
    struct Lista* igual = cria();
    struct Lista* diferente = cria();

    // Gera um conjunto de registros para serem armazenados na lista
    int chave;
    for (chave = 1; chave <= 5; ++chave) {
        Reg r = { chave, rand() % 100 };
        insereFim(lista, &r);
        insereFim(igual, &r);
        insereFim(diferente, &r);
    }
    printf("Lista inicial: "); imprime(lista); putchar('\n');

    // Remove um elemento do inicio e outro do fim da lista
    removeInicio(lista);
    removeInicio(igual);
    printf("Apos remocao do primeiro: "); imprime(lista); putchar('\n');
    if (compara(lista, igual) == true) {
        puts("Listas 'lista' e 'igual' sao iguais!");
    }
    else {
        puts("Listas 'lista' e 'igual' sao DIFERENTES X-o");
    }
    if (compara(lista, diferente) == true) {
        puts("Listas 'lista' e 'diferente' sao IGUAIS X-o");
    }
    else {
        puts("Listas 'lista' e 'diferente' sao diferentes!");
    }
    removeInicio(diferente);    // tornei igual novamente
    removeFim(lista);
    removeFim(igual);
    printf("Apos remocao do ultimo: "); imprime(lista); putchar('\n');
    if (compara(lista, igual) == true) {
        puts("Listas 'lista' e 'igual' sao iguais!");
    }
    else {
        puts("Listas 'lista' e 'igual' sao DIFERENTES X-o");
    }
    if (compara(lista, diferente) == true) {
        puts("Listas 'lista' e 'diferente' sao IGUAIS X-o");
    }
    else {
        puts("Listas 'lista' e 'diferente' sao diferentes!");
    }
    removeFim(diferente);    // tornei igual novamente

    // Adiciona um novo elemento ao inicio da lista e outro ao final dela
    Reg i = { 0, 1 }, f = { 100, 99 };
    insereInicio(lista, &i);
    printf("Apos novo primeiro: "); imprime(lista); putchar('\n');
    insereFim(lista, &f);
    printf("Apos novo ultimo: "); imprime(lista); putchar('\n');

    // Testa operacao de busca na lista
    if (busca(lista, 3) == NULL) {
        puts("Chave 3 NAO encontrada!");
    }
    else {
        puts("Chave 3 encontrada!");
    }
    if (busca(lista, 50) == NULL) {
        puts("Chave 50 NAO encontrada!");
    }
    else {
        puts("Chave 50 encontrada!");
    }

    // Teste da insercao em ordem
    Reg inicio = { -1, 1001 }, meio = { 20, 1020 }, fim = { 110, 1110 };
    insereOrdem(lista, &inicio);
    printf("Apos insercao da chave -1: "); imprime(lista); putchar('\n');
    insereOrdem(lista, &meio);
    printf("Apos insercao da chave 20: "); imprime(lista); putchar('\n');
    insereOrdem(lista, &fim);
    printf("Apos insercao da chave 110: "); imprime(lista); putchar('\n');

    // Teste da remocao de chaves
    removeRegistro(lista, -1);
    printf("Apos remocao da chave -1: "); imprime(lista); putchar('\n');
    removeRegistro(lista, 20);
    printf("Apos remocao da chave 20: "); imprime(lista); putchar('\n');
    removeRegistro(lista, 110);
    printf("Apos remocao da chave 110: "); imprime(lista); putchar('\n');

    // Encerra lista
    destroi(lista);

    return EXIT_SUCCESS;
}
