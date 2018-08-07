#include <stdlib.h>
#include <stdio.h>
#include "tad_lista_linear.h"

Registro vetor[] = {
    { 1, "Maria" },
    { 2, "Joao" },
    { 3, "Manoel" },
    { 4, "Joaquim" },
    { 5, "Estacio" },
    { -1, "nonono" }
};

int main(void) {
    Registro* r = vetor;
    ListaReg* lista = criar();
    printf("Lista: "); imprimir(lista); putchar('\n');
    while (r->chave > 0) {
        if (r->chave % 2 == 0) {
            inserir_cabeca(lista, r);
        } else {
            inserir_cauda(lista, r);
        }
        printf("Lista: "); imprimir(lista); putchar('\n');
        ++r;
    }
    remover_cabeca(lista);
    printf("Lista: "); imprimir(lista); putchar('\n');
    remover_cauda(lista);
    printf("Lista: "); imprimir(lista); putchar('\n');

    Registro* x = buscar(lista, 3);
    printf("Encontrei o registro do(a) %s.\n", x->nome);

    destruir(lista);

    return EXIT_SUCCESS;
}
