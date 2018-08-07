#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "registro.h"

void imprime(R [*], size_t);
void troca(R*, R*);
void bolha(R [*], size_t);
int binaria(R [*], int, int, int);
unsigned conta(R [*], int, int, int);

#define TAMANHO 20

int main() {
    srand((unsigned) time(0));
    R banco_dados[TAMANHO];
    int i;
    for (i=0; i<TAMANHO; ++i) {
        banco_dados[i].chave = rand() % 10;
        banco_dados[i].outro = 'A' + i;
    }
    bolha(banco_dados, TAMANHO);
    imprime(banco_dados, TAMANHO);

    printf("Digite a chave para busca: ");
    int ch;
    scanf("%d", &ch);

    int ind = binaria(banco_dados, 0, TAMANHO-1, ch);
    if (ind == -1) {
        puts("Chave nao encontrada");
    }
    else {
        printf("Chave encontrada no indice %d\n", ind);
    }

    unsigned n = conta(banco_dados, 0, TAMANHO-1, ch);
    printf("Chave encontrada %u vezes\n", n);

    return 0;
}

void imprime(R v[], size_t t) {
    int i;
    for (i=0; i<t; ++i) {
        printf("%d ", v[i].chave);
    }
    putchar('\n');
}

void troca(R* r1, R* r2) {
    R temp;
    memcpy(&temp, r1, sizeof(R));
    memcpy(r1, r2, sizeof(R));
    memcpy(r2, &temp, sizeof(R));
}

void bolha(R v[], size_t t) {
    int i;
    for (i=1; i<=t; ++i) {
        int j;
        for (j=t-1; j>0; --j) {
            if (v[j].chave < v[j-1].chave) { 
                troca(&v[j], &v[j-1]);
            }
        }
    }
}

int binaria(R v[], int i, int s, int x) {
    if (i > s) {
        return -1;
    }
    int m = (i+s)/2;
    if (v[m].chave == x) {
        return m;
    }
    return (v[m].chave > x)? binaria(v, i, m-1, x): binaria(v, m+1, s, x);
}

unsigned conta(R v[], int i, int s, int x) {
    if (i > s) {
        return 0;
    }
    int m = (i+s)/2;
    /*
    // Alternativa 1 (preferida)
    unsigned contador = (v[m].chave == x)? 1: 0;
    contador += conta(v, i, m-1, x);
    contador += conta(v, m+1, s, x);
    */
    // Alternativa 2
    if (v[m].chave == x) {
        unsigned contador = 1;
        // Como o vetor estah ordenado, entao a contagem pode continuar
        // pelos adjacentes ah esquerda e ah direita dessa posicao
        int j = m-1;
        while (j >= i && v[j].chave == x) {
            ++contador, --j;
        }
        j = m+1;
        while (j <= s && v[j].chave == x) {
            ++contador, ++j;
        }
        return contador;
    }
    return (v[m].chave > x)? conta(v, i, m-1, x): conta(v, m+1, s, x);
}

