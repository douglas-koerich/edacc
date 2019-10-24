#ifdef DEBUG
#include <stdio.h>
#endif
#include <string.h>
#include "registro.h"
#include "alg_ordenacao.h"

static void imprime_chaves(const Reg vetor[], size_t n) {
#ifdef DEBUG
    int i;
    for (i = 0; i < n; ++i) {
        printf("%u ", vetor[i].chave);
    }
    putchar('\n');
#endif
}

void bolha(Reg vetor[], size_t n) {
    imprime_chaves(vetor, n); // imprime(?) as chaves no inicio
    int passagem;
    for (passagem = 1; passagem <= n; ++passagem) { // n passagens
        int posicao;
        for (posicao = n-1; posicao > 0; --posicao) {
            // Se existe uma chave menor na posicao mais a frente,
            // ela estah fora de ordem, deve trocar
            if (vetor[posicao].chave < vetor[posicao-1].chave) {
                troca(&vetor[posicao-1], &vetor[posicao]);
            }
        }
        // Imprime novamente as chaves apos essa passagem
        imprime_chaves(vetor, n);
    }
}

void selecao(Reg vetor[], size_t n) {
    imprime_chaves(vetor, n);
    int posicao;
    // Repete para todas as posicoes menos a ultima, que no final
    // acaba mesmo ficando com o maior valor
    for (posicao = 0; posicao < n-1; ++posicao) {
        int posicao_menor = posicao, outra_posicao;
        for (outra_posicao = posicao+1; outra_posicao < n; ++outra_posicao) {
            if (vetor[outra_posicao].chave < vetor[posicao_menor].chave) {
                posicao_menor = outra_posicao;
            }
        }
        // Usando aritmetica de ponteiros :-)
        troca(vetor + posicao, vetor + posicao_menor);
        imprime_chaves(vetor, n);
    }
}

void insercao(Reg vetor[], size_t n) {
    imprime_chaves(vetor, n);
    int posicao;
    // Comeca na segunda posicao do vetor pois a primeira nao
    // tem com quem ser comparada
    for (posicao = 1; posicao < n; ++posicao) {
        Reg* aux = malloc(sizeof(Reg));

        // Salva o registro original que vai ser reposicionado,
        // pois ele pode ser sobrescrito pelo deslocamento dos
        // outros
        memcpy(aux, vetor+posicao, sizeof(Reg));

        int posicao_anterior = posicao - 1;
        while (posicao_anterior >= 0 && // nao chegou no inicio E...
               vetor[posicao_anterior].chave > aux->chave) { // ... o anterior eh maior?
            memcpy(vetor+posicao_anterior+1, vetor+posicao_anterior,
                   sizeof(Reg)); // "empurra" o maior pra frente
            --posicao_anterior;
        }
        // Poe o elemento que estava sendo comparado na sua
        // posicao final
        memcpy(vetor+posicao_anterior+1, aux, sizeof(Reg));
        imprime_chaves(vetor, n);
    }
}

