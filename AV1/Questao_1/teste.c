#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"

const char* portugal[] = { "Maria", "Joao", "Manoel", "Joaquim", "Estacio", "" };
const char* england[] = { "Mary", "John", "Edward", "William", "Philip", "" };

ListaPalavras* mesclar_inversa(const ListaPalavras* l1, const ListaPalavras* l2);

int main(void) {
    const char** vp = portugal;
    const char** ve = england;

    ListaPalavras* lp = criar();
    while (strlen(*vp) > 0) {
        inserir(lp, *vp++);
    }
    ListaPalavras* le = criar();
    while (strlen(*ve) > 0) {
        inserir(le, *ve++);
    }
    printf("Portugal: "); imprimir(lp); putchar('\n');
    printf("England: "); imprimir(le); putchar('\n');

    ListaPalavras* lm = mesclar_inversa(lp, le);
    printf("Merged: "); imprimir(lm); putchar('\n');
    destruir(lm);

    remover(lp, "Maria");
    remover(lp, "Estacio");
    remover(le, "Mary");

    printf("Portugal: "); imprimir(lp); putchar('\n');
    printf("England: "); imprimir(le); putchar('\n');

    lm = mesclar_inversa(lp, le);
    printf("Merged: "); imprimir(lm); putchar('\n');
    destruir(lm);

    destruir(lp);
    destruir(le);

    return EXIT_SUCCESS;
}
