#ifdef DEBUG
#include <stdio.h>
#endif
#include "registro.h"
#include "alg_busca.h"

static void imprime_intervalo(const Reg vetor[], int inferior, int superior) {
#ifdef DEBUG
    printf("Buscando desde a posicao %d (%u) ateh %d (%u)\n",
           inferior, vetor[inferior], superior, vetor[superior]);
#endif
}

int binaria(const Reg vetor[], int inf, int sup, unsigned chave) {
    if (inf > sup) {
        // Neste ponto das chamadas recursivas o segmento do vetor
        // a ser consultado tornou-se nulo (dividido ateh nao existir)
        return -1; // nao encontrou a chave
    }
    imprime_intervalo(vetor, inf, sup);
    int meio = (inf + sup) / 2;
    if (vetor[meio].chave == chave) {
        return meio; // localizada no meio do segmento de vetor que foi
                     // delimitado entre inf e sup pelas chamadas recursivas
    }
    if (chave < vetor[meio].chave) {
        // Continua busca de forma recursiva pela metade inferior
        return binaria(vetor, inf, meio-1, chave); // nao inclui 'meio'
    } else {
        return binaria(vetor, meio+1, sup, chave);
    }
}

