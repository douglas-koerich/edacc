#include <stdio.h>
#include <limits.h>
#include "warmup.h"

static size_t contador, tamanho;

int* cria(size_t maximo) {
    if (maximo == 0) {
        return NULL;
    }
    contador = 0;
    tamanho = maximo;
    return malloc(sizeof(int) * tamanho);
}

void destroi(int* vetor) {
    if (vetor == NULL) {
        return;
    }
    free(vetor);
}

size_t comprimento(const int* vetor) {
    if (vetor == NULL) {
        return 0;
    }
    return contador;
}

bool vazio(const int* vetor) {
    return contador == 0;
}

void imprime(const int* vetor) {
    int i;
    for (i = 0; i < contador; ++i) {
        printf("%d ", vetor[i]);
    }
}

int busca(const int* vetor, int valor) {
    if (vetor == NULL) {
        return -1;
    }
    int i;
    for (i = 0; i < contador; ++i) {
        if (vetor[i] == valor) {
            return i;
        }
    }
    return -1;
}

void insere(int* vetor, int valor, criterio opcao) {
    if (vetor == NULL || contador == tamanho) {
        return;
    }
    switch (opcao) {
        case FIM:
            vetor[contador++] = valor;
            break;

        case INICIO: {
            int i;
            // Desloca os elementos jah existentes uma posicao para
            // frente a fim de abrir o devido espaco para o novo elemento
            // na posicao inicial
            for (i = contador-1; i >= 0; --i) {
                vetor[i+1] = vetor[i];
            }
            vetor[0] = valor;
            ++contador;
            break;
        }
        case EM_ORDEM: {
            int i;
            // Desloca todos os valores maiores uma posicao para frente
            // a fim de colocar o novo valor no indice correto
            for (i = contador-1; i >= 0; --i) {
                if (vetor[i] > valor) {
                    vetor[i+1] = vetor[i];
                } else {
                    break;
                }
            }
            vetor[i+1] = valor;
            ++contador;
        }
        default:
            return;
    }
}

int retira(int* vetor, criterio opcao, int valor) {
    // A funcao retorna INT_MIN (menor valor inteiro possivel) se
    // nao foi possivel remover (ou encontrar) o valor
    if (vetor == NULL || contador == 0) {
        return INT_MIN;
    }
    int n;
    switch (opcao) {
        case FIM:
            n = vetor[--contador];
            break;

        case INICIO: {
            n = vetor[0];
            int i;
            // Desloca todos os elementos restantes uma posicao para tras
            // a fim de nao deixar a posicao inicial "vazia" (pois todo
            // vetor eh considerado valido desde a sua posicao inicial)
            for (i = 0, --contador; i < contador; ++i) {
                vetor[i] = vetor[i+1];
            }
            break;
        }

        case VALOR: {
            n = INT_MIN;
            int i;
            for (i = 0; i < contador; ++i) {
                if (vetor[i] == valor) {
                    n = valor;
                    break;
                }
            }
            for (--contador; i < contador; ++i) {
                vetor[i] = vetor[i+1];
            }
            break;
        }

        default:
            n = INT_MIN;
    }
    return n;
}
