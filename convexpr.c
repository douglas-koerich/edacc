#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "pilha.h"

#define MAX_INFIXA 128

void in2pos(const char*, char*);

int main(void) {
    char infixa[MAX_INFIXA];
    puts("Digite uma expressao infixa sem espacos entre operandos e operadores");
    gets(infixa);

    char posfixa[2*MAX_INFIXA]; // capacidade maior para conter os espacos em branco

    in2pos(infixa, posfixa);

    puts("A expressao pos-fixa correspondente eh:");
    puts(posfixa);

    return EXIT_SUCCESS;
}

int precedencia(char operador) {
    switch (operador) {
        case '*': case '/': case '%':
            return 2;

        case '+': case '-':
            return 1;

        default:
            return 0;
    }
    return 0;
}

void in2pos(const char* in, char* pos) {
    Pilha* operadores = cria();

    int i = 0, p = 0; // indices nas strings infixa e posfixa
    while (in[i] != '\0') {
        if (isalnum(in[i])) {   // eh um caractere diferente de um operador?
            pos[p++] = in[i++]; // copia para posfixa o operando (ou parte dele)
        } else {
            // Poe um espaco separador na expressao posfixa
            pos[p++] = ' ';

            // Empilhamento de operadores
            // 1. Se for abre-parenteses, empilha direto
            if (in[i] == '(') {
                push(operadores, '(');
            } else {
                char o;
                // 2. Se for fecha-parenteses, desempilha ateh o abre-parenteses
                // correspondente
                if (in[i] == ')') {
                    while (pop(operadores, &o)) { // enquanto pop estah desempilhando...
                        if (o == '(') {
                            break;  // para quando encontra o abre-parenteses que estava empilhado
                        } else {
                            pos[p++] = o; // ... poe na posfixa o operador que estava no topo
                        }
                    }
                } else {
                    // 3. Para outros operadores, deve obedecer a uma hierarquia entre eles:
                    // (mul & div = 2; soma & sub = 1; abre-par = 0)
                    while (pop(operadores, &o)) { // enquanto houver operador na pilha...
                        if (precedencia(o) >= precedencia(in[i])) { // se o que estava no topo
                                                                    // tem maior precedencia do
                                                                    // que o lido da infixa
                            pos[p++] = o;   // poe esse operador tirado da pilha na posfixa
                        } else {
                            // o operador que estava no topo tem precedencia menor, volta
                            // para a pilha
                            push(operadores, o);
                            break; // interrompe a remocao de operadores
                        }
                    }
                    // Empilha o operador que foi lido da infixa
                    push(operadores, in[i]);
                }
            }
            ++i;
        }
    }
    while (!underflow(operadores)) {
        pos[p++] = ' ';
        pop(operadores, pos+p);
        ++p;
    }
    destroi(operadores);
}
