#include <stdlib.h>
#include <stdio.h>
#include "registro.h"
#include "ordenacao.h"

void imprime(Registro* v, size_t n) {
    int i = 0;
    while (i < n) {
        printf("<%d,%c> ", (v+i)->chave, (v+i)->valor);
        // printf("<%d,%c> ", v[i].chave, v[i].valor);
        ++i;
    }
    putchar('\n');
}

void algoritmo_ordenacao(Registro* v, size_t n) {
    // Algoritmos complexos
    // bubble(v, n);
    // selection(v, n);
    // insertion(v, n);

    // Algoritmos melhorados ou especificos
    // shellsort(v, n);
    // radixsort(v, n);

    // Algoritmos eficientes
    mergesort(v, 0, n-1);
    // quicksort(v, 0, n-1);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de parametros");
        printf("Uso: %s <numero-de-registros>\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t tamanho_vetor = atoi(argv[1]);
    Registro* vetor = malloc(tamanho_vetor * sizeof(Registro));

    srand(20210609);
    int i;
    for (i = 0; i < tamanho_vetor; ++i) {
        vetor[i].chave = rand() % 9999 + 1; // faixa de 1 a 9999
        vetor[i].valor = rand() % 26 + 'A'; // faixa de 'A' a 'Z'
    }
    puts("ANTES:");
    imprime(vetor, tamanho_vetor);

    algoritmo_ordenacao(vetor, tamanho_vetor);

    puts("DEPOIS:");
    imprime(vetor, tamanho_vetor);

    free(vetor);

    return EXIT_SUCCESS;
}