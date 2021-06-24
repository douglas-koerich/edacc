#include <stdlib.h>
#include <stdio.h>
#include "registro.h"
#include "ordenacao.h"
#include "busca.h"

extern unsigned insucessos;

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
    quicksort(v, 0, n-1);
}

int algoritmo_busca(const Registro* v, size_t n, int x) {
    // return sequencial(v, n, x);
    // return binaria(v, 0, n-1, x);
    return interpolacao(v, 0, n-1, x);
    // return espalhamento(v, n, x);
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
        vetor[i].chave = rand() % 99 + 1; // faixa de 1 a 9999
        vetor[i].valor = rand() % 26 + 'A'; // faixa de 'A' a 'Z'
    }
    puts("ANTES:");
    imprime(vetor, tamanho_vetor);

    // Para alguns algoritmos mais eficientes que o sequencial, eh necessario
    // ordenar o vetor pelo campo a ser usado na busca (no caso, a chave)
    algoritmo_ordenacao(vetor, tamanho_vetor);

    puts("DEPOIS:");
    imprime(vetor, tamanho_vetor);

    printf("Digite uma chave para buscar no conjunto de elementos: ");
    int chave;
    scanf("%d", &chave);

    int indice = algoritmo_busca(vetor, tamanho_vetor, chave);
    if (indice < 0) {
        puts("Chave nao encontrada no conjunto de dados");
        printf("Numero de insucessos = %d\n", insucessos);
    } else {
        printf("Chave encontrada no indice %d\n", indice);
    }

    free(vetor);

    return EXIT_SUCCESS;
}