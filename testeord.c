#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "filaint.h" // implementada no 1o. bimestre :-)

void bubblesort(int [*], size_t);
void selectionsort(int [*], size_t);
void insertionsort(int [*], size_t);

void radixsort(int [*], size_t);
void mergesort(int [*], int, int);
void quicksort(int [*], int, int);

int main(void) {
    const size_t TAM_MINIMO = 16;
    const size_t TAM_MAXIMO = 16 * 1024 * 1024;
    FILE* arqcsv = fopen("/tmp/teste.csv", "wt");
    if (arqcsv == NULL) {
        perror("Nao pude criar o arquivo de medicoes");
        return EXIT_FAILURE;
    }
    fputs("Tamanho;Bubble;Selection;Insertion;Radixsort;Mergesort;Quicksort\n", arqcsv);
    
    size_t tam;
    for (tam = TAM_MINIMO; tam <= TAM_MAXIMO; tam *= 2) {
        fprintf(arqcsv, "%zd;", tam);
        int* chaves = malloc(sizeof(int) * tam);
        
        // Gera o conjunto de chaves da pior maneira ("pior caso"), que eh ter
        // os valores na ordem completamente inversa aquela da ordenacao
        int i, j;
        for (i = tam, j = 0; i > 0; --i, ++j) {
            chaves[j] = i;
        }
        
        // Faz a ordenacao sobre uma copia desse vetor fora de ordem
        int* copia = malloc(sizeof(int) * tam);
        memcpy(copia, chaves, sizeof(int)*tam);
        
        clock_t antes, depois, dif;
        
        if (tam <= 32*1024) {
            antes = clock();
            bubblesort(copia, tam);
            depois = clock();
            
            dif = depois - antes;
            fprintf(arqcsv, "%ld;", dif);
            printf("Bolha levou %ld ciclos para ordenar %zd elementos.\n", dif, tam);
        } else {
            fputs("-;", arqcsv);
        }
        if (tam <= 64*1024) {
            memcpy(copia, chaves, sizeof(int)*tam);
            antes = clock();
            selectionsort(copia, tam);
            depois = clock();
            
            dif = depois - antes;
            fprintf(arqcsv, "%ld;", dif);
            printf("Selecao levou %ld ciclos para ordenar %zd elementos.\n", dif, tam);
            
            memcpy(copia, chaves, sizeof(int)*tam);

            antes = clock();
            insertionsort(copia, tam);
            depois = clock();
            
            dif = depois - antes;
            fprintf(arqcsv, "%ld;", dif);
            printf("Insercao levou %ld ciclos para ordenar %zd elementos.\n", dif, tam);
        } else {
            fputs("-;-;", arqcsv);
        }
        memcpy(copia, chaves, sizeof(int)*tam);

        antes = clock();
        radixsort(copia, tam);
        depois = clock();
        
        dif = depois - antes;
        fprintf(arqcsv, "%ld;", dif);
        printf("Radixsort levou %ld ciclos para ordenar %zd elementos.\n", dif, tam);

        memcpy(copia, chaves, sizeof(int)*tam);

        antes = clock();
        mergesort(copia, 0, tam-1);
        depois = clock();
        
        dif = depois - antes;
        fprintf(arqcsv, "%ld;", dif);
        printf("Mergesort levou %ld ciclos para ordenar %zd elementos.\n", dif, tam);
        
        memcpy(copia, chaves, sizeof(int)*tam);

        antes = clock();
        quicksort(copia, 0, tam-1);
        depois = clock();
        
        dif = depois - antes;
        fprintf(arqcsv, "%ld\n", dif);
        printf("Quicksort levou %ld ciclos para ordenar %zd elementos.\n", dif, tam);
        
        free(copia);
        free(chaves);
    }
    fclose(arqcsv);
    
    return EXIT_SUCCESS;
}

#if 0
#define TROCA(a, b) \
    int aux = a; /* 2 */ \
    a = b;       /* 2 */ \
    b = aux;     /* 2 */
#endif
void TROCA(int a, int b) {
    int aux = a; /* 2 */
    a = b;       /* 2 */
    b = aux;     /* 2 */
}

void bubblesort(int vetor[], size_t n) {
    int i, j;
    for (i=1; i<=n; i=i+1) {                              /* 2 + 3(n+1) + 4n */
        // Laco interno faz comparacao entre pares
        for (j=n-1; j>0; --j) {                           /* (4 + 3n + 4(n-1))n */
            // Considerando uma ordenacao crescente...
            if (vetor[j] < vetor[j-1]) {                  /* (4 + 1 + 6)n² */
                // Usa macro para troca de valores...
                TROCA(vetor[j], vetor[j-1]);              /* (6 + 4 + 6)n² */
            }
        }
    }                                               //--------------------------
}                                                   // T(n) = 38n² + 7n + 5
                                                    // Classe O(n²)
                                                    
void selectionsort(int vetor[], size_t n) {         // Tambem na ordem de O(n²)
    int i, j;
    for (i=0; i<n-1; ++i) { // a posicao que vai ser ocupada com o menor da vez
        int menor = i;      // indice da posicao onde estah o menor
        for (j=i+1; j<n; ++j) { // comeca a busca por um menor ainda a frente
            if (vetor[j] < vetor[menor]) {
                menor = j;      // lembra quem eh o menor que vai ocupar a posicao i
            }
        }
        TROCA(vetor[i], vetor[menor]);  // efetiva a mudanca do menor para a posicao i
    }   
}

void insertionsort(int vetor[], size_t n) {
    int i, j;
    for (j=1; j<n; ++j) { // indice do proximo elemento a ser ordenado (inserido)
        int backup = vetor[j];
        for (i=j-1; vetor[i] > backup && i >= 0; --i) { // vai para tras
                                                        // procurando a posicao de insercao
            vetor[i+1] = vetor[i]; // abrindo espaco para o numero a ser inserido
        }
        vetor[i+1] = backup;    // poe o elemento na posicao que foi aberta para ele
    }
}

#define NUM_SIMBOLOS 10
#define MAX_ALGARISMOS 9

void radixsort(int vetor[], size_t n) {
    FilaInt* filas[NUM_SIMBOLOS];
    int digito;
    for (digito = 0; digito < NUM_SIMBOLOS; ++digito) {
        filas[digito] = cria();
    }
    // Ja que o vetor eh de numeros inteiros (int), o maior
    // numero armazenado nele sera na ordem de unidades de bilhao
    // (maximo de 9 algarismos no numero)
    int i, algarismos = 1;
    unsigned grandeza = 1;
    while (algarismos <= MAX_ALGARISMOS) {
        // Transfere os numeros do vetor para as filas, de acordo
        // com o digito na posicao da grandeza da vez
        for (i=0; i<n; ++i) { // para cada numero do vetor...
            int num = vetor[i] / grandeza; // descarta grandezas inferiores
            digito = num % 10; // pega o digito da grandeza
            enqueue(filas[digito], vetor[i]);
        }
        // Recupera os valores que foram transferidos para as filas
        for (digito=i=0; digito<NUM_SIMBOLOS; ++digito) {
            while (!underflow(filas[digito])) {
                vetor[i++] = dequeue(filas[digito]);
            }
        }
        ++algarismos;
        grandeza *= 10;
    }
    for (digito = 0; digito < NUM_SIMBOLOS; ++digito) {
        destroi(filas[digito]);
    }
}

void intercala(int vetor[], int inf, int meio, int sup) {
    int tam = sup - inf + 1;
    int* dest = malloc(sizeof(int) * tam);

    int i = 0, e = inf, d = meio+1;

    while (e <= meio && d <= sup) {
        dest[i++] = vetor[e] < vetor[d]? vetor[e++]: vetor[d++];
    }
    while (e <= meio) {
        dest[i++] = vetor[e++];
    }
    while (d <= sup) {
        dest[i++] = vetor[d++];
    }

    memcpy(vetor + inf, dest, sizeof(int) * tam);
    free(dest);
}

void mergesort(int vetor[], int inf, int sup) {
    if (inf < sup) {
        int meio = (inf + sup) / 2;
        mergesort(vetor, inf, meio);
        mergesort(vetor, meio+1, sup);
        intercala(vetor, inf, meio, sup);
    }
}

void quicksort(int vetor[], int inf, int sup) {
    if (inf < sup) {
        int esq = inf, dir = sup; // indices de percurso
        int pivo_referencia = vetor[(inf+sup)/2]; // salva valor de referencia
        while (dir >= esq) { // enquanto percursos opostos nao se cruzam
            while (vetor[esq] < pivo_referencia) ++esq; // procura por um maior antes do pivo
            while (vetor[dir] > pivo_referencia) --dir; // procura por um menor depois do pivo
            TROCA(vetor[esq], vetor[dir]);  // troca os valores que estao fora de ordem em
                                            // relacao ao pivo
            ++esq, --dir;   // continua nos proximos em cada sentido de percurso
        }
        quicksort(vetor, inf, dir); // recursao sobre cada segmento restante
        quicksort(vetor, esq, sup);
    }
}

