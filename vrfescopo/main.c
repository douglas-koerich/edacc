/* PROBLEMA: Escreva um programa que abra um arquivo-fonte em linguagem C qualquer
 * e retorne VERDADEIRO/FALSO se o codigo tem algum "descasamento" nos seguintes
 * delimitadores: {}, [], (). Por exemplo, a linha abaixo estah ok:
 * int c = (x + y) * (w - z);
 * enquanto as linhas a seguir nao estao corretas:
 * {
 *     int c = (x + y) * (w - z);
 * -fim do arquivo-
 * pois faltou o } antes de terminar o arquivo.
 * Utilize uma pilha como estrutura de dados de apoio para essa verificacao.
 */

#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de parametros");
        printf("Uso: %s <arquivo-fonte.c>\n", argv[0]);
        return EXIT_FAILURE;
    }
    FILE* arquivo_fonte = fopen(argv[1], "rt");
    if (arquivo_fonte == NULL) {
        perror("Nao foi possivel abrir o arquivo");
        return EXIT_FAILURE;
    }
    Pilha* controle = cria();
    bool erro = false;
    while (!feof(arquivo_fonte) && !erro) {
        char c = fgetc(arquivo_fonte);
        switch (c) {
            case EOF:
                if (ferror(arquivo_fonte)) {
                    perror("Nao foi possivel ler o arquivo");
                    fclose(arquivo_fonte);
                    return EXIT_FAILURE;
                }
                break;

            case '{':
            case '[':
            case '(':
                if (overflow(controle) == false) {
                    push(controle, c);
                    /* DEBUG */
                    printf("Pilha: ");
                    imprime(controle);
                    putchar('\n');
                }
                break;

            case '}':
                if (underflow(controle) == true) {
                    erro = true;
                } else {
                    char x = pop(controle);
                    /* DEBUG */
                    printf("Pilha: ");
                    imprime(controle);
                    putchar('\n');
                    if (x != '{') {
                        erro = true;
                    }
                }
                break;

            case ']':
                if (underflow(controle) == true) {
                    erro = true;
                } else {
                    char x = pop(controle);
                    /* DEBUG */
                    printf("Pilha: ");
                    imprime(controle);
                    putchar('\n');
                    if (x != '[') {
                        erro = true;
                    }
                }
                break;

            case ')':
                if (underflow(controle) == true) {
                    erro = true;
                } else {
                    char x = pop(controle);
                    /* DEBUG */
                    printf("Pilha: ");
                    imprime(controle);
                    putchar('\n');
                    if (x != '(') {
                        erro = true;
                    }
                }
                break;

            default:
                // outro caractere, ignora
                break;
        }
    }
    fclose(arquivo_fonte);
    if (!underflow(controle)) {
        erro = true;
    }
    destroi(controle);
    if (erro == true) {
        puts("Arquivo com problema em operadores de escopo");
    } else {
        puts("Arquivo OK!");
    }
    return EXIT_SUCCESS;
}

