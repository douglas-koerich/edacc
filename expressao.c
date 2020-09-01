#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "operador.h"

#define TAM_MAX_EXPRESSAO 100

void converte(char*, const char*);
int prioridade_operador(char); // valor segundo tabela abaixo, ou 0 se nao for operador

/* Tabela de precedencia/prioridade entre operadores:
 * OPERADOR(ES)     PRIORIDADE
 * ^ (potencia)     4 (maior)
 * / % *            3
 * + -              2
 * ( (abre)         1
 */

int main(void) {
    char infixa[TAM_MAX_EXPRESSAO];
    char posfixa[TAM_MAX_EXPRESSAO];
    puts("Digite abaixo uma expressao infixa usada em programacao:");
    gets(infixa);

    converte(posfixa, infixa);

    puts("Expressao posfixa equivalente:");
    puts(posfixa);

    return EXIT_SUCCESS;
}

int prioridade_operador(char c) {
    switch (c) {
        case '^': // potencia
            return 4;

        case '*': case '/': case '%':
            return 3;

        case '+': case '-':
            return 2;

        case '(':
            return 1;

        default:
            return 0;
    }
    return -1;
}

void converte(char* pos, const char* in) {
    Stack* pilha_aux = create(TAM_MAX_EXPRESSAO);

    while (*in != '\0') {
        // Se for (parte do) operando, copia direto para posfixa
        if (isalnum(*in) || *in == '_') {
            *pos++ = *in;
        }
        // Se for o '(', empilha diretamente
        else if (*in == '(') {
            push(pilha_aux, *in);
        }
        // Se for o ')', desempilha ateh o primeiro '(' encontrado
        else if (*in == ')') {
            char c;
            do {
                if (underflow(pilha_aux)) {
                    puts("\nEXPRESSAO INVALIDA\n");
                    exit(EXIT_FAILURE);
                }
                c = pop(pilha_aux);
                if (c != '(') {
                    *pos++ = c;
                }
            } while (c != '(');
        }
        else {
            int prio = prioridade_operador(*in);
            if (prio > 1) { // eh um operador valido
                // Enquanto houver um operador no topo da pilha que tiver
                // prioridade (precedencia) MAIOR que este que acabou de ser
                // lido da infixa...
                while (!underflow(pilha_aux) &&
                       prioridade_operador(top(pilha_aux)) >= prio) {
                    // ... move-se para posfixa esse operador do topo
                    *pos++ = pop(pilha_aux);
                }
                // Empilha-se o operador recem-lido da expressao infixa
                push(pilha_aux, *in);
            }
        }
        ++in;
    }
    while (!underflow(pilha_aux)) {
        *pos++ = pop(pilha_aux);
    }
    destroy(pilha_aux);
    *pos = '\0'; // poe o terminador nulo no fim da expressao posfixa
}

