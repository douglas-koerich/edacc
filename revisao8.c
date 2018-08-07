#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "revisao8.h"

#define NUM_ESTADOS 5

int main() {
    // Declaracao de um vetor de Estados
    Estado lista_ufs[NUM_ESTADOS];

    // Variaveis auxiliares da estatistica:
    unsigned menor_num_acidentes, maior_num_acidentes;
    char estado_menos_acidentes[TAM_SIGLA+1], estado_mais_acidentes[TAM_SIGLA+1];

    float perc_veic_por_estado[NUM_ESTADOS];    // quantos veiculos cada estado tem proporcionalmente ao total geral

    float media_acidentes_do_estado[NUM_ESTADOS];   // percentual dos veiculos que se acidentaram em relacao ao total de veiculos

    // Preenche os dados estatisticos
    int uf;
    unsigned total_geral = 0;
    for (uf = 0; uf < NUM_ESTADOS; ++uf) {
        // Declaracao de um registro isolado para rascunho
        Estado rascunho;

        printf("Digite a sigla do estado da federacao: ");
        scanf(" %s", rascunho.sigla);
        printf("Quantos veiculos o estado possui? ");
        scanf("%u", &rascunho.veiculos);
        printf("Informe o numero de acidentes ocorridos: ");
        scanf("%u", &rascunho.acidentes);

        if (uf == 0) {
            menor_num_acidentes = maior_num_acidentes = rascunho.acidentes;
            strcpy(estado_menos_acidentes, rascunho.sigla);
            strcpy(estado_mais_acidentes, rascunho.sigla);
        } else {
            if (rascunho.acidentes > maior_num_acidentes) {
                maior_num_acidentes = rascunho.acidentes;
                strcpy(estado_mais_acidentes, rascunho.sigla);
            }
            if (rascunho.acidentes < menor_num_acidentes) {
                menor_num_acidentes = rascunho.acidentes;
                strcpy(estado_menos_acidentes, rascunho.sigla);
            }
        }

        total_geral += rascunho.veiculos;

        media_acidentes_do_estado[uf] = rascunho.acidentes * 100.0 / rascunho.veiculos;

        // Copia do rascunho direto pra um elemento/estado da lista
        lista_ufs[uf] = rascunho;
    }

    for (uf = 0; uf < NUM_ESTADOS; ++uf) {
        perc_veic_por_estado[uf] = lista_ufs[uf].veiculos * 100.0 / total_geral;
    }

    puts("Tabela de estados:\nUF VEIC ACID PERC_V MED_AC");
    for (uf = 0; uf < NUM_ESTADOS; ++uf) {
        printf("%s %4u %4u %4.0f%% %4.0f%%\n", lista_ufs[uf].sigla, lista_ufs[uf].veiculos,
               lista_ufs[uf].acidentes, perc_veic_por_estado[uf],
               media_acidentes_do_estado[uf]);
    }
    printf("\nEstado com MAIS acidentes: %s (%u).\n", estado_mais_acidentes, maior_num_acidentes);
    printf("Estado com MENOS acidentes: %s (%u).\n", estado_menos_acidentes, menor_num_acidentes);

    return EXIT_SUCCESS;
}
