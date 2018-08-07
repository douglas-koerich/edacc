#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include "registro.h"
#include "filar.h"

void imprime(R [*], size_t);
void bolha_crescente(R [*], size_t);
void selecao_decrescente(R [*], size_t);
void insercao_crescente(R [*], size_t);
void shell_decrescente(R [*], size_t);
void raiz_crescente(R [*], size_t);
void merge_decrescente(R [*], int, int);
void quick_crescente(R [*], int, int);

#define K  1024
#define M  K*K

int main(void) {
    FILE* tabela = fopen("/tmp/ordem.csv", "wt");
    if (tabela == NULL) {
        return EXIT_FAILURE;
    }
    fputs("Tamanho;Bolha;Selecao;Insercao;Shell;Raiz;Merge;Quick\n", tabela);
    int r, t, tamanho = 64;
    while (tamanho < 64 * M) {
        printf("\nTamanho = %d, gerando...", tamanho);
        fflush(stdout);
        // Para simular o pior caso, vamos preencher um vetor de
        // registros na ordem inversa do criterio desejado
        R* vetor = (R*) malloc(tamanho * sizeof(R));
        for (r = 0, t = tamanho; r < tamanho; ++r, --t) {
            vetor[r].chave = t;
            vetor[r].qualquer_coisa = ' ';
        }
        if (tamanho < 100) {
            printf("\nOriginal: "); imprime(vetor, tamanho);
            bolha_crescente(vetor, tamanho);
            printf("\nDepois do bolha: "); imprime(vetor, tamanho);
            selecao_decrescente(vetor, tamanho);
            printf("\nDepois do selecao: "); imprime(vetor, tamanho);
            insercao_crescente(vetor, tamanho);
            printf("\nDepois do insercao: "); imprime(vetor, tamanho);
            shell_decrescente(vetor, tamanho);
            printf("\nDepois do shell: "); imprime(vetor, tamanho);
            raiz_crescente(vetor, tamanho);
            printf("\nDepois do radix: "); imprime(vetor, tamanho);
            merge_decrescente(vetor, 0, tamanho-1);   // para o vetor inteiro
            printf("\nDepois do merge: "); imprime(vetor, tamanho);
            quick_crescente(vetor, 0, tamanho-1);
            printf("\nDepois do quick: "); imprime(vetor, tamanho);
        } else {
            clock_t antes;
            fprintf(tabela, "%d;", tamanho);
            if (tamanho > 64 * K) {
                fprintf(tabela, "-;-;-;-;");
            } else {
                printf(" bolha...");
                fflush(stdout);
                antes = clock();
                bolha_crescente(vetor, tamanho);
                fprintf(tabela, "%ld;", clock()-antes);
                printf(" selecao...");
                fflush(stdout);
                antes = clock();
                selecao_decrescente(vetor, tamanho);
                fprintf(tabela, "%ld;", clock()-antes);
                printf(" insercao...");
                fflush(stdout);
                antes = clock();
                insercao_crescente(vetor, tamanho);
                fprintf(tabela, "%ld;", clock()-antes);
                printf(" shell...");
                fflush(stdout);
                antes = clock();
                shell_decrescente(vetor, tamanho);
                fprintf(tabela, "%ld;", clock()-antes);
            }
            if (tamanho > 4 * M) {
                fprintf(tabela, "-;");
            } else {
                printf(" radix...");
                antes = clock();
                raiz_crescente(vetor, tamanho);
                fprintf(tabela, "%ld;", clock()-antes);
            }
            printf(" merge...");
            antes = clock();
            merge_decrescente(vetor, 0, tamanho-1);
            fprintf(tabela, "%ld;", clock()-antes);
            printf(" quick...");
            antes = clock();
            quick_crescente(vetor, 0, tamanho-1);
            fprintf(tabela, "%ld;", clock()-antes);
            printf(" feito!");
            fputc('\n', tabela);
        }
        free(vetor);
        tamanho *= 2;
    }
    putchar('\n');
    fclose(tabela);
    return EXIT_SUCCESS;
}

void imprime(R v[], size_t t) {
    int i;
    for (i = 0; i < t; ++i) {
        printf("%d ", v[i].chave);
    }
}

void bolha_crescente(R v[], size_t t) {
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

void selecao_decrescente(R v[], size_t t) {
    int i;
    for (i=0; i<t; ++i) {
        int chave_maior = v[i].chave;
        int indice_maior = i;
        int j;
        for (j=i+1; j<t; ++j) {
            if (v[j].chave > chave_maior) {
                chave_maior = v[j].chave;
                indice_maior = j;
            }
        }
        troca(v[i], v[indice_maior]);
    }
}

void insercao_crescente(R v[], size_t t) {
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

#define MAX_SERIE   50

void shell_decrescente(R v[], size_t t) {
    // Cria a serie de incrementos
    int serie_incrementos[MAX_SERIE];
    int h = 1, indice = 0;
    while (h < t) {
        if (indice == MAX_SERIE) {
            puts("Vetor de incrementos esgotado pelo tamanho do problema");
            return;
        }
        serie_incrementos[indice] = h;
        h = 3 * h + 1;
        if (h < t) {    // vou contar com esse novo incremento?
            ++indice;
        }
    }
    // Primeiro incremento estarah 2 posicoes atras do ultimo efetivamente
    // armazenado
    indice -= 2;
    while (indice >= 0) {
        h = serie_incrementos[indice]; // leh da serie o incremento da vez

        // Repete o mesmo algoritmo de ordenacao (neste caso, vamos escolher
        // selecao direta) para cada segmento/"sub-vetor" dividido pelo incremento
        int seg;
        for (seg = 0; seg < h; ++seg) { // para cada segmento...
            // Ordenacao desse segmento por selecao direta (algoritmo escolhido)
            int i;
            for (i=seg; // inicia com o primeiro indice do segmento da vez
                 i<t;   // ate o fim do vetor...
                 i+=h) {// ... "pulando" os elementos dos outros segmentos
                int chave_maior = v[i].chave;
                int indice_maior = i;
                int j;
                for (j=i+h; // primeiro a comparar dentro do mesmo segmento estah h posicoes a frente
                     j<t;
                     j+=h) { // para continuar comparando com os demais do mesmo segmento, "pula"...
                    if (v[j].chave > chave_maior) {
                        chave_maior = v[j].chave;
                        indice_maior = j;
                    }
                }
                troca(v[i], v[indice_maior]);
            }
        }
        --indice;   // vai para o incremento anterior
    }
}

#define NUM_FILAS   10

void raiz_crescente(R v[], size_t t) {
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

void merge_decrescente(R v[], int inf, int sup) {
    if (inf >= sup) {
        return;
    }
    int meio = (inf + sup) / 2; // media aritmetica dos indices-extremos
    merge_decrescente(v, inf, meio);
    merge_decrescente(v, meio+1, sup);

    // Intercala os elementos oriundos de cada metade recebida jah ordenada internamente
    int i = inf, s = meio+1;
    size_t tamanho = sup - inf + 1;
    R* aux = (R*) malloc(tamanho*sizeof(R));
    int a = 0;
    while (i<=meio && s<=sup) {
        if (v[i].chave > v[s].chave) {  // comparacao para ordenacao decrescente
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

void quick_crescente(R v[], int inf, int sup) {
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
    quick_crescente(v, inf, dir);  // parte "de baixo" do vetor
    quick_crescente(v, esq, sup);  // parte "de cima"
}
