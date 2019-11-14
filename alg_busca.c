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
        return binaria(vetor, meio+1, sup, chave); // na metade superior...
    }
}

int interpolacao(const Reg vetor[], int inf, int sup, unsigned chave) {
    if (inf > sup) {
        return -1; // nao encontrou a chave
    }
    imprime_intervalo(vetor, inf, sup);

    // Calcula diferenca ("distancia") entre o indice superior e o inferior
    float dif_ind_total = sup - inf;

    // Calcula diferenca ("distancia") entre as chaves nesses indices limitrofes
    float dif_chv_total = vetor[sup].chave - vetor[inf].chave;

    // Outra diferenca ("distancia") conhecida eh aquela entre a chave da
    // posicao inferior e a chave que se busca
    float dif_chv_parcial = chave - vetor[inf].chave;

    // A diferenca que se quer encontrar eh aquela entre a posicao "provavel" e
    // a posicao inferior, que deve ser tao proporcional a 'dif_chv_parcial'
    // quanto 'dif_ind_total' eh proporcional a 'dif_chv_total'
    // (conceitos de "razao" e "proporcao": aplicacao de regra-de-tres simples)
    float dif_ind_parcial = dif_chv_total > 0?
                            (dif_ind_total * dif_chv_parcial) / dif_chv_total: 
                            0.0;

    int provavel = inf + dif_ind_parcial;
    if (vetor[provavel].chave == chave) {
        return provavel;
    }
    if (chave < vetor[provavel].chave) {
        return interpolacao(vetor, inf, provavel-1, chave);
    } else {
        return interpolacao(vetor, provavel+1, sup, chave);
    }
}
