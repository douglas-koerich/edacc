#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

unsigned comparacoes;

int sequencial(int* v, size_t n, int x) {
    int i;
    for (i = 0; i < n; ++i) {
        ++comparacoes;
        if (v[i] == x) {
            return i;
        }
    }
    return -1;
}

int binaria(int* v, int i, int s, int x) {
    if (i > s) {
        return -1;
    }
    int m = (i + s) / 2;
    ++comparacoes;
    if (v[m] == x) {
        return m;
    }
    if (x < v[m]) {
        return binaria(v, i, m-1, x);
    } else {
        return binaria(v, m+1, s, x);
    }
}

int interpolacao(int* v, int i, int s, int x) {
    if (i > s) {
        return -1;
    }
    float dv_total = v[s] - v[i],
          di_total = s - i,
          dv_chave = x - v[i];

    int y;
    if (dv_total != 0.0) {
        y = dv_chave * di_total / dv_total + i;
        if (y > s) {
            y = s;
        }
    } else {
        y = i;
    }
    
    ++comparacoes;
    if (v[y] == x) {
        return y;
    }
    if (x < v[y]) {
        return interpolacao(v, i, y-1, x);
    } else {
        return interpolacao(v, y+1, s, x);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero invalido de parametros");
        printf("Uso: %s <tamanho-do-vetor>\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t tamanho = atoi(argv[1]);
    int vetor[tamanho], i;
    for (i = 0; i < tamanho; ++i) {
        vetor[i] = i;
        printf("%d ", i);
    }
    putchar('\n');

    comparacoes = 0;
    assert(sequencial(vetor, tamanho, tamanho) == -1);
    printf("O numero de comparacoes com a busca sequencial foi %u\n", comparacoes);

    comparacoes = 0;
    assert(binaria(vetor, 0, tamanho-1, tamanho) == -1);
    printf("O numero de comparacoes com a busca binaria foi %u\n", comparacoes);

    comparacoes = 0;
    assert(interpolacao(vetor, 0, tamanho-1, tamanho) == -1);
    printf("O numero de comparacoes com a busca interpolacao foi %u\n", comparacoes);

    return EXIT_SUCCESS;
}

