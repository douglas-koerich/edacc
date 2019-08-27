#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

#define MAX_EXPRESSAO 256

bool valida_expressao(const char*);

int main(void) {
    char e[MAX_EXPRESSAO];
    puts("Digite uma expressao:");
    gets(e);

    if (valida_expressao(e)) {
        puts("A expressao eh valida.");
    } else {
        puts("A expressao esta incorreta.");
    }
    return EXIT_SUCCESS;
}

bool valida_expressao(const char* expr) {
    Pilha* limitadores = cria();
    bool valida = true;
    while (*expr != '\0' && valida == true) {
        char c;
        switch (*expr) {
            case '(': case '{': case '[':
                push(limitadores, *expr);
                break;

            case ')':
                if (pop(limitadores, &c) == false) {
                    valida = false;
                } else {
                    valida = c == '(';
                }
                break;

            case '}':
                if (pop(limitadores, &c) == false) {
                    valida = false;
                } else {
                    valida = c == '{';
                }
                break;

            case ']':
                if (pop(limitadores, &c) == false) {
                    valida = false;
                } else {
                    valida = c == '[';
                }
                break;

            case '\"':
                if (!underflow(limitadores)) {
                    pop(limitadores, &c);
                    if (c != '\"') {
                        push(limitadores, c);
                        push(limitadores, '\"');
                    }
                } else {
                    push(limitadores, '\"');
                }
                break;

            case '\'':
                if (!underflow(limitadores)) {
                    pop(limitadores, &c);
                    if (c != '\'') {
                        push(limitadores, c);
                        push(limitadores, '\'');
                    }
                } else {
                    push(limitadores, '\'');
                }
                break;

            default:
                ; // outro caractere, nada a fazer
        }
        ++expr;
    }
    if (valida == true) {
        valida = underflow(limitadores);
    }
    destroi(limitadores);
    return valida;
}
