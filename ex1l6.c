#include <stdlib.h>
#include <stdio.h>

struct Noh {
    int valor;
    struct Noh* proximo;
};
typedef struct Noh Noh;

struct Lista {
    Noh* cabeca;
};
typedef struct Lista Lista;

static Lista* cria() {
    Lista* l = (Lista*) malloc(sizeof(Lista));
    l->cabeca = NULL;
    return l;
}

static void destroi(Lista* l) {
    if (l != NULL) {
        while (l->cabeca != NULL) {
            Noh* x = l->cabeca;
            l->cabeca = x->proximo;
            free(x);
        }
        free(l);
    }
}

static void insere(Lista* l, int novo) {
    if (l != NULL) {
        Noh* n = (Noh*) malloc(sizeof(Noh));
        n->valor = novo;
        n->proximo = l->cabeca;
        l->cabeca = n;
    }
}

static Noh* lbusca_i(Lista* l, int chave) {
    if (l == NULL) {
        return NULL;
    }
    Noh* n = l->cabeca;
    while (n != NULL) {
        if (n->valor == chave) {
            break;
        }
        n = n->proximo;
    }
    return n;
}

Noh* lbusca_no(Noh* atual, int chave) {
    // Condicao terminal #1
    if (atual == NULL) {    // nao ha noh a ser inspecionado
        return NULL;
    }
    // Condicao terminal #2
    if (atual->valor == chave) {
        return atual;       // encontrei a chave neste noh
    }
    // Fase ativa (chamada recursiva) - nao achei nem eh noh inexistente, devo continuar
    return lbusca_no(atual->proximo, chave);
}

static Noh* lbusca_r(Lista* l, int chave) {
    if (l == NULL) {    // lista nao criada
        return NULL;
    }
    return lbusca_no(l->cabeca, chave);
}

int vbusca_r(int* vetor, size_t tamanho, int chave) {
    // Condicao terminal #1: fim do vetor
    if (tamanho == 0) {
        return -1;
    }
    // Condicao terminal #2: encontrei nesta posicao do vetor
    if (vetor[0] == chave) {
        return 0;
    }
    // Fase ativa (chamada recursiva) - procuro no proximo (do proximo (do proximo))...
    int ret = vbusca_r(vetor+1, tamanho-1, chave);
    if (ret == -1) {
        return ret;
    }
    else {
        return ret + 1;  // cada retorno incrementa o valor do indice devolvido
                         // com a sua posicao onde nao foi encontrado...
    }
}

//int vbusca_i(int vetor[], size_t tamanho, int chave) {
int vbusca_i(int* vetor, size_t tamanho, int chave) {
    int i = 0;
    while (i < tamanho) {
        if (vetor[i] == chave) {
            return i;
        }
        ++i;
    }
    return -1;
}

#define TAMANHO 10

int main(void) {
    int vetor[TAMANHO];
    Lista* lista = cria();
    int i;
    for (i=TAMANHO-1; i>=0; --i) {
        vetor[i] = i;
        insere(lista, i);
    }
    // Buscas sem sucesso:
    int indice = vbusca_r(vetor, TAMANHO, TAMANHO);
    printf("Chave %d %sencontrada no vetor (ind=%d)\n", TAMANHO,
           indice==-1? "NAO ": "", indice);
    void* endereco = lbusca_r(lista, TAMANHO);
    printf("Chave %d %sencontrada na lista (end=%p)\n", TAMANHO,
           endereco==NULL? "NAO ": "", endereco);

    // Buscas com sucesso:
    indice = vbusca_r(vetor, TAMANHO, TAMANHO/2);
    printf("Chave %d %sencontrada no vetor (ind=%d)\n", TAMANHO/2,
           indice==-1? "NAO ": "", indice);
    endereco = lbusca_r(lista, TAMANHO/2);
    printf("Chave %d %sencontrada na lista (end=%p)\n", TAMANHO/2,
           endereco==NULL? "NAO ": "", endereco);

    destroi(lista);

    return EXIT_SUCCESS;
}
