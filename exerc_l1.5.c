#include <stdlib.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <ctype.h>
#include "pilha.h"

#define TAM_MAX_EXPRESSAO   64

int prio(char op) {
    switch (op) {
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
    char infixa[TAM_MAX_EXPRESSAO];
    printf("Digite a expressao na forma infixa: ");
    __fpurge(stdin);
    gets(infixa);

    char posfixa[TAM_MAX_EXPRESSAO];
    Pilha* aux = cria();
    int i = 0, p = 0;
    while (infixa[i] != '\0') {
        // Operando eh copiado diretamente da infixa pra posfixa
        if (isalnum(infixa[i])) {
            posfixa[p++] = infixa[i++];
            continue;
        }
        // Espacos sao ignorados nesta implementacao
        if (isspace(infixa[i])) {
            ++i;
            continue;
        }
        // Outros caracteres (provavelmente os operadores)...
        switch (infixa[i]) {
            // Abre-parenteses sempre eh empilhado diretamente,
            // SEM inspecao do que jah estah na pilha
            case '(': {
                generico op = { &infixa[i] };   // callback nula
                push(aux, &op);
                break;
            }
            // Ao encontrar o fecha-parenteses na infixa, tira
            // TODOS os operadores da pilha ateh encontrar o
            // abre-parenteses correspondente
            case ')': {
                char operador;
                do {
                    generico* op = pop(aux);
                    operador = *((char*) op->coisa);
                    free(op);
                    if (operador != '(') {
                        posfixa[p++] = operador;
                    }
                } while (operador != '(' && !underflow(aux));
                break;
            }
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '^': {
                // Antes de empilhar o novo operador, vai ateh
                // a pilha e...
                char topo;
                while (!underflow(aux)) {
                    generico* op = pop(aux);
                    topo = *((char*) op->coisa);
                    // ... tira da pilha (pondo na pos-fixa)
                    // TODOS os operadores com prioridade MAIOR-ou-IGUAL
                    // aquela do novo operador
                    if (prio(topo) >= prio(infixa[i])) {
                        posfixa[p++] = topo;
                        free(op);
                    } else {
                        // ATENCAO! Como foi necessario tirar o operador
                        // da pilha pra verificar sua prioridade, no caso
                        // dessa prioridade ser MENOR, ele precisa VOLTAR
                        // pra pilha, certo?!
                        push(aux, op);
                        free(op);
                        break;  // pahra de percorrer a pilha
                    }
                }
                // Depois de tirar da pilha os MAIS prioritarios
                // eh hora de por nela o novo operador
                generico op = { &infixa[i] } ;
                push(aux, &op);
                break;
            }
            default:
                puts("\nEXPRESSAO MAL-FORMADA!\n");
                destroi(aux);
                return EXIT_FAILURE;
        }
        ++i;
    }
    // Se ficaram operadores na pilha, eles terminam a expressao pos-fixa...
    while (!underflow(aux)) {
        generico* op = pop(aux);
        char operador = *((char*) op->coisa);
        posfixa[p++] = operador;
        free(op);
    }
    posfixa[p] = '\0';
    printf("Expressao pos-fixa: %s.\n", posfixa);

    destroi(aux);
    return EXIT_SUCCESS;
}

