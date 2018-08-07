#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tad_pilha_caracteres.h"

bool eh_operador(char simbolo) {
    return strchr("()+-*/%^", simbolo) != NULL;
}

int prio_operador(char operador) {
    switch (operador) {
        case '(':
            return 1;

        case '+': case '-':
            return 2;

        case '*': case '/': case '%':
            return 3;

        case '^':
            return 4;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero invalido de argumentos");
        printf("Use: %s '<expressao-infixa-sem-espacos>'\n", argv[0]);
        puts("OBS: Use aspas simples (\') ou duplas (\") na expressao");
        return EXIT_FAILURE;
    }
    // calloc() inicializa area alocada com zeros binarios... :-)
    char* posfixa = (char*) calloc(strlen(argv[1]), sizeof(char));
    unsigned contador_posfixa = 0;
    PilhaChar* operadores = cria_pilha();

    int i;
    for (i=0; argv[1][i] != '\0'; ++i) {
        char c = argv[1][i];
        if (!eh_operador(c)) {
            posfixa[contador_posfixa++] = c;
            continue;
        }
        if (c == '(') {
            push(operadores, c);
        } else if (c == ')') {
            while (underflow(operadores) == false) {
                char topo = pop(operadores);
                if (topo != '(') {
                    posfixa[contador_posfixa++] = topo;
                } else {
                    break;
                }
            }
        } else {
            while (underflow(operadores) == false) {
                // Como a pilha nao tem uma operacao de leitura sem remocao,
                // pra testar a prioridade do operador que estah no topo sou
                // obrigado a tira-lo da pilha :-(
                char topo = pop(operadores);
                if (prio_operador(topo) >= prio_operador(c)) {
                    posfixa[contador_posfixa++] = topo;
                } else {
                    // Devolve o topo para a pilha jah que ele tem prioridade menor
                    // que o operador da vez :-(
                    push(operadores, topo);
                    break;
                }
            }
            push(operadores, c);
            imprime_pilha(operadores);
        }
    }
    while (underflow(operadores) == false) {
        posfixa[contador_posfixa++] = pop(operadores);
    }

    printf("A expressao pos-fixa correspondente eh %s.\n", posfixa);

    destroi_pilha(operadores);
    free(posfixa);
    return EXIT_SUCCESS;
}
