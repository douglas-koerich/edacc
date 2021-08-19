#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pilha.h" // apesar de ser uma pilha de inteiros, vamos
                   // armazenar caracteres (na verdade, seus codigos ASCII)

bool testa_balanceada(const char* cadeia);

int main(void) {
    const char *EXEMPLO_OK_1 = "[{()()}{}]",    // tirados do exercicio no livro
               *EXEMPLO_OK_2 = "{[([{}])]}",
               EXEMPLO_NOK_1[] = "{[(}])",
               EXEMPLO_NOK_2[] = "{[)()([}";

    if (testa_balanceada(EXEMPLO_OK_1) == true) {
        puts("OK");
    } else {
        puts("NOK");
    }
    
    if (testa_balanceada(EXEMPLO_OK_2) == true) {
        puts("OK");
    } else {
        puts("NOK");
    }
    
    if (testa_balanceada(EXEMPLO_NOK_1) == true) {
        puts("OK");
    } else {
        puts("NOK");
    }
    
    if (testa_balanceada(EXEMPLO_NOK_2) == true) {
        puts("OK");
    } else {
        puts("NOK");
    }
    return EXIT_SUCCESS;
}

bool testa_balanceada(const char* cadeia) {
    bool r = true;

    pilha* p = create(strlen(cadeia));

    int i = 0;
    bool continua = true;
    while (continua) {
        switch (cadeia[i]) {
            case '(':
            case '[':
            case '{':
                push(p, cadeia[i]);
                break;

            // No topo da pilha deveria estar o simbolo de abertura
            // correspondente...
            case ')':
                if (top(p) == '(') {
                    pop(p); // ok, continua...
                } else {
                    r = continua = false; // nao combina, interrompe
                }
                break;

            case ']':
                if (top(p) == '[') {
                    pop(p);
                } else {
                    r = continua = false;
                }
                break;

            case '}':
                if (top(p) == '{') {
                    pop(p);
                } else {
                    r = continua = false;
                }
                break;

            case '\0':
                continua = false;
                break;

            default:
                puts("Caractere invalido, ignorado...");
        }
        ++i;
    }

    // Se a pilha nao sai do laco acima vazia, eh porque algum simbolo
    // de abertura ficou sem o correspondente simbolo de fechamento...
    if (underflow(p) == false) {
        r = false;
    }

    destroy(p);

    return r;
}