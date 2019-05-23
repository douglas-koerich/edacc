#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilhagen.h"

/* Funcao que verifica se uma expressao tem o numero correto de parenteses
 * de abertura e fechamento, na ordem tambem correta
 */
bool valida_expressao(const char*);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        puts("Numero invalido de parametros");
        printf("Uso: %s <expressao-sem-espacos>\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (valida_expressao(argv[1]) /* == true */) {
        puts("Expressao valida :-)");
    } else {
        puts("Expressao invalida :-(");
    }
    return EXIT_SUCCESS;
}

bool valida_expressao(const char* expr) {
    bool res = true;
    Pilha* p = cria(strlen(expr)); // reserva espaco suficiente para a expressao
    int i = 0;
    while (expr[i] != '\0') {
        if (expr[i] == '(') {
            push(p, &expr[i]);
        } else if (expr[i] == ')') {
            if (underflow(p)) { // nao ha uma abertura anterior pendente na pilha
                res = false; // expressao invalida
                break; // pode interromper a varredura na expressao (laco while)
            } else {
                char dummy;
                pop(p, &dummy);
            }
        } else {
            // Faz nada, continua pela expressao
        }
        ++i;
    }
    if (!underflow(p)) { // sobrou uma abertura sem fechamento?
        res = false;
    }
    destroi(p);
    return res;
}

