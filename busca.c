#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define NUM 20

int busca_sequencial(int*, size_t, int, int*);
int busca_binaria(int*, int, int, int, int*);
int busca_interpolacao(int*, int, int, int, int*);

int main(int argc, char* argv[]) {
    int vetor[NUM];
    int i, n = 10000;
    float j;
    puts("Vetor: ");
    for (i=0,j=1.0; i<NUM; ++i, j*=1.2) {
        /*
        vetor[i] = n + i*10; // distribuicao uniforme (diferenca constante entre valores)
                             // nao havera valores concentrados numa faixa especifica
        */
        vetor[i] = n + i*j; // distribuicao NAO-uniforme (diferenca entre consecutivos vai
                            // ficando maior a medida que vamos para o fim do vetor)
        printf("%d ", vetor[i]);
    }
    putchar('\n');

    int chave;
    printf("Valor a ser procurado no vetor: ");
    scanf("%d", &chave);

    int comparacoes, indice;

    indice = busca_sequencial(vetor, NUM, chave, &comparacoes);
    printf("SEQ: Encontrei na posicao %d apos %d comparacoes.\n", indice, comparacoes);
    comparacoes = 0;    // tem que inicializar fora das recursoes
    indice = busca_binaria(vetor, 0, NUM-1, chave, &comparacoes);
    printf("BIN: Encontrei na posicao %d apos %d comparacoes.\n", indice, comparacoes);
    comparacoes = 0;    // tem que inicializar fora das recursoes
    indice = busca_interpolacao(vetor, 0, NUM-1, chave, &comparacoes);
    printf("INT: Encontrei na posicao %d apos %d comparacoes.\n", indice, comparacoes);

    return EXIT_SUCCESS;
}

int busca_sequencial(int* vetor, size_t tamanho, int chave, int* comparacoes) {
    *comparacoes = 0;
    int indice = 0;
    while (indice < tamanho) {
        bool achou = vetor[indice] == chave;
        ++(*comparacoes);
        if (achou) {
            return indice;
        }
        ++indice;
    }
    return -1;
}

int busca_binaria(int* vetor, int inferior, int superior, int chave, int* comparacoes) {
    if (inferior > superior) {
        return -1;
    }
    int meio = (inferior + superior) / 2;
    ++(*comparacoes);
    if (vetor[meio] == chave) {
        return meio;
    }
    if (chave < vetor[meio]) {
        return busca_binaria(vetor, inferior, meio-1, chave, comparacoes);
    } else {
        return busca_binaria(vetor, meio+1, superior, chave, comparacoes);
    }
}

int busca_interpolacao(int* vetor, int inferior, int superior, int chave, int* comparacoes) {
    if (inferior > superior) {
        return -1;
    }

    float distancia_total_entre_indices = superior - inferior;
    float diferenca_total_entre_chaves = vetor[superior] - vetor[inferior];
    float diferenca_valor_inferior_valor_chave = chave - vetor[inferior];
    // "REGRA-DE-3 SIMPLES": a distancia entre os indices dos extremos estah para
    // a diferenca entre os valores extremos ASSIM COMO a diferenca entre o valor
    // da chave procurada e o menor valor estah para a distancia entre a chave
    // procurada e o indice desse menor valor
    float distancia_indice_inferior_indice_chave =
        (diferenca_valor_inferior_valor_chave * distancia_total_entre_indices) /
        diferenca_total_entre_chaves;

    int indice_interpolado = inferior + distancia_indice_inferior_indice_chave;

    ++(*comparacoes);
    if (vetor[indice_interpolado] == chave) {
        return indice_interpolado;
    }
    if (chave < vetor[indice_interpolado]) {
        return busca_interpolacao(vetor, inferior, indice_interpolado-1, chave, comparacoes);
    } else {
        return busca_interpolacao(vetor, indice_interpolado+1, superior, chave, comparacoes);
    }
}
