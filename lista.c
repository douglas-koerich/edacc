#include "lista.h"

// Definicao interna de um tipo que armazena na memoria:
// - O elemento (inteiro, registro, etc.)
// - O "link" pro proximo elemento, isto eh, o ponteiro para o proximo noh
struct Noh {
    int valor;
    struct Noh* proximo;
};

// Definicao concreta do TAD: Lista
struct Lista {
    Noh* cabeca; // ponteiro para o primeiro noh da lista
};

Lista* cria(void) {
    Lista* nova = malloc(sizeof(Lista)); // alocacao da estrutura contendo
                                         // apenas o ponteiro da cabeca
    nova->cabeca = NULL; // nao existe ainda um noh na lista
    return nova;
}

void destroi(Lista* lista) {
    while (!underflow(lista)) { // precisa liberar a memoria de cada noh
                                // individualmente
        retira(lista, INICIO, NULL); // operacao de remocao mais simples
    }
    free(lista);
}

bool underflow(const Lista* lista) {
    return lista->cabeca == NULL;
}

void insere(Lista* lista, int elemento, Posicao onde) {
    Noh* novo = malloc(sizeof(Noh)); // aloca somente quando necessario
    novo->valor = elemento;
    switch (onde) {
        case CABECA:
            novo->proximo = lista->cabeca; // recupera o endereco do (agora)
                                           // antigo primeiro noh da lista
            lista->cabeca = novo; // redefine quem eh o novo primeiro noh
            break;

        case CAUDA:
            break;

        case ORDEM:
            break;

        default:
            fprintf(stderr, "Posicao INVALIDA para insercao!\n");
            free(novo); // descarta o noh recem-alocado
    }
}

int retira(Lista* lista, Posicao onde, const int* valor) {
    Noh* velho; // endereco do noh que sera retirado
    switch (onde) {
        case CABECA:
            velho = lista->cabeca;
            lista->cabeca = velho->proximo;
            break;

        case CAUDA:
            break;

        case VALOR:
            break;

        default:
            fprintf(stderr, "Posicao INVALIDA para remocao!\n");
    }
    int val = velho->valor;
    free(velho);
    return val;
}

