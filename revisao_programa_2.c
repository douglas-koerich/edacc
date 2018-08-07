#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "revisao.h"

int main(void) {
    char nome_arquivo[16];
    printf("Digite o nome do arquivo: ");
    gets(nome_arquivo);

    FILE* arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return EXIT_FAILURE;
    }
    fseek(arquivo, 0, SEEK_END);    // vou pro fim do arquivo
    int tamanho = ftell(arquivo);   // numero da posicao em que estou
    fseek(arquivo, 0, SEEK_SET);    // volta ao inicio para comecar as leituras

    int num_paises_gravados = tamanho / sizeof(Pais);
    Pais lista_paises[num_paises_gravados];

    if (fread(lista_paises, sizeof(Pais), num_paises_gravados, arquivo) < num_paises_gravados) {
       if (ferror(arquivo)) {
          perror("Erro ao ler o conteudo do arquivo");
          fclose(arquivo);
          return EXIT_FAILURE;
       }
    }
    fclose(arquivo);

    char melhor_pais[TAM_NOME_PAIS], pior_pais[TAM_NOME_PAIS];
    int melhor_indice, pior_indice;

    melhor_pior_pais(lista_paises, num_paises_gravados, melhor_pais, pior_pais,
                     &melhor_indice, &pior_indice);
    printf("Melhor pais em acidentes: %s, com %d acidentes\n", melhor_pais, melhor_indice);
    printf("Pior pais em acidentes: %s, com %d acidentes\n", pior_pais, pior_indice);

    float* novo_vetor = devolve_vetor(lista_paises, num_paises_gravados);
    int i;
    for (i=0; i<num_paises_gravados; ++i) {
        printf("Percentual de afastados em relacao aos ativos do pais %s: %.2f%%\n",
               lista_paises[i].nome, novo_vetor[i]);
    }
    free(novo_vetor);

    return EXIT_SUCCESS;
}

void melhor_pior_pais(Pais lista[], int num_paises, char nome_melhor[], char* nome_pior,
                      int* num_acid_melhor, int* num_acid_pior) {
    int i = 0;
    int posicao_melhor = -1, posicao_pior = -1;
    while (i < num_paises) {
        if (i == 0) {
            posicao_melhor = posicao_pior = 0;
        } else {
            if (lista[i].acidentes > lista[posicao_pior].acidentes) {
                posicao_pior = i;
            }
            if (lista[i].acidentes < lista[posicao_melhor].acidentes) {
                posicao_melhor = i;
            }
        }
        ++i;
    }
    strcpy(nome_melhor, lista[posicao_melhor].nome);
    *num_acid_melhor = lista[posicao_melhor].acidentes;
    strcpy(nome_pior, lista[posicao_pior].nome);
    *num_acid_pior = lista[posicao_pior].acidentes;
}

float* devolve_vetor(const Pais* lista, int num_paises) {
    float* novo = malloc(num_paises * sizeof(float)); // espaco para N floats
    int i = 0;
    while (i < num_paises) {
        int afastados = lista->perc_afastamento * lista->acidentes / 100.0;
        // novo[i] = afastados * 100.0 / lista->ativos;
        *(novo + i) = afastados * 100.0 / lista->ativos;
        ++i, ++lista;
    }
    return novo;
}

