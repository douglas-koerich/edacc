#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "lista.h"

#define TAM_LISTA 15
#define MAX_NUMERO 1000

int main(void) {
    srand(time(NULL));
    const int POSICAO = 5;

    ListaInt* lista_i = cria(); // insercoes e remocoes no inicio
    ListaInt* lista_f = cria(); // insercoes e remocoes no fim
    ListaInt* lista_o = cria(); // lista ordenada
    ListaInt* lista_5 = cria(); // lista onde se insere e remove na/da 5a. posicao

    int n;
    printf("Numeros gerados: ");
    for (n=1; n<=TAM_LISTA; ++n) {
        int numero = rand() % (MAX_NUMERO+1);
        printf("%d ", numero);

        insere(lista_i, INICIO, numero);
        insere(lista_f, FIM, numero);
        insere_ordem(lista_o, numero);
        insere_posicao(lista_5, numero, POSICAO);
    }
    putchar('\n');
    printf("lista_i: "); imprime(lista_i);
    putchar('\n');
    printf("lista_f: "); imprime(lista_f);
    putchar('\n');
    printf("lista_o: "); imprime(lista_o);
    putchar('\n');
    printf("lista_5: "); imprime(lista_5);
    putchar('\n');

    exclui(lista_i, INICIO);
    exclui(lista_f, FIM);
    exclui_posicao(lista_5, POSICAO);

    printf("lista_i: "); imprime(lista_i);
    putchar('\n');
    printf("lista_f: "); imprime(lista_f);
    putchar('\n');
    printf("lista_5: "); imprime(lista_5);
    putchar('\n');

    printf("Digite um valor para remover da lista_o: ");
    int valor;
    scanf("%d", &valor);
    exclui_valor(lista_o, valor);
    printf("lista_o: "); imprime(lista_o);
    putchar('\n');

    printf("Digite um valor que ESTEJA na lista_i: ");
    scanf("%d", &valor);
    assert(busca(lista_i, valor));

    printf("Digite um valor que *NAO* esteja na lista_i: ");
    scanf("%d", &valor);
    assert(!busca(lista_i, valor));

    destroi(lista_i);
    destroi(lista_f);
    destroi(lista_o);
    destroi(lista_5);

    return EXIT_SUCCESS;
}

