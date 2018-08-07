#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "pilhaint.h"

int main(void) {
    puts("===========================");
    puts("Minha calculadora com pilha");
    puts("===========================");

    PilhaInt* resultados = cria();

    int operando1, operando2, resultado;
    char operacao;
    bool inicio = true;
    for (;;) {
        if (inicio) {
            printf("Operando 1? ");
            scanf("%d", &operando1);
        } else {
            operando1 = resultado;
            printf("Operando 1: %d\n", operando1);
        }
        do {
            printf("Operacao (+-*/, U para voltar resultado anterior, F para finalizar)? ");
            scanf(" %c", &operacao);
            operacao = tolower(operacao);
        } while (operacao != '+' && operacao != '-' &&
                 operacao != '*' && operacao != '/' &&
                 operacao != 'u' && operacao != 'f');
        if (operacao == 'f') {
            destroi(resultados);
            return EXIT_SUCCESS;
        }
        if (operacao == 'u') {
            if (!underflow(resultados)) {
                resultado = pop(resultados);
            } else {
                inicio = true;
            }
            continue;
        }
        printf("Operando 2? ");
        scanf("%d", &operando2);
        switch (operacao) {
            case '+':
                resultado = operando1 + operando2;
                break;
            case '-':
                resultado = operando1 - operando2;
                break;
            case '*':
                resultado = operando1 * operando2;
                break;
            case '/':
                resultado = operando1 / operando2;
                break;
        }
        printf("Resultado: %d\n\n", resultado);
        push(resultados, operando1);
        inicio = false;
    }
}

