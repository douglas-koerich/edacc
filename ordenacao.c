#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include "registro.h"
#include "filar.h"

void preenche(R [*], size_t);
void bolha(R [*], size_t);
void selecao(R [*], size_t);
void insercao(R [*], size_t);
void raiz(R [*], size_t);
void merge(R [*], int, int);
void quick(R [*], int, int);

#define K  1024
#define M  K*K

int main(void) {
    FILE* tabela = fopen("/tmp/ordem.csv", "wt");
    if (tabela == NULL) {
        return EXIT_FAILURE;
    }
    fputs("Tamanho;Bolha;Selecao;Insercao;Raiz;Merge;Quick\n", tabela);
    int r, t, tamanho = 512;
    while (tamanho < 64 * M) {
        printf("Tamanho = %8d:", tamanho);
        fflush(stdout);
        R* vetor = (R*) malloc(tamanho * sizeof(R));
        clock_t antes;
        fprintf(tabela, "%d;", tamanho);
        if (tamanho > 64 * K) {
            fprintf(tabela, "-;-;-;");
        } else {
            printf(" bolha...");
            fflush(stdout);
            preenche(vetor, tamanho);
            antes = clock();
            bolha(vetor, tamanho);
            fprintf(tabela, "%ld;", clock()-antes);
            printf(" selecao...");
            fflush(stdout);
            preenche(vetor, tamanho);
            antes = clock();
            selecao(vetor, tamanho);
            fprintf(tabela, "%ld;", clock()-antes);
            printf(" insercao...");
            fflush(stdout);
            preenche(vetor, tamanho);
            antes = clock();
            insercao(vetor, tamanho);
            fprintf(tabela, "%ld;", clock()-antes);
        }
        if (tamanho > 4 * M) {
            fprintf(tabela, "-;");
        } else {
            printf(" radix...");
            preenche(vetor, tamanho);
            antes = clock();
            raiz(vetor, tamanho);
            fprintf(tabela, "%ld;", clock()-antes);
        }
        printf(" merge...");
        preenche(vetor, tamanho);
        antes = clock();
        merge(vetor, 0, tamanho-1);
        fprintf(tabela, "%ld;", clock()-antes);
        printf(" quick...");
        preenche(vetor, tamanho);
        antes = clock();
        quick(vetor, 0, tamanho-1);
        fprintf(tabela, "%ld;", clock()-antes);
        putchar('\n');
        fputc('\n', tabela);
        free(vetor);
        tamanho *= 2;
    }
    putchar('\n');
    fclose(tabela);
    return EXIT_SUCCESS;
}

void preenche(R v[], size_t t) {
    int i, j;
    // Para simular o pior caso, vamos preencher um vetor de
    // registros na ordem inversa do criterio desejado
    for (i = 0, j = t; i < t; ++i, --j) {
        v[i].chave = j;
        v[i].qualquer_coisa = ' ';
    }
}

void bolha(R v[], size_t t) {
    // Sao necessarias 't' (tamanho) varreduras para garantir
    // que todos os valores tenham sido reposicionados
    int i = 1;
    while (i <= t) {
        int j = t - 1;  // comeca a comparacao pelo ultimo elemento
        while (j > 0) {
            if (v[j].chave < v[j-1].chave) {
                troca(v[j], v[j-1]);
            }
            --j;
        }
        ++i;
    }
}

void selecao(R v[], size_t t) {
    int i;
    for (i=0; i<t; ++i) {
        int chave_menor = v[i].chave;
        int indice_menor = i;
        int j;
        for (j=i+1; j<t; ++j) {
            if (v[j].chave < chave_menor) {
                chave_menor = v[j].chave;
                indice_menor = j;
            }
        }
        troca(v[i], v[indice_menor]);
    }
}

void insercao(R v[], size_t t) {
    int fronteira = 1;
    while (fronteira < t) {
        R auxiliar;
        memcpy(&auxiliar, &v[fronteira], sizeof(R));
        int o = fronteira - 1;  // ultimo elemento do segmento ordenado
        while (o >= 0 && v[o].chave > auxiliar.chave) {
            memcpy(&v[o+1], &v[o], sizeof(R));
            --o;
        }
        memcpy(&v[o+1], &auxiliar, sizeof(R));
        ++fronteira;
    }
}

#define NUM_FILAS   10

void raiz(R v[], size_t t) {
    Fila* fila[NUM_FILAS];
    int i;
    for (i=0; i<NUM_FILAS; ++i) {
        fila[i] = cria();
    }
    const int NUM_DIGITOS_MAIOR = log10(INT_MAX) + 1;
    int d;
    for (d=0; d<NUM_DIGITOS_MAIOR; ++d) {
        for (i=0; i<t; ++i) {
            int digito = (int)(v[i].chave / pow(10, d)) % 10;
            enqueue(fila[digito], v[i]);
        }
        int f;
        for (i=f=0; f<NUM_FILAS; ++f) {
            while (!underflow(fila[f])) {
                v[i++] = dequeue(fila[f]);
            }
        }
    }
    for (i=0; i<NUM_FILAS; ++i) {
        destroi(fila[i]);
    }
}

void merge(R v[], int inf, int sup) {
    if (inf >= sup) {
        return;
    }
    int meio = (inf + sup) / 2; // media aritmetica dos indices-extremos
    merge(v, inf, meio);
    merge(v, meio+1, sup);

    // Intercala os elementos oriundos de cada metade recebida jah ordenada internamente
    int i = inf, s = meio+1;
    size_t tamanho = sup - inf + 1;
    R* aux = (R*) malloc(tamanho*sizeof(R));
    int a = 0;
    while (i<=meio && s<=sup) {
        if (v[i].chave < v[s].chave) {
            aux[a] = v[i];
            ++i;
        } else {
            aux[a] = v[s];
            ++s;
        }
        ++a;
    }
    while (i<=meio) {
        aux[a++] = v[i++];
    }
    while (s<=sup) {
        aux[a++] = v[s++];
    }
    memcpy(&v[inf], aux, tamanho*sizeof(R));
    free(aux);
}

void quick(R v[], int inf, int sup) {
    if (inf >= sup) {
        return;
    }
    int pivo = v[(inf+sup)/2].chave;
    int esq = inf, dir = sup;
    while (esq <= dir) {
        while (v[esq].chave < pivo) ++esq;
        while (v[dir].chave > pivo) --dir;
        if (esq <= dir) {
            troca(v[esq], v[dir]);
            ++esq, --dir;
        }
    }
    quick(v, inf, dir);  // parte "de baixo" do vetor
    quick(v, esq, sup);  // parte "de cima"
}
