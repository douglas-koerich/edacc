#include <stdlib.h>
#include <stdio.h>

#include "elemento.h"
#include "pilha.h"

void consulta_pilha(const Pilha* p) {
    p_print(p);
    if (p_underflow(p) == true) {
        puts("Pilha vazia");
    } else {
        puts("Pilha nao-vazia");
    }
}

int main(void) {
    // Demonstra o funcionamento da pilha
    Pilha* uma_pilha = p_create();

    // Testa e imprime o conteudo da pilha (ainda vazia)
    consulta_pilha(uma_pilha);

    // Usa a pilha para armazenar alguns elementos
    TipoElemento sequencia[] = { 0x31, 0x32, 0x33, 0x34, 0x35 };
    int i;
    for (i = 0; i < sizeof(sequencia) / sizeof(TipoElemento); ++i) {
        push(uma_pilha, sequencia[i]);
    }

    // Testa e imprime de novo
    consulta_pilha(uma_pilha);

    // Remove todos os elementos
    while (!p_underflow(uma_pilha)) {
        TipoElemento e = pop(uma_pilha);
        printf("Removido elemento %#x\n", e);
        p_print(uma_pilha);
    }

    p_destroy(uma_pilha);

    return EXIT_SUCCESS;
}