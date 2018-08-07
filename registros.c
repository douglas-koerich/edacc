/* Vamos modelar (e esse eh o primeiro passo) a entidade "carro" para ser usada
 * num programa de cadastro de veiculos. As caracteristicas dessa entidade, para
 * o ponto de vista desse programa, sao:
 * a) Placa
 * b) Modelo
 * c) Cor (M - metalica; F - fosca)
 * d) Ano de fabricacao
 */

/*
// DEFINICAO do modelo/registro / da estrutura (movida para registros.h)
// OBS.: Normalmente essa definicao fica a parte num arquivo-cabecalho
#define TAM_CAMPO_PLACA 8   // "ABC1234\0" - lembre-se do terminador-nulo!!!
#define TAM_CAMPO_MODELO 20
struct Carro {
    char placa[TAM_CAMPO_PLACA];
    char modelo[TAM_CAMPO_MODELO];
    char cor;   // 'M' ou 'F'
    int ano_fabricacao;
    // float potencia; // 1.0, 1.4, ...
};  // nao esquecer de terminar com ;
// Se eu nao quiser usar a palavra 'struct' toda vez que me referir a 'Carro',
// uso um typedef pra dar um apelido pra estrutura
typedef struct Carro carro; // poderia ser qualquer nome, inclusive "Carro"
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdio_ext.h>
#include "registros.h"

int main(void) {
    carro var;  // variavel do tipo Carro, com todos os atributos internos a serem preenchidos

    puts("Digite as informacoes do carro:");
    printf("Placa? ");
    __fpurge(stdin);
    gets(var.placa);    // indico o campo de interesse com um ponto (.) depois do nome
                        // da variavel em questao
    printf("Modelo? ");
    __fpurge(stdin);
    gets(var.modelo);

    char rascunho;
    do {
        printf("(M)etalico ou (F)osco? ");
        __fpurge(stdin);
        rascunho = toupper(getchar());
    } while (rascunho != 'M' && rascunho != 'F');
    var.cor = rascunho;

    printf("Ano de fabricacao? ");
    scanf("%d", &var.ano_fabricacao);

    printf("Seu carro faz %d anos no ano atual...\n", 2016 - var.ano_fabricacao);

    return EXIT_SUCCESS;
}
