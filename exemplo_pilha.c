#include <stdlib.h>
#include <stdio.h>
#include "tipo.h"
#include "pilhagen.h"

int main(int argc, char* argv[]) {
    char nome[] = "Tuiuti";

    Pilha* pilha = cria(100);

    int i = 0;
    while (nome[i] != '\0') {
        push(pilha, &nome[i]);
        ++i;
    }
    printf("Dump da pilha: ");
    dump(pilha);
    putchar('\n');

    i = 0;
    while (!underflow(pilha)) { // enquanto nao esvaziar totalmente
        pop(pilha, &nome[i]);
        ++i;
    }
    printf("nome = %s\n", nome);

    destroi(pilha);

    return EXIT_SUCCESS;
}

