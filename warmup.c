#include <stdio.h>
#include <limits.h>
#include "warmup.h"

struct lista {
    int* vetor;
    size_t contador, tamanho;
};

lista* cria(size_t maximo) {
    if (maximo == 0) {
        return NULL;
    }
    lista* nova = malloc(sizeof(lista));
    nova->contador = 0;
    nova->tamanho = maximo;
    nova->vetor = malloc(sizeof(int) * nova->tamanho);
    return nova;
}

void destroi(lista* l) {
    if (l == NULL) {
        return;
    }
    free(l->vetor);
    free(l);
}

size_t comprimento(const lista* l) {
    if (l == NULL) {
        return 0;
    }
    return l->contador;
}

bool vazio(const lista* l) {
    return l->contador == 0;
}

void imprime(const lista* l) {
    int i;
    for (i = 0; i < l->contador; ++i) {
        printf("%d", l->vetor[i]);
        if (i < l->contador - 1) {
            printf(", ");
        }
    }
}

int busca(const lista* l, int valor) {
    if (l == NULL) {
        return -1;
    }
    int i;
    for (i = 0; i < l->contador; ++i) {
        if (l->vetor[i] == valor) {
            return i;
        }
    }
    return -1;
}

void insere(lista* l, int valor, criterio opcao) {
    if (l == NULL || l->contador == l->tamanho) {
        return;
    }
    switch (opcao) {
        case FIM:
            l->vetor[l->contador++] = valor;
            break;

        case INICIO: {
            int i;
            // Desloca os elementos jah existentes uma posicao para
            // frente a fim de abrir o devido espaco para o novo elemento
            // na posicao inicial
            for (i = l->contador-1; i >= 0; --i) {
                l->vetor[i+1] = l->vetor[i];
            }
            l->vetor[0] = valor;
            ++l->contador;
            break;
        }
        case EM_ORDEM: {
            int i;
            // Desloca todos os valores maiores uma posicao para frente
            // a fim de colocar o novo valor no indice correto
            for (i = l->contador-1; i >= 0; --i) {
                if (l->vetor[i] > valor) {
                    l->vetor[i+1] = l->vetor[i];
                } else {
                    break;
                }
            }
            l->vetor[i+1] = valor;
            ++l->contador;
        }
        default:
            return;
    }
}

int retira(lista* l, criterio opcao, int valor) {
    // A funcao retorna INT_MIN (menor valor inteiro possivel) se
    // nao foi possivel remover (ou encontrar) o valor
    if (l == NULL || l->contador == 0) {
        return INT_MIN;
    }
    int n;
    switch (opcao) {
        case FIM:
            n = l->vetor[--l->contador];
            break;

        case INICIO: {
            n = l->vetor[0];
            int i;
            // Desloca todos os elementos restantes uma posicao para tras
            // a fim de nao deixar a posicao inicial "vazia" (pois todo
            // l eh considerado valido desde a sua posicao inicial)
            for (i = 0, --l->contador; i < l->contador; ++i) {
                l->vetor[i] = l->vetor[i+1];
            }
            break;
        }

        case VALOR: {
            n = INT_MIN;
            int i;
            for (i = 0; i < l->contador; ++i) {
                if (l->vetor[i] == valor) {
                    n = valor;
                    break;
                }
            }
            for (--l->contador; i < l->contador; ++i) {
                l->vetor[i] = l->vetor[i+1];
            }
            break;
        }

        default:
            n = INT_MIN;
    }
    return n;
}
