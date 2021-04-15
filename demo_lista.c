#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

int main(void) {
    srand(2021);
    Lista* lst = create();

    int i;
    for (i = 1; i <= 10; ++i) {
        Registro reg;
        reg.chave = rand() % 100 + 1;
        reg.valor = 'A' + i - 1;

        Criterio cri;
        if (reg.chave > 50) {
            cri = CABECA;
        } else {
            cri = CAUDA;
        }
        insert(lst, &reg, cri);
    }

    print(lst);

    int chave_usuario;
    printf("Digite uma chave de busca na lista: ");
    scanf("%d", &chave_usuario);

    Registro aux;
    if (search(lst, chave_usuario, &aux)) {
        printf("O valor associado eh a letra %c\n", aux.valor);
        extract(lst, &aux, VALOR);
    } else {
        puts("Chave nao encontrada na lista");
    }

    print(lst);

    destroy(lst);

    return EXIT_SUCCESS;
}