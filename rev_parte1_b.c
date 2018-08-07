#include <stdlib.h>
#include <stdio.h>
#include <stdio_ext.h> // __fpurge (apenas em Linux)
#include <string.h>
#include <stdbool.h>
#include "rev_parte1.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero de parametros insuficiente");
        return EXIT_FAILURE;
    }
    char nome_arquivo[16];
    strcpy(nome_arquivo, argv[1]);
    strcat(nome_arquivo, ".bin");
    FILE* arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL) {
        perror("Erro na criacao do arquivo");
        return EXIT_FAILURE;
    }
    // struct pais um_pais_qualquer;
    Pais um_pais_qualquer;
    bool fim;
    do {
        puts("Cadastro de novo pais:");
        printf("Nome? ");
        __fpurge(stdin);    // limpa o buffer antes de nova entrada
        gets(um_pais_qualquer.nome);
        fim = strcmp(um_pais_qualquer.nome, "NONONONO") == 0;
        if (fim == false) {
            printf("Numero de trabalhadores ativos? ");
            scanf("%d", &um_pais_qualquer.ativos);
            printf("Numero de acidentes? ");
            scanf("%d", &um_pais_qualquer.acidentes);
            printf("Percentual de afastamentos (%%)? ");
            scanf("%f", &um_pais_qualquer.perc_afastamento);

            if (fwrite(&um_pais_qualquer, sizeof(Pais), 1, arquivo) < 1) {
                perror("Erro ao gravar no arquivo");
                fclose(arquivo);
                return EXIT_FAILURE;
            }
        }
    } while (!fim); // while (fim == false);
    fclose(arquivo);
    return EXIT_SUCCESS;
}

