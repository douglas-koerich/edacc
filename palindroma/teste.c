#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // strlen()
#include <ctype.h> // toupper()
#include "pilha.h"

// Prototipo da funcao de teste
bool testa_palindroma(const char []);

int main(int argc, char* argv[]) {
    // A string a ser verificada deve ser recebida como argumento
    // da linha de comando do programa
    if (argc < 2) {
        puts("Numero insuficiente de parametros");
        printf("Uso: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (testa_palindroma(argv[1])) {
        puts("A string eh palindroma");
    } else {
        puts("A string NAO eh palindroma");
    }
    return EXIT_SUCCESS;
}

bool testa_palindroma(const char string[]) {
    Pilha* aux = cria(strlen(string));
    int i = 0;
    while (string[i] != '\0') {
        push(aux, string[i++]); // empilha o caractere e vai ao proximo
    }
    // O teste consiste em comparar a sequencia de caracteres direta
    // da string com o conteudo armazenado na pilha (sequencia inversa)
    bool eh_palindroma_sim_senhor = true;
    i = 0;
    while (!underflow(aux) && eh_palindroma_sim_senhor) {
        char c = pop(aux);
        if (toupper(c) != toupper(string[i++])) { // desconsidera maius/minus
            eh_palindroma_sim_senhor = false;
        }
    }
    destroi(aux);
    return eh_palindroma_sim_senhor; // ou nao...
}

