#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "pilhachar.h"

bool valida(const char* expressao);

int main(void) {
    char expressao[128];
    puts("Digite uma expressao em C abaixo:");
    gets(expressao);

    bool ok = valida(expressao);
    printf("A expressao estah ");
    if (ok) {
        puts("ok!");
    } else {
        puts("ERRADA!");
    }
    return EXIT_SUCCESS;
}

bool valida(const char* expressao) {
    PilhaChar* pilha = cria();
    bool ok = true;
    while (*expressao != '\0') {
        if (*expressao == '(') {
            push(pilha, *expressao);
        } else if (*expressao == ')') {
            if (underflow(pilha)) {
                ok = false;
                break;
            } else {
                pop(pilha);
            }
        }
        ++expressao;
    }
    if (!underflow(pilha)) {
        ok = false;
    }
    destroi(pilha);
    return ok;
}

