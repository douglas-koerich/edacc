#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Registro a ser movimentado durante a ordenacao
#define N   20
struct Registro {
    unsigned chave; // campo usado como criterio de ordenacao
    char nome[N];
    int codigo;
    float valor;
};
typedef struct Registro Registro;

#define REGS 10

void ordena(Registro [*], size_t);

int main(void) {
    srand((unsigned) time(NULL));

    // Conjunto de registro ("base de dados") eh representado por um vetor
    Registro a[REGS];

    puts("Chaves geradas para o conjunto de registros:");
    int i;
    for (i=0; i<REGS; ++i) {
        bool primaria;
        do {
            a[i].chave = rand() % 100 + 1;
            primaria = true;
            int j = i-1;
            while (j >= 0) {
                if (a[j].chave == a[i].chave) { // se estah repetindo uma chave anterior...
                    primaria = false;
                    break;  // ... para de comparar e...
                }
                --j;
            }
        } while (primaria == false);    // ... volta pra gerar um outro valor
        printf("%u ", a[i].chave);
    }
    putchar('\n');

    ordena(a, REGS);
    puts("Chaves ordenadas:");
    for (i=0; i<REGS; ++i) {
        printf("%u ", a[i].chave);
    }
    putchar('\n');

    return EXIT_SUCCESS;
}

void ordena(Registro vetor[], size_t tamanho) {
    /** Bolha
    // Eh necessario executar um numero de varreduras de comparacao igual ao
    // tamanho do vetor para garantir que todas as chaves foram deslocadas para
    // suas respectivas posicoes ordenadas
    int n;
    for (n=1; n<=tamanho; ++n) {
        // Em cada varredura/passagem pelo vetor, pega duas posicoes e compara entre si
        // Faz isso para todos os pares de posicoes, comecando do fim ("fundo") do vetor
        int m;
        for (m=tamanho-1; m>0; --m) {
            if (vetor[m].chave < vetor[m-1].chave) { // chaves estao em posicoes trocadas no par?
                // A contiguidade fisica define que TODO o registro se movimenta
                // com a chave
                Registro temp;
                memcpy(&temp, &vetor[m], sizeof(Registro));
                memcpy(&vetor[m], &vetor[m-1], sizeof(Registro));
                memcpy(&vetor[m-1], &temp, sizeof(Registro));
            }
        }
    }
    ** Fim do bolha */
    /** Selecao direta
    int inicio = 0;
    while (inicio < tamanho) {
        int menor = inicio; // comeco a procura pelo menor de onde eu estou...
        int i;
        for (i=inicio; i<tamanho; ++i) {
            if (vetor[i].chave < vetor[menor].chave) {
                menor = i;
            }
        }
        Registro temp;
        memcpy(&temp, &vetor[inicio], sizeof(Registro));
        memcpy(&vetor[inicio], &vetor[menor], sizeof(Registro));
        memcpy(&vetor[menor], &temp, sizeof(Registro));
        ++inicio;   // continua o processo para o segmento restante do vetor
    }
    ** Fim do selecao direta */
    // Insercao direta
    int fronteira = 1;  // primeiro indice da parte nao ordenada por insercao
    while (fronteira < tamanho) {
        Registro temp;
        memcpy(&temp, &vetor[fronteira], sizeof(Registro));
        int i;
        for (i=fronteira-1; i>=0; --i) {
            if (vetor[i].chave > temp.chave) {
                memcpy(&vetor[i+1], &vetor[i], sizeof(Registro));
            }
            else {
                break;  // encontrei alguem menor do que eu, nao posso desloca-lo
            }
        }
        // A outra hipotese pra ter chego aqui eh i < 0
        // Em ambos os casos, vou trazer o valor para a posicao aberta para ele
        memcpy(&vetor[i+1], &temp, sizeof(Registro));

        ++fronteira;    // vai buscar novo valor para inserir na parte inicial do vetor
    }
}

/*
// Analise do algoritmo
void ordena(Registro vetor[], size_t tamanho) {                     // t = 0
    int n;                                                          // t = 0
    for (n=1; n<=tamanho; ++n) {                                    // t = A.n + B
        int m;                                                      // t = 0
        for (m=tamanho-1; m>0; --m) {                               // t = (C.n + D).n
            if (vetor[m].chave < vetor[m-1].chave) {                // t = E.n²
                Registro temp;                                      // t = 0
                memcpy(&temp, &vetor[m], sizeof(Registro));         // t = X.n²
                memcpy(&vetor[m], &vetor[m-1], sizeof(Registro));   // t = Y.n²
                memcpy(&vetor[m-1], &temp, sizeof(Registro));       // t = Z.n²
            }
        }
    }
}
T(n) = (C + E + X + Y + Z).n² + (A + D).n + B ==> O(n²)
*/
