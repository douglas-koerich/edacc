#include <string.h>
#include "ordenacao.h"

void mergesort(Registro* vetor, int inf, int sup) {
    if (inf >= sup) { // condicao terminal
        return; // nao ha o que dividir, retorna
    }
    // Fase ativa da recursividade
    int meio = (inf + sup) / 2;
    mergesort(vetor, inf, meio);
    mergesort(vetor, meio+1, sup);
    
    // Ao retornar das chamadas recursivas, efetua intercalacao entre as
    // metades (jah ordenadas internamente)
    size_t tamanho = sup - inf + 1;
    Registro* ordenado = malloc(sizeof(Registro) * tamanho);
    int o = 0; // indice de adicao no vetor ordenado
    int esq = inf, dir = meio+1;
    while (esq <= meio && dir <= sup) {
        if (vetor[esq].chave < vetor[dir].chave) {
            ordenado[o++] = vetor[esq++]; // 'dir' nao eh incrementado
        } else {
            ordenado[o++] = vetor[dir++]; // 'esq' nao eh incrementado
        }
    }
    while (esq <= meio) {
        ordenado[o++] = vetor[esq++];
    }
    while (dir <= sup) {
        ordenado[o++] = vetor[dir++];
    }
    // CUIDADO! Precisa lembrar que o segmento ordenado eh copiado a partir do 
    // indice 'inf'!
    memcpy(vetor + inf, ordenado, tamanho*sizeof(Registro));
    free(ordenado);
}

void quicksort(Registro* vetor, int inf, int sup) {

}
