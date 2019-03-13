#include <stdlib.h>
#include <stdio.h>
#include "pilhagen.h"

void dec2bin(char*, int); // char* <-- int

int main(void) {
    int i = 51;
    char s[33]; // 32 bits possiveis mais um terminador nulo
    dec2bin(s, i);
    printf("%d %o %x %s\n", i, i, i, s);
    return EXIT_SUCCESS;
}

void dec2bin(char* bin, int dec) {
    Pilha* aux = cria(32); // numero maximo de elementos (bits do numero)
    while (dec > 0) {
        int quoc = dec / 2;
        int resto = dec % 2;
        push(aux, &resto);
        dec = quoc; // para continuar o laco
    }
    // DEBUG: conteudo da pilha completa
    printf("Pilha: ");
    dump(aux);
    putchar('\n');

    // Construcao da string com os digitos binarios, caractere por caractere...
    int i = 0;
    while (!underflow(aux)) {
        int bit;
        pop(aux, &bit);
        bin[i] = bit + '0'; // conversao do inteiro para o ASCII correspondente
        ++i;
    }
    bin[i] = '\0'; // finaliza a string com o terminador nulo
    destroi(aux);
}

