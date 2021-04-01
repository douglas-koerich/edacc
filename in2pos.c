#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

/* Conversao de expressao algebrica da forma infixa (operando-operador-operando)
para posfixa (operando-operando-operador), utilizada na traducao para instrucoes
basicas da arquitetura de computadores */

void in2pos(const char*, char*);

#define MAX_COMPRIMENTO_EXPRESSAO 60

int main(void) {
    char infixa[MAX_COMPRIMENTO_EXPRESSAO + 1];
    char posfixa[MAX_COMPRIMENTO_EXPRESSAO + 1];

    // Exemplo de digitacao: (a + 3) * b - 10 / c
    puts("Digite abaixo uma expressao algebrica em formato da linguagem C");
    gets(infixa);

    in2pos(infixa, posfixa);

    puts("A expressao na forma posfixa (RPN) eh:");
    puts(posfixa);

    return EXIT_SUCCESS;
}

bool eh_operador(char simbolo) {
    /*
    switch (simbolo) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '(':
        case ')':
            return true;

        default:
            return false;
    }
    */
    return simbolo == '+' || simbolo == '-' || simbolo == '*' || simbolo == '/' || simbolo == '%' || simbolo == '(' || simbolo == ')';
}

int prio_operador(char operador) {
    if (operador == '*' || operador == '/' || operador == '%') {
        return 2; // mais alta
    }
    if (operador == '+' || operador == '-') {
        return 1;
    }
    return 0; // serah o caso do '(' ao entrar/sair da pilha
}

void in2pos(const char* infixa, char* posfixa) {
    Pilha* apoio = create();

    while (*infixa != '\0') {   // ateh o fim da string infixa
        if (!eh_operador(*infixa)) {
            *posfixa++ = *infixa; // copia o conteudo do endereco 'infixa' (caractere)
                                  // para o endereco 'posfixa', incrementando-o em seguida
        } else { // Eh um operador ou ()
            switch (*infixa) {
                case '(':
                    // Empilha diretamente, sem qualquer consideracao adicional
                    push(apoio, *infixa);
                    break;

                case ')': {
                    // Remove da pilha ateh encontrar o '(' correspondente
                    char operador;
                    do {
                        operador = pop(apoio);
                        if (operador != '(') {
                            *posfixa++ = operador;
                        }
                    } while (operador != '(');
                    break;
                }
                default:
                    // Enquanto o operador no topo tiver prioridade (precedencia)
                    // maior ou igual ao que estah na posicao atual da infixa,
                    // retira-o da pilha para a posfixa
                    while (!underflow(apoio) &&
                           prio_operador(*infixa) <= prio_operador(top(apoio))) {
                        *posfixa++ = pop(apoio);
                    }
                    // O operador vindo da infixa sempre vai pra pilha primeiro
                    push(apoio, *infixa);
            }
        }
        ++infixa;
    }
    // Pode ser que algum(ns) operador(es) tenham ficado na pilha para serem
    // adicionados ao fim da expressao na forma posfixa
    while (!underflow(apoio)) {
        *posfixa++ = pop(apoio);
    }

    destroy(apoio);

    *posfixa = '\0'; // "Fecha" a string com o terminador nulo
}