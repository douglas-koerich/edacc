#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

int iguais(pilha*, pilha*);

int main(void) {
    int sequencia1[] = { 1, 2, 3, 4, 5, -1 },
        sequencia2[] = { 1, 2, 3, 6, 5, -1 },
        sequencia3[] = { 2, 3, 4, 5, -1 };

    const size_t TAMANHO_PILHA = 10;
    pilha* p1 = create(TAMANHO_PILHA),
         * p2 = create(TAMANHO_PILHA),
         * p3 = create(TAMANHO_PILHA),
         * p4 = create(TAMANHO_PILHA);
    
    int i = 0;
    while (sequencia1[i] >= 0) {
        push(p1, sequencia1[i]);
        push(p4, sequencia1[i++]);
    }
    puts("Pilha 1:");
    print(p1);
    putchar('\n');

    i = 0;
    while (sequencia2[i] >= 0) {
        push(p2, sequencia2[i++]);
    }
    puts("Pilha 2:");
    print(p2);
    putchar('\n');
    
    i = 0;
    while (sequencia3[i] >= 0) {
        push(p3, sequencia3[i++]);
    }
    puts("Pilha 3:");
    print(p3);
    putchar('\n');
    
    puts("Pilha 4:");
    print(p4);
    putchar('\n');
    
    if (iguais(p1, p2)) {
        puts("P1 e P2 sao iguais");
    } else {
        puts("P1 e P2 sao diferentes");
    }
    
    if (iguais(p1, p3)) {
        puts("P1 e P3 sao iguais");
    } else {
        puts("P1 e P3 sao diferentes");
    }

    if (iguais(p1, p4)) {
        puts("P1 e P4 sao iguais");
    } else {
        puts("P1 e P4 sao diferentes");
    }

    puts("Pilha 1:");
    print(p1);
    putchar('\n');
    puts("Pilha 2:");
    print(p2);
    putchar('\n');
    puts("Pilha 3:");
    print(p3);
    putchar('\n');
    puts("Pilha 4:");
    print(p4);
    putchar('\n');

    destroy(p1);
    destroy(p2);
    destroy(p3);
    destroy(p4);
    
    return EXIT_SUCCESS;
}

int iguais(pilha* p1, pilha* p2) {
    if (p1 == NULL || p2 == NULL) {
        return 0;
    }
    if (size(p1) != size(p2)) {
        return 0;
    }
    size_t tamanho = size(p1);
    pilha* aux1 = create(tamanho),
         * aux2 = create(tamanho);

    int resultado = 1;

    while (!underflow(p1) && resultado == 1) {
        int n1 = pop(p1), n2 = pop(p2);
        if (n1 != n2) {
            push(p1, n1);
            push(p2, n2);
            resultado = 0;
        } else {
            push(aux1, n1);
            push(aux2, n2);
        }
    }
    while (!underflow(aux1)) {
        push(p1, pop(aux1));
        push(p2, pop(aux2));
    }
    destroy(aux1);
    destroy(aux2);

    return resultado;
}