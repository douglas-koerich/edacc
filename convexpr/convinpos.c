#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilha.h"

void converte(char* posfixa, const char* infixa);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        puts("Numero invalido de parametros!");
        printf("Uso: %s <expressao-sem-espacos>\n", argv[0]);
        return EXIT_FAILURE;
    }
    // Aloca um char extra para o terminador nulo da string
    char* posfixa = malloc(strlen(argv[1]) * (sizeof(char)+1));

    converte(posfixa, argv[1]); // expressao infixa eh o 2o. argumento na
                                // linha de comando

    printf("A expressao pos-fixa correspondente eh '%s'.\n", posfixa);

    free(posfixa);

    return EXIT_SUCCESS;
}

static int peso(char operador) {
    /* Cada operador algebrico terah um "peso" correspondente ah sua precedencia
     * (maior o peso, maior a precedencia); o '(' serah considerado um "operador"
     * com o MENOR peso.
     * Resumindo (podendo ser expandido):
     * '('                 = 1 (qualquer operador encontrado depois dele eh mais
     *                          prioritario, ou seja, deve ser tratado antes)
     * '+' e '-'           = 2
     * '*', '/' e '%'      = 3 (note que incluimos o operador de resto tambem)
     * '^' (exponenciacao) = 4 (NAO eh um operador valido em C, usado aqui como
     *                          exemplo, apenas)
     */
    int p;
    switch (operador) {
        case '(' : p = 1; break;
        case '+' : case '-': p = 2; break;
        case '*' : case '/': case '%': p = 3; break;
        case '^' : p = 4; break;
        default : p = 0; // nao deveria cair aqui...
    }
    return p;
}

void converte(char* pos, const char* in) {
    // Pilha de caracteres para armazenar os OPERADORES
    Pilha* oper = cria(strlen(in)); // pelo tamanho maximo da entrada

    // Varre a expressao de entrada (infixa)...
    int i = 0;
    while (in[i] != '\0') {
        // O que eh o caractere atual da expressao?
        switch (in[i]) {
            // Qualquer outro caractere que nao um operador
            default:
                // Copia o OPERANDO diretamente da infixa para pos-fixa
                *pos++ = in[i]; // copia o conteudo e DEPOIS incrementa
                break; // mesmo o 'default' de um 'switch', se eh uma
                       // clausula intermediaria, requer 'break'

            case '(':
                // Abertura de parenteses eh SEMPRE empilhada
                push(oper, in[i]);
                break;

            case ')': {
                // Desempilha ateh encontrar o '(' correspondente
                char c;
                do {
                    c = pop(oper);
                    if (c != '(') {
                        // Apenas os operadores algebricos vao para a pos-fixa
                        *pos++ = c;
                    }
                } while (c != '(');
                break;
            }
            case '+': case '-':
            case '*': case '/': case '%':
            case '^':
                // Enquanto o operador que estiver no TOPO da pilha tiver
                // peso MAIOR-OU-IGUAL que o operador recem-lido da expressao,
                // desempilha para a pos-fixa
                while (!underflow(oper)) {
                    char c = pop(oper);
                    // O '(' tem o MENOR peso para "perder" sempre nesta
                    // comparacao com outros operadores (soh pode sair da
                    // pilha por causa do ')')
                    if (peso(c) >= peso(in[i])) {
                        *pos++ = c;
                    } else {
                        push(oper, c); // volta pra pilha o de menor peso
                        break;
                    }
                }
                // Empilha o operador recem-lido da expressao
                push(oper, in[i]);
                break;
        }
        ++i;
    }
    while (!underflow(oper)) {
        *pos++ = pop(oper);
    }
    destroi(oper);
}

