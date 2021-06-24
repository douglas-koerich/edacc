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
    if (inf >= sup) { // condicao terminal
        return; // nao ha mais o que ordenar
    }
    // Como a chave de ordenacao eh um 'int', esse eh o tipo da
    // variavel 'pivo' que vai armazerar o valor de referencia
    int pivo;
    pivo = vetor[(inf + sup)/2].chave; // chave do elemento central do segmento

    // Indices de percurso no segmento
    int esq = inf, dir = sup;

    // Enquanto indices nao se cruzarem...
    while (esq <= dir) {
        // ... busca pela esquerda um elemento fora de ordem, e...
        while (vetor[esq].chave < pivo) {
            ++esq;
        }
        // ... faz o mesmo pela direita
        while (vetor[dir].chave > pivo) {
            --dir;
        }
        // Se indices ainda nao se cruzaram...
        if (esq <= dir) {
            // ... troca os elementos entre si
            TROCA(vetor[esq], vetor[dir]);
            ++esq, --dir;
        }
    }
    quicksort(vetor, inf, dir); // continua pelo segmento dos menores
    quicksort(vetor, esq, sup); // faz o mesmo para o segmento dos maiores
}
