#include <stdio.h>
#include <string.h>
#include "pilha_ch.h"

#define TAM_STRING  50

void validaExpressao(const char*);
void imprimePosfixa(const char*);

int main() {
    char expressao[TAM_STRING];

    printf("Digite a expressao para avaliar os parenteses: ");
    gets(expressao);

    validaExpressao(expressao);
    imprimePosfixa(expressao);

    return 0;
}

void validaExpressao(const char* expressao) {
    // Cria uma pilha para auxiliar no teste de correspondencia dos ()...
    struct PilhaCh* auxiliar = cria();

    // Percorre a expressao...
    int i=0;
    while (expressao[i] != '\0') {  // ateh o fim da string...
        if (expressao[i] == '(') {
            // Empilha o abre-parenteses
            push(auxiliar, expressao[i]);
        }
        else if (expressao[i] == ')') {
            char abre;
            if (pop(auxiliar, &abre) == false) { // nao tinha ( na pilha!
                puts("Erro, expressao mal formada (fechamento sem abertura)!");
                break;
            }
        }
        ++i;
    }
    if (i == strlen(expressao)) {
        // Encerrou o laco sem erros (atingiu o ultimo indice)
        if (underflow(auxiliar)) {
            puts("Expressao correta!");
        }
        else {
            puts("Erro, expressao mal formada (sobra de parenteses)!");
        }
    }
    // Nao esquecer de destruir a pilha, liberando a memoria alocada dela
    destroi(auxiliar);
}

int prioOperador(char operador) {
    // TABELA DE PRIORIDADES DOS "OPERADORES"
    // (   --> prioridade 1
    // + - --> prioridade 2
    // * / --> prioridade 3
    // pow --> prioridade 4
    switch (operador) {
        case '(':
            return 1;

        case '+': case '-':
            return 2;

        case '*': case '/':
            return 3;

        default: // pra simplificar...
            return 4;
    }
}

void imprimePosfixa(const char* infixa) {
    printf("Expressao pos-fixa: ");

    // Cria uma pilha para guardar os OPERADORES (porque eles vem DEPOIS
    // dos operandos)
    struct PilhaCh* operadores = cria();

    // Percorre a expressao...
    int i=0;
    while (infixa[i] != '\0') {
        switch (infixa[i]) {
            case '(':
                // Todo abre-parenteses eh empilhado (sempre!)
                push(operadores, infixa[i]);
                break;

            case ')': {
                // Enquanto nao encontrar o correspondente de abertura,
                // desempilha os operadores
                char operador;
                while (pop(operadores, &operador)) {
                    if (operador == '(') {
                        break;
                    }
                    else {
                        // Sendo outro operador, poe na expressao de saida
                        putchar(operador);
                    }
                }
                break;
            }
            case '+': case '-': case '*': case '/': // vou ignorar potencia pra simplificar...
                while (!underflow(operadores)) {
                    char operador;
                    pop(operadores, &operador);
                    if (prioOperador(operador) >= prioOperador(infixa[i])) {
                        // Operadores na pilha com prioridades maiores que
                        // o atual sao removidos e postos na saida
                        putchar(operador);
                    }
                    else {
                        // Devolve o operador lido da pilha que eh de
                        // prioridade menor que o atual
                        push(operadores, operador);
                        break;
                    }
                }
                // Depois de ter removido os operadores de maior
                // prioridade, empilha este que acabou de vir da
                // expressao infixa
                push(operadores, infixa[i]);
                break;

            default:
                // Operandos vao direto para expressao de saida
                putchar(infixa[i]);
        }
        ++i;
    }
    // Poe na expressao de saida os operadores que ficaram na pilha
    while (!underflow(operadores)) {
        char operador;
        pop(operadores, &operador);
        putchar(operador);
    }
    putchar('\n');

    // Destroi a pilha auxiliar
    destroi(operadores);
}

