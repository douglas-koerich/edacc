#include <stdlib.h> // srand(), rand(), malloc(), free()
#include <stdio.h>  // printf(), scanf()
#include <time.h>   // time()
#include "revisao_exerc2v.h"

/*
#define N   20  // de acordo com o enunciado
*/

int main() {
    srand((unsigned) time(0));

    // Tamanho do vetor escolhido pelo usuario
    size_t N;
    printf("Qual o tamanho do vetor que deve ser gerado? ");
    scanf("%u", &N);

    // Vetor (conjunto) de numeros inteiros, com N elementos
    /*
    int vetor[N];   // alocacao na pilha do programa (area de variaveis locais)
                    // PROBLEMAS:
                    // (1) Tamanho da pilha eh limitado (padrao = 8 MiB);
                    // (2) Essa solucao nao eh suportada em compiladores C89
    */
                    // SOLUCAO: criar um "vetor" na area de alocacao dinamica (heap) - na verdade,
                    // essa reserva serah de um BLOCO disforme (sem tipo) de bytes
    int *vetor = (int*) malloc(N*sizeof(int)); // () contem o tamanho do BLOCO a ser reservado,
                                               // em bytes! O cast (int*) serve para dar um tipo
                                               // para a natureza "disforme" do bloco

    // Qualquer operacao que implique o percurso, a navegacao, a passagem
    // pelos elementos do vetor eh feita atraves de um laco
    int indice; // controle do laco + indice de referencia
    for (indice = 0;    // o primeiro indice do vetor eh sempre 0
         indice < N;    // o ultimo indice valido eh N-1
         ++indice) {    // vai de elemento em elemento (indice a indice)
        vetor[indice] = rand() % 10 + 1;    // (de 1 a 10) repare que estou INDEXANDO um ponteiro!
        // igual a fazer *(vetor+indice) = ..., usando aritmetica de ponteiro
    }

    // Lista de controle
    // item controle[N];
    item *controle = (item*) malloc(N*sizeof(item));    // ou sizeof(struct item)
    int contador = 0;

    // Percorre o vetor, passando por cada numero
    /*
    int *pnumero = &vetor[0];   // pnumero armazena o endereco de inicio do vetor (do seu
                                // primeiro elemento
    */
    int *pnumero = vetor;       // 'vetor' (sem []) eh sinonimo do endereco inicial dele na memoria

    for (indice = 0; indice < N; ++indice) {    // 'indice' passa a ser usado agora apenas pra
                                                // controle do laco
        int numero_da_vez = *pnumero;
        int *pnum_da_vez = &numero_da_vez;  // pnum_da_vez armazena o ENDERECO de memoria da
                                            // variavel numero_da_vez (nao o valor dela)

        // Percorro a lista de controle a procura desse numero para ver
        // se o mesmo ja ocorreu
        int i;
        for (i=0; i<contador; ++i) {
            // if (controle[i].valor == numero_da_vez) {
            if (controle[i].valor == *pnum_da_vez) {    // *pnum_da_vez recupera o "inquilino" do
                                                        // ENDERECO (ou seja, o valor armazenado)
                ++controle[i].repeticoes;
                break;
            }
        }
        if (i == contador) {    // chegou ao fim da lista sem achar
            // item *pnovo = &controle[contador];
            item *pnovo = controle + contador;  // (endereco inicial de 'controle' INCREMENTADO de
                                                //  'contador' itens a frente -> endereco adiante)
            /*
            controle[contador].valor = numero_da_vez;
            controle[contador].repeticoes = 1;
            */
            pnovo->valor = *pnum_da_vez;    // -> permite alcancar o campo a partir do endereco
                                            // inicial do registro em questao (apontado)
            pnovo->repeticoes = 1;
            ++contador;
        }
        ++pnumero;  // "incrementa" o ponteiro, PULANDO para o proximo endereco de elemento
    }
    // Impressao do vetor
    printf("Vetor gerado: ");
    for (indice = 0; indice < N; ++indice) {
        printf("%d ", vetor[indice]);
    }
    putchar('\n');

    // Elementos repetidos
    printf("Numeros repetidos(repeticoes): ");
    for (indice = 0; indice < contador; ++indice) {
        if (controle[indice].repeticoes > 1) {
            printf("%d(%u) ", controle[indice].valor, controle[indice].repeticoes);
        }
    }
    putchar('\n');

    // A alocacao dinamica me obriga a devolver manualmente os blocos de memoria reservados
    free(vetor);
    free(controle);

    return 0;
}

