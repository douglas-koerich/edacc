/* Escreva um programa que leia um conjunto de 10 numeros e chame uma funcao
 * para encontrar o maior numero contido nesse conjunto, retornando a posicao
 * desse elemento no conjunto.
 * Por exemplo, no conjunto: 2, 39, 12, 90, 45, 102, 26, 88, -1 e 29, o maior
 * numero pode ser encontrado na 6a. posicao do mesmo.
 */

#include <stdlib.h>
#include <stdio.h>

// O pre-processador do compilador substituira todas as ocorrencias de NUM_ELEMENTOS
// dentro do codigo-fonte por 10
#define NUM_ELEMENTOS   10

// Exemplo de prototipo de funcao que recebe um vetor como parametro
int busca_maior(int [*], size_t);   // pode ficar sem nomes dos parametros

int main(void) {
    // Declaracao de uma variavel-vetor para armazenar um conjunto HOMOGENEO de
    // elementos
    int conjunto[NUM_ELEMENTOS];

    /*
    // Para preencher o vetor, pode-se faze-lo elemento a elemento, um em cada
    // comando:
    conjunto[0] = 2;    // repare que o INDICE de posicao do primeiro elemento vale 0
    conjunto[1] = 39;
    ...
    */
    // A maneira mais pratica de preencher o conteudo de um conjunto/vetor eh
    // lancar mao de um LACO para visitar cada posicao, de maneira iterativa/repetida
    int ind;    // variavel usada pra armazenar o indice da vez e ao mesmo tempo
                // ser testada para controlar o numero de iteracoes do laco
    for (ind = 0; ind < NUM_ELEMENTOS; ++ind) {
        printf("Digite o proximo elemento do vetor (posicao %d): ", ind);
        scanf("%d", &conjunto[ind]);
    }

    // Chamar uma funcao passando o conjunto/vetor por parametro para que a mesma
    // possa buscar o maior, significa passar apenas o nome do vetor para a funcao;
    // porem, como a funcao nao tem ciencia do tamanho do vetor (porque isso pertence
    // a declaracao local), eh preciso tambem passa-lo como parametro
    int pos_maior;
    pos_maior = busca_maior(conjunto, NUM_ELEMENTOS);

    printf("O maior elemento do conjunto estah na posicao %d.\n", pos_maior);

    // Para conferir o resultado, imprimimos o vetor
    printf("Elementos do conjunto: ");
    for (ind = 0; ind < NUM_ELEMENTOS; ++ind) {
        printf("%d ", conjunto[ind]);   // imprime o elemento da vez...
    }
    putchar('\n');

    return EXIT_SUCCESS;
}

int busca_maior(int vetor[], size_t tamanho) {  // aqui, sem * nos colchetes!...
    int ind_maior = 0, maior = vetor[0];    // comeca assumindo que o maior esta no inicio
    int i;
    for (i = 0; i < tamanho; ++i) {
        if (vetor[i] > maior) {
            maior = vetor[i];   // atualiza controle de quem eh o maior do vetor
            ind_maior = i;
        }
    }
    return ind_maior;   // note que vai ser devolvida uma posicao que tem como base o 0
                        // (primeira posicao de um vetor)
}
