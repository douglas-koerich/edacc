#include <stdlib.h>
#include <stdio.h>
#include <string.h> // memcpy
#include <time.h>   // clock
#include "registro.h"

void imprime(R [*], size_t);
void troca(R*, R*);
void bolha(R [*], size_t);
void coquetel(R [*], size_t);

int main() {
    FILE* tabela = fopen("/tmp/tabela.txt", "w");
    if (tabela == NULL) {
        perror("Erro ao criar o arquivo de tabela");
        return -1;
    }
    fputs("Tamanho;Bolha;Coqueteleira\n", tabela);
    int tamanho;
    for (tamanho=16; tamanho<=8*1024; tamanho*=2) {
        fprintf(tabela, "%d;", tamanho);
        clock_t antes, depois;
        R* banco_dados = (R*) malloc(sizeof(R)*tamanho);
        R* backup = (R*) malloc(sizeof(R)*tamanho);
        int i, x;
        for (i=0, x=tamanho-1; i<tamanho; ++i, --x) {
            banco_dados[i].chave = x;
        }
        memcpy(backup, banco_dados, sizeof(R)*tamanho);
        if (tamanho < 50) {
            // Imprime antes da ordenacao
            puts(">>>>>>>>>>>>>>>>>>>>>>>");
            imprime(banco_dados, tamanho);
        }
        // Executa o algoritmo de ordenacao
        printf("Ordenando %d elementos por bolha... ", tamanho); fflush(stdout);
        antes = clock();
        bolha(banco_dados, tamanho);
        depois = clock();
        fprintf(tabela, "%lld;", (long long) (depois-antes));
        puts("Feito!");
        if (tamanho < 50) {
            // Imprime o banco de dados ordenado
            imprime(banco_dados, tamanho);
            puts("<<<<<<<<<<<<<<<<<<<<<<<");
        }
        memcpy(banco_dados, backup, sizeof(R)*tamanho);
        if (tamanho < 50) {
            // Imprime antes da ordenacao
            puts(">>>>>>>>>>>>>>>>>>>>>>>");
            imprime(banco_dados, tamanho);
        }
        // Executa o algoritmo de ordenacao
        printf("Ordenando %d elementos por coqueteleira... ", tamanho); fflush(stdout);
        antes = clock();
        coquetel(banco_dados, tamanho);
        depois = clock();
        fprintf(tabela, "%lld\n", (long long) (depois-antes));
        puts("Feito!");
        if (tamanho < 50) {
            // Imprime o banco de dados ordenado
            imprime(banco_dados, tamanho);
            puts("<<<<<<<<<<<<<<<<<<<<<<<");
        }
        free(backup);
        free(banco_dados);
        fflush(tabela);
    }
    fclose(tabela);
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

void coquetel(R v[], size_t t) {
    int i;
    for (i=1; i<=t; ++i) {
        int j;
        if (i % 2) {
            for (j=t-1; j>0; --j) {
                if (v[j].chave < v[j-1].chave) {
                    troca(&v[j], &v[j-1]);
                }
            }
        }
        else {
            for (j=0; j<t-1; ++j) {
                if (v[j].chave > v[j+1].chave) {
                    troca(&v[j], &v[j+1]);
                }
            }
        }
    }
}

