/* Programa que coleta uma sequencia/colecao de medidas e determina
 * a maior e a menor delas; ele tambem possui uma funcao que calcula a media
 * das medidas  */
#include <stdio.h>

/*
 * Tipo do retorno        Vetor de float's como primeiro parametro
 * |                      |    Numero de elementos do vetor como segundo parametro
 * |                      |    |
 * v                      v    v */
float calcula_media(float [*], size_t);

#define NUM_ELEMENTOS_VETOR 10  // capacidade maxima do vetor

int main(void) {
    float vetor[NUM_ELEMENTOS_VETOR];
    int indice;
    int qtde;
    do {
        // Pede ao usuario que defina quantas medidas vai digitar
        printf("Sr(a). usuario(a), quantas medidas vai digitar? ");
        scanf("%d", &qtde);
    } while (qtde < 1 || qtde > NUM_ELEMENTOS_VETOR);   // nao pode "estourar" o vetor!

    // Leitura de cada elemento do vetor dentro de um laco, ateh a quantidade escolhida
    for (indice = 0; indice < qtde; ++indice) {
        printf("Digite a medida do elemento [%d]: ", indice);
        scanf("%f", &vetor[indice]);    // scanf("%f", vetor+indice);
    }
    // Descobre qual o maior e o menor valor informados
    float menor = vetor[0]; // pra ter uma referencia de comparacao
    float maior = vetor[0]; // idem
    for (indice = 0; indice < qtde; ++indice) {
        if (vetor[indice] > maior) {
            maior = vetor[indice];
        }
        if (vetor[indice] < menor) {
            menor = vetor[indice];
        }
    }

    // Chama a funcao pra calcular a media DESSE vetor
    float media = calcula_media(vetor, qtde);   // "tamanho util" do vetor

    printf("A maior medida eh %f e a menor eh %f; a media das medidas eh %f.\n", maior, menor, media);
    return 0;
}

float calcula_media(float v[], size_t tam) {
    float media = 0.0;
    int ind = 0;
    while (ind < tam) {
        media += v[ind];
        ++ind;
    }
    return media / tam;
}

