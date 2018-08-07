#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "filai.h"

#define SEMENTE 128

//void ordena(int [*], size_t);
void ordena(int [*], int, int);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de parametros");
        printf("Use: %s <tamanho>\n", argv[0]);
        return EXIT_FAILURE;
    }
    srand(SEMENTE);
    size_t tamanho = atoi(argv[1]);
    int* vetor = (int*) malloc(sizeof(int)*tamanho);
    int i;
    for (i=0; i<tamanho; ++i) {
        vetor[i] = rand() % (128*1024);
    }
    if (tamanho < 20) {
        printf("Antes: ");
        for (i=0; i<tamanho; ++i) {
            printf("%d ", vetor[i]);
        }
        putchar('\n');
    }
    // ordena(vetor, tamanho);
    ordena(vetor, 0, tamanho-1);
    if (tamanho < 20) {
        printf("Depois: ");
        for (i=0; i<tamanho; ++i) {
            printf("%d ", vetor[i]);
        }
        putchar('\n');
    }
    free(vetor);
    return EXIT_SUCCESS;
}

/*
// Versao BOLHA da ordenacao
void ordena(int v[], size_t n) {
    // Para um vetor totalmente invertido, o algoritmo precisa de
    // n passagens/varreduras para reordenar
    int j;
    for (j=1; j<=n; ++j) {
        // Uma passagem/varredura no vetor...
        int i = n-1;
        while (i > 0) {
            if (v[i] < v[i-1]) {
                int aux = v[i];
                v[i] = v[i-1];
                v[i-1] = aux;
            }
            --i;
        }
    }
}
*/

/*
// Versao SELECAO da ordenacao
void ordena(int v[], size_t n) {
    int i;
    // Marca a cada passo do laco o inicio do segmento no qual
    // vai fazer a busca pelo menor
    for (i=0; i<n; ++i) {
        int ind_menor = i, val_menor = v[i];
        int j;
        for (j=i+1; j<n; ++j) {
            if (v[j] < val_menor) {
                val_menor = v[j];
                ind_menor = j;
            }
        }
        // Ao concluir a busca pelo menor deste segmento,
        // leva-o ateh o inicio do mesmo (marcado por i)
        int aux = v[i];
        v[i] = v[ind_menor];
        v[ind_menor] = aux;
    }
}
*/

/*
// Versao INSERCAO da ordenacao
void ordena(int v[], size_t n) {
    int i;
    // Marca a cada passo do laco a linha divisoria entre os
    // elementos ja ordenados e aqueles ainda por ordenar
    for (i=1; i<n; ++i) {
        int backup = v[i];  // porque v[i] pode ser sobrescrito por um maior
        int j;
        for (j=i-1; j>=0; --j) {
            if (v[j] > backup) {
                v[j+1] = v[j];
            }
            else {
                break;
            }
        }
        v[j+1] = backup;
    }
}
*/

/*
// Versao SHELL da ordenacao
void ordena(int v[], size_t n) {
    int I=0, k=1, incrementos[20];
    // Gera a sequencia de incrementos (1,4,13,40,121,...)
    while (I<20) {
        incrementos[I] = k;
        if (k > n) {    // Para quando gera um incremento maior que n
            break;
        }
        k = 3*k + 1;
        ++I;
    }
    // Inicia com o incremento que esta a duas posicoes atras da parada
    for (I=I-2; I>=0; --I) {
        k = incrementos[I];
        int s;
        for (s=1; s<=k; ++s) {  // Numero de segmentos a serem ordenados = k
            // Todo percurso agora vai de k em k pelo vetor
            int i;
            for (i=k; i<n; i+=k) {
                int backup = v[i];
                int j;
                for (j=i-k; j>=0; j-=k) {
                    if (v[j] > backup) {
                        v[j+k] = v[j];
                    }
                    else {
                        break;
                    }
                }
                v[j+k] = backup;
            }
        }
    }
}
*/

/*
// Versao RADIX da ordenacao
void ordena(int v[], size_t n) {
    struct FilaI* fila_dig[10];
    int f;
    // Cria uma fila para cada "simbolo do alfabeto" (0..9)
    for (f=0; f<10; ++f) {
        fila_dig[f] = cria();
    }
    // Numero maximo de digitos (pesos: unidade/dezena/centena...) a considerar
    int max_digitos = log10(INT32_MAX);
    int pos_digito = 1, peso = 1;

    // Para todas as posicoes de algarismos previstas...
    while (pos_digito <= max_digitos) {
        int i;
        // Coloca cada elemento do vetor em sua respectiva fila, de acordo
        // com o algarismo ("simbolo") na posicao da vez
        for (i=0; i<n; ++i) {
            int digito = (v[i]/peso) % 10;
            enqueue(fila_dig[digito], v[i]);
        }
        // Com todos os elementos do vetor nas filas, traz de volta das mesmas
        // na ordem crescente dos "simbolos" (algarismos) que elas representam
        for (i=f=0; f<10; ++f) {
            while (!underflow(fila_dig[f])) {
                v[i++] = dequeue(fila_dig[f]);
            }
        }
        ++pos_digito;
        peso *= 10;
    }
    for (f=0; f<10; ++f) {
        destroi(fila_dig[f]);
    }
}
*/

/*
// Versao MERGE da ordenacao
void ordena(int v[], int i, int s) {
    void intercala(int v[], int i, int m, int s) {
        int tam = s-i+1;        // tamanho do segmento para intercalar
        int* rasc = (int*) malloc(sizeof(int) * tam);   // rascunho
        int r=0, e=i, d=m+1;    // indices de percurso nos segmentos
        while (e<=m && d<=s) {  // enquanto AMBOS segmentos nao finalizados
            // Copia o menor dentre os valores dos segmentos para o rascunho
            rasc[r++] = (v[e] < v[d])? v[e++]: v[d++];
        }
        // Caso o segmento inferior tenha ficado com algum elemento (porque
        // o segmento superior foi completamente percorrido no laco acima)
        while (e<=m) {
            rasc[r++] = v[e++];
        }
        // Caso o segmento superior tenha ficado com algum elemento...
        while (d<=s) {
            rasc[r++] = v[d++];
        }
        // Traz do rascunho o vetor totalmente ordenado
        for (r=0; r<tam; ++r) {
            v[i+r] = rasc[r];
        }
        free(rasc);
    }
    if (i < s) {
        int m = (i+s)/2;
        ordena(v, i, m);
        ordena(v, m+1, s);
        intercala(v, i, m, s);
    }
}
*/

// Versao QUICK da ordenacao
void ordena(int v[], int i, int s) {
    if (i < s) {
        int pivo = v[(i+s)/2];
        int e = i, d = s;
        while (e <= d) {
            while (v[e] < pivo) ++e;
            while (v[d] > pivo) --d;
            if (e <= d) {
                int aux = v[e];
                v[e] = v[d];
                v[d] = aux;
                ++e, --d;
            }
        }
        ordena(v, i, d);
        ordena(v, e, s);
    }
}

