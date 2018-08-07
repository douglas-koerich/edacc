#include <stdlib.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <ctype.h>
#include "registros.h"

int ano_mais_antigo(carro [*], size_t);

int main(void) {
    int numero_carros;
    printf("Digite o numero de carros a serem cadastrados: ");
    scanf("%d", &numero_carros);

    // Declaracao de um vetor com tamanho definido pelo usuario
    carro frota[numero_carros]; // cada posicao desse vetor tem o conjunto completo de atributos

    // Para preencher os dados da frota, vou percorrer o vetor com um LACO e
    // editar cada campo de cada carro/elemento do vetor individualmente
    int ind;
    for (ind = 0; ind < numero_carros; ++ind) {
        printf("Digite os dados do proximo carro da frota (posicao %d):\n", ind);
        printf("Placa? ");
        __fpurge(stdin);
        gets(frota[ind].placa);
        printf("Modelo? ");
        __fpurge(stdin);
        gets(frota[ind].modelo);

        char rascunho;
        do {
            printf("(M)etalico ou (F)osco? ");
            __fpurge(stdin);
            rascunho = toupper(getchar());
        } while (rascunho != 'M' && rascunho != 'F');
        frota[ind].cor = rascunho;

        printf("Ano de fabricacao? ");
        scanf("%d", &frota[ind].ano_fabricacao);
    }
    int mais_antigo = ano_mais_antigo(frota, numero_carros);    // de novo, passa soh o nome do vetor
    printf("O carro mais antigo foi fabricado em %d\n", mais_antigo);

    return EXIT_SUCCESS;
}

int ano_mais_antigo(carro vetor[], size_t tamanho) {
    int mais_antigo = vetor[0].ano_fabricacao; // de novo, inicializo como o mais antigo o primeiro
    int i;
    for (i = 0; i < tamanho; ++i) {
        if (vetor[i].ano_fabricacao < mais_antigo) {
            mais_antigo = vetor[i].ano_fabricacao;
        }
    }
    return mais_antigo;
}
