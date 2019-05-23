#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilhagen.h"

void conv_in2pos(char*, const char*);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        puts("Numero invalido de parametros!");
        printf("Uso: %s <expressao-sem-espacos>\n", argv[0]);
        return EXIT_FAILURE;
    }
    // Aloca um char extra para o terminador nulo da string
    char* posfixa = malloc(strlen(argv[1]) * (sizeof(char)+1));

    conv_in2pos(posfixa, argv[1]);

    printf("A expressao pos-fixa correspondente eh '%s'.\n", posfixa);

    free(posfixa);

    return EXIT_SUCCESS;
}

int peso_operador(char operador) {
    /* Cada operador algebrico terah um "peso" correspondente
     * ah sua precedencia (maior o peso, maior a precedencia);
     * o '(' serah considerado um "operador" com o MENOR peso.
     * Resumindo (podendo ser expandido):
     * '('                 = 1
     * '+' e '-'           = 2
     * '*', '/' e '%'      = 3
     * '^' (exponenciacao) = 4
     */
    int peso;
    switch (operador) {
        case '(' : peso = 1; break;
        case '+' : case '-': peso = 2; break;
        case '*' : case '/': case '%': peso = 3; break;
        case '^' : peso = 4; break;
        default : peso = 0; // nao deveria cair aqui...
    }
    return peso;
}

void conv_in2pos(char* pos, const char* in) {
    // Pilha de caracteres para armazenar os OPERADORES
    Pilha* p_oper = cria(strlen(in)); // pelo tamanho maximo da entrada

    // Varre a expressao de entrada (infixa)...
    int i = 0;
    while (in[i] != '\0') {
        // O que eh o caractere atual da expressao?
        switch (in[i]) {
            // Qualquer outro caractere que nao um operador
            default:
                // Copia o OPERANDO diretamente da infixa para pos-fixa
                *pos++ = in[i]; // copia o conteudo e DEPOIS incrementa
                break; // 'default' como clausula intermediaria requer 'break'

            case '(':
                // Abertura de parenteses eh SEMPRE empilhada
                push(p_oper, &in[i]);
                break;

            case ')': {
                // Desempilha ateh encontrar o '(' correspondente
                char c;
                do {
                    pop(p_oper, &c);
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
                while (!underflow(p_oper)) {
                    char c;
                    pop(p_oper, &c);
                    // O '(' tem o MENOR peso para "perder" sempre nesta
                    // comparacao com outros operadores (soh pode sair da
                    // pilha por causa do ')')
                    if (peso_operador(c) >= peso_operador(in[i])) {
                        *pos++ = c;
                    } else {
                        push(p_oper, &c); // volta pra pilha o de menor peso
                        break;
                    }
                }
                // Empilha o operador recem-lido da expressao
                push(p_oper, &in[i]);
                break;
        }
        ++i;
    }
    while (!underflow(p_oper)) {
        char c;
        pop(p_oper, &c);
        *pos++ = c;
    }
    destroi(p_oper);
}

