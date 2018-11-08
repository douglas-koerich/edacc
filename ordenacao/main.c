#include <stdlib.h>
#include <stdio.h>
#include "registro.h"
#include "ordenacao.h"

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
    return EXIT_SUCCESS;
}

