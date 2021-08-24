/* Algoritmo de conversao de expressao infixa para posfixa:
   - inicia com expressao posfixa vazia
   - para todo elemento da expressao infixa faca:
     -- se elemento for operando entao
          copia para expressao posfixa
        senao (eh operador: + - * / % ^ () )
          se operador da expressao infixa for parentese de abertura '(' entao
            empilha o operador
          senao
            se operador da expressao infixa for parentese de fechamento ')' entao
              enquanto nao desempilha um operador de abertura faca
                desempilha o operador para expressao posfixa
              fim-enquanto
            senao
              enquanto a precedencia do operador que estah no topo for maior que a da expressao fixa faca
                desempilha o operador para expressao posfixa
              fim-enquanto
              empilha o operador da expressao infixa
            fim-se
          fim-se
        fim-se
   - ao fim da expressao infixa, esvazia a pilha com operadores remanescentes copiando-os para a expressao posfixa */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilha.h"

unsigned precedencia(char operador);
bool eh_operador(char caractere);
void infixa_para_posfixa(char* posfixa, const char* infixa);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        puts("Numero invalido de argumentos");
        printf("Uso: %s <expressao-infixa-sem-espacos>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char expressao[strlen(argv[1]) * 2];
    infixa_para_posfixa(expressao, argv[1]);
    puts(expressao);

    return EXIT_SUCCESS;
}

unsigned precedencia(char operador) {
    unsigned p;
    switch (operador) {
        case '^':
            p = 3;
            break;
        case '*':
        case '/':
        case '\\':
        case '%':
            p = 2;
            break;
        case '+':
        case '-':
            p = 1;
            break;
        case '(':
            p = 0; // para efeito pratico do algoritmo
            break;
        default:
            printf("Operador %c invalido, abortando...\n", operador);
            exit(EXIT_FAILURE);
    }
    return p;
}

bool eh_operador(char caractere) {
    return caractere == '(' || caractere == ')' ||
           caractere == '+' || caractere == '-' ||
           caractere == '*' || caractere == '/' ||
           caractere == '\\' || caractere == '%' ||
           caractere == '^';
}

void infixa_para_posfixa(char* posfixa, const char* infixa) {
    pilha* auxiliar = create(1024);
    int p = 0, i = 0;
    while (infixa[i] != '\0') {
        if (!eh_operador(infixa[i])) {
            posfixa[p++] = infixa[i];
            posfixa[p++] = ' ';
        } else {
            if (infixa[i] == '(') {
                push(auxiliar, infixa[i]);
            } else if (infixa[i] == ')') {
                while (top(auxiliar) != '(') {
                    posfixa[p++] = pop(auxiliar);
                    posfixa[p++] = ' ';
                }
                pop(auxiliar); // descarta o '('
            } else {
                while (!underflow(auxiliar) &&
                       precedencia(top(auxiliar)) > precedencia(infixa[i])) {
                    posfixa[p++] = pop(auxiliar);
                    posfixa[p++] = ' ';
                }
                push(auxiliar, infixa[i]);
            }
        }
        ++i;
    }
    while (!underflow(auxiliar)) {
        posfixa[p++] = pop(auxiliar);
        posfixa[p++] = ' ';
    }
    destroy(auxiliar);

    posfixa[p] = '\0'; // finaliza a string da expressao posfixa
}