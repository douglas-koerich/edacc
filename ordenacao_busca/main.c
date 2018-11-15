#include <stdlib.h>
#include <stdio.h>
#include "registro.h"
#include "ordenacao.h"
#include "busca.h"

int main(int argc, char* argv[]) {
    printf("Quantos registros deseja gerar? ");
    size_t n;
    scanf("%zd", &n);

    Registro banco_de_dados[n];
    int i;
    puts(">>> Antes da ordenacao:");
    for (i=0; i<n; ++i) {
        preenche_registro_aleatorio(banco_de_dados + i); // (&banco_de_dados[i])
        imprime_registro(banco_de_dados + i);
    }
    quicksort(banco_de_dados, 0, n-1);
    puts("<<< Depois da ordenacao:");
    for (i=0; i<n; ++i) {
        imprime_registro(banco_de_dados + i);
    }
    unsigned x;
    printf("Digite uma chave para procurar nesse conjunto: ");
    scanf("%u", &x);
    comparacoes = 0;
    //int indice = sequencial(banco_de_dados, n, x);
    //int indice = binaria(banco_de_dados, 0, n-1, x);
    int indice = interpolacao(banco_de_dados, 0, n-1, x);
    if (indice == -1) {
        printf("Chave nao encontrada apos %u comparacoes!\n", comparacoes);
    } else {
        printf("Chave encontrada em %d apos %u comparacoes, registro: ", indice, comparacoes);
        imprime_registro(banco_de_dados + indice);
    }
    return EXIT_SUCCESS;
}

