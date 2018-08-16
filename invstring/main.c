#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

void inverte(char*);

int main(void) {
    char teste[200];
    printf("Digite uma string para teste: ");
    gets(teste);

    inverte(teste);

    printf("String invertida: '%s'\n", teste);

    return EXIT_SUCCESS;
}

// Exemplo do USO de uma pilha por uma aplicacao
void inverte(char* string) {
    Pilha* pilha = cria();
    int pos = 0;
    while (string[pos] != '\0') {
        if (overflow(pilha) == false) { // ha espaco na pilha?
            push(pilha, string[pos]);
        } else {
            puts("Erro, pilha insuficiente!");
            destroi(pilha); // libera memoria
            exit(EXIT_FAILURE);
        }
        ++pos;
    }
    // Codigo de depuracao (debug): imprime a pilha pra ver o que
    // ela contem
    printf("Conteudo da pilha: ");
    imprime(pilha);
    putchar('\n');

    pos = 0; // posiciona-se no inicio da string novamente
    while (underflow(pilha) == false) { // ainda ha elementos na pilha?
        string[pos] = pop(pilha);
        ++pos;
    }
    destroi(pilha);
}

