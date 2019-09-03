#include <stdlib.h>
#include <stdio.h>

#include "pilha.h"

void remove_elemento(Pilha*, char);

int main(void) {
    char exemplo[] = { 'i', 'm', 'k', 'a', 'x' };
    int i;

    Pilha* S = cria();

    for (i=0; i<sizeof(exemplo)/sizeof(char); ++i) {
        if (push(S, exemplo[i])) {
            printf("Empilhado o caractere %c\n", exemplo[i]);
        }
    }

#ifdef DEBUG
    printf("S: "); imprime(S);
#endif

    char ch;
    printf("Digite um caractere: ");
    scanf(" %c", &ch);

    remove_elemento(S, ch);

#ifdef DEBUG
    printf("S: "); imprime(S);
#endif

    destroi(S);

    return EXIT_SUCCESS;
}

void remove_elemento(Pilha* p, char c) {
    Pilha* p_aux = cria();
    char c_aux;

    while (!underflow(p)) {
        pop(p, &c_aux);
        if (c_aux != c) {
            push(p_aux, c_aux);
        }
    }

    while (!underflow(p_aux)) {
        pop(p_aux, &c_aux);
        push(p, c_aux);
    }

    destroi(p_aux);
}

