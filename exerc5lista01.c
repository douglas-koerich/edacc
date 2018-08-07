#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilha_char.h"

#define MAX_COMPRIMENTO_EXPRESSAO   MAX_ELEMENTOS_PILHA

int prio_operador(char operador) {
    // Tabela de referencia para reordenar a expressao na forma pos-fixa
    struct PrioOperador {
        char operadores[3]; // string com os operadores desta prioridade (ex: "+-" ou "*/")
        int prioridade;
    } tabela_prioridades[] = {
        { "("  , 1 },   // abre-parenteses tem a menor prioridade entre operadores
        { "+-" , 2 },
        { "*/%", 3 },
        { "^"  , 4 }    // potenciacao tem a maior prioridade na comparacao
    };
    int j = 0;
    while (strchr(tabela_prioridades[j].operadores, operador) == NULL) {
        ++j;
    }
    return tabela_prioridades[j].prioridade;
}

int main(void) {

    char infixa[MAX_COMPRIMENTO_EXPRESSAO];
    char posfixa[MAX_COMPRIMENTO_EXPRESSAO] = {'\0'};   // expressao/string vazia
    unsigned contador_posfixa = 0;

    printf("Digite a expressao sem espacos em branco: ");
    fgets(infixa, sizeof(infixa), stdin);   // gets eh considerado inseguro!

    // Algoritmo de conversao
    // 1) Crie uma pilha de OPERADORES vazia
    Pilha_ch* operadores = cria();

    // 2) Percorra a expressao infixa ateh o seu fim:
    int i = 0;
    while (infixa[i] != '\0') {
        char c = infixa[i];

        // 2.1) Se for um operador: + - * / % ^
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^') {
            // Enquanto a pilha contiver algo E (logico) a prioridade do topo for
            // maior ou igual a prioridade desse operador (da vez), copie o topo
            // para a expressao posfixa
            while (underflow(operadores) == false) {
                char topo = pop(operadores);    // pra ver a prioridade tenho que tirar da pilha
                int prio_topo = prio_operador(topo);
                int prio_c = prio_operador(c);
                if (prio_topo >= prio_c) {
                    posfixa[contador_posfixa++] = topo;
                }
                else {
                    // Devolve o topo para a pilha jah que ele tem prioridade menor
                    // que o operador da vez
                    push(operadores, topo);
                    break;
                }
            }
            // Empilha o operador encontrado na infixa
            push(operadores, c);
        }
        // 2.2) Se for um parentese de abertura, empilha-o diretamente
        else if (c == '(') {
            push(operadores, c);
        }
        // 2.3) Se for um parentese de fechamento, remove todos os operadores da pilha
        // ateh encontrar o parentese de abertura
        else if (c == ')') {
            while (underflow(operadores) == false) {
                char topo = pop(operadores);
                if (topo != '(') {
                    posfixa[contador_posfixa++] = topo;
                }
                else {
                    break;
                }
            }
        }
        // (Ignora o \n lido do teclado)
        else if (c == '\n') {
            // Nao faz nada...
        }
        // 2.4) Todos os outros simbolos sao os operandos, copia-os diretamente para
        // a expressao posfixa
        else {
            posfixa[contador_posfixa++] = c;
        }
        ++i;
    }
    // Ao fim da varredura na infixa, algum(ns) operador(es) pode(m) ter ficado
    // na pilha, esvazia-a para a posfixa
    while (underflow(operadores) == false) {
        posfixa[contador_posfixa++] = pop(operadores);
    }
    // Nao esquece de destruir a pilha
    destroi(operadores);

    printf("A expressao pos-fixa correspondente eh %s.\n", posfixa);

    return EXIT_SUCCESS;
}
