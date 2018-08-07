#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void inverte_i(int*, size_t);   // versao iterativa (com laco para repeticao)
void inverte_r(int*, int*);     // versao recursiva (cada chamada executa um passo)
                                // (recebe ponteiros para dois numeros, nao interessa o tamanho do vetor)

int main(void) {
    size_t tamanho;
    printf("Digite o tamanho do vetor a ser preenchido: ");
    scanf("%zd", &tamanho);

    int vetor[tamanho];
    srand(time(NULL));
    int i;
    puts("Vetor original:");
    for (i=0; i<tamanho; ++i) {
        vetor[i] = rand() % 100;
        printf("%d ", vetor[i]);
    }
    putchar('\n');
    inverte_i(vetor, tamanho);
    puts("Vetor invertido:");
    for (i=0; i<tamanho; ++i) {
        printf("%d ", vetor[i]);
    }
    putchar('\n');
    inverte_r(vetor, vetor+tamanho-1);  // aritmetica de ponteiros
    puts("Vetor revertido:");
    for (i=0; i<tamanho; ++i) {
        printf("%d ", vetor[i]);
    }
    putchar('\n');
    return EXIT_SUCCESS;
}

void inverte_i(int* v, size_t t) {
    int i = 0, j = t-1;
    while (i < j) {
        int x = v[i];
        v[i] = v[j];
        v[j] = x;
        ++i, --j;
    }
}

void inverte_r(int* pi, int* pj) {
    if (pi < pj) {  // condicao terminal: endereco do "esquerdo" ainda eh menor que
                    // o endereco do "direito"?
        int x = *pi;
        *pi = *pj;
        *pj = x;
        inverte_r(pi+1, pj-1);  // feito o meu passo (sobre o par da minha vez,
                                // passo a vez para o meu "clone" fazer com o proximo par)
    }
}
