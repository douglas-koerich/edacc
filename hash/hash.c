#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

/**
 * Tratamento de colisoes pelo metodo do encadeamento exterior:
 * Usamos uma lista encadeada como estrutura de apoio, e definimos suas 
 * funcoes/operacoes diretamente aqui no codigo-fonte do TAD Hash
 */

// Definicao do ponto de operacao dentro da lista
enum Posicao {
    CABECA, // no primeiro noh (inicio da lista)
    CAUDA,  // no ultimo noh (fim da lista)
    VALOR   // usado pela remocao quando buscando um valor especifico
};
typedef enum Posicao Posicao;

struct Noh {
    R registro;
    struct Noh* proximo;
};
typedef struct Noh Noh;

struct Lista {
    Noh* cabeca;
};
typedef struct Lista Lista;

static bool underflow(const Lista* lista) {
    return lista->cabeca == NULL;
}

static void insere(Lista* lista, const R* registro, Posicao onde) {
    // Unica insercao eh na CAUDA porque se faz o percurso sobre toda
    // a lista a fim de certificar-se que a chave ainda nao estah na
    // lista
    if (onde != CAUDA) {
        fprintf(stderr, "Posicao INVALIDA para insercao!\n");
        return;
    }
    Noh* novo = malloc(sizeof(Noh));
    novo->registro = *registro;
    novo->proximo = NULL;
    if (underflow(lista)) {
        lista->cabeca = novo;
        return;
    }
    Noh* noh = lista->cabeca;
    while (noh->proximo != NULL &&
           noh->registro.chave != registro->chave) {
        noh = noh->proximo;
    }
    // Parou o laco porque encontrou um noh que jah tem a chave do
    // registro a ser inserido?
    if (noh->registro.chave == registro->chave) {
        noh->registro = *registro; // atualizacao, nao insercao
        free(novo); // descarta o noh que foi alocado para ser o novo
    } else {
        noh->proximo = novo;
    }
}

static R* retira(Lista* lista, Posicao onde, unsigned chave) {
    if (underflow(lista)) {
        return NULL; // nao existe noh/registro nesta lista
    }
    Noh* velho; // endereco do noh que sera retirado
    switch (onde) {
        case CABECA: // usada apenas para limpeza da lista (v. destroi)
            velho = lista->cabeca;
            lista->cabeca = velho->proximo;
            break;

        case VALOR: {
            Noh* noh = lista->cabeca;
            Noh* anterior = NULL; // "memoria" de qual era o noh anterior
                                  // atualizada a cada passo do laco
            while (noh != NULL && noh->registro.chave != chave) {
                anterior = noh; // lembra onde estava antes
                noh = noh->proximo;
            }
            if (noh == NULL) { // cheguei ao fim da lista sem encontrar
                return NULL;   // a chave
            }
            velho = noh; // chegou ao noh que serah removido

            // Mantem a continuidade da lista ligando o anterior ao
            // proximo deste noh
            if (anterior == NULL) { // nao existe um anterior?
                lista->cabeca = noh->proximo;
            } else {
                anterior->proximo = noh->proximo;
            }
            R* reg = malloc(sizeof(R));
            *reg = velho->registro;

            free(velho);
            return reg;
        }
        default:
            fprintf(stderr, "Posicao INVALIDA para remocao!\n");
    }
    return NULL;
}

static const R* busca(const Lista* lista, unsigned chave) {
    if (underflow(lista)) {
        return NULL;
    }
    Noh* noh = lista->cabeca;
    while (noh != NULL) {
        if (noh->registro.chave == chave) {
            return &noh->registro;
        }
        noh = noh->proximo;
    }
    return NULL;
}

static void imprime(const Lista* lista) {
    if (underflow(lista)) {
        printf("[VAZIA]");
        return;
    }
    printf("[CABECA]->");
    Noh* noh = lista->cabeca;
    while (noh != NULL) {
        printf("{%u}->", noh->registro.chave);
        noh = noh->proximo;
    }
    printf("[CAUDA]");
}

// Removemos a funcao de criacao da lista porque o vetor/tabela hash
// serah formado por uma colecao de 'struct Lista's

// Jah a funcao de destruicao permanece, mas agora com o unico proposito
// de "esvaziar" as listas antes de destruir o vetor de listas
static void destroi(Lista* lista) {
    while (!underflow(lista)) { // precisa liberar a memoria de cada noh
                                // individualmente
        retira(lista, CABECA, 0); // operacao de remocao mais simples
    }
}

/**
 * Implementacao do TAD Hash
 */

#define TAMANHO_TABELA 7 // um numero primo

struct Hash {
    Lista vetor[TAMANHO_TABELA];
};

Hash* criar(void) {
    Hash* h = malloc(sizeof(Hash)); // aloca o vetor
    int i;

    // Sendo um vetor de listas encadeadas...
    for (i = 0; i < TAMANHO_TABELA; ++i) {
        // ... inicializa cada lista com o status "vazia"
        h->vetor[i].cabeca = NULL;
    }
    return h;
}

void destruir(Hash* hash) {
    int i;
    for (i = 0; i < TAMANHO_TABELA; ++i) {
        destroi(&hash->vetor[i]);
    }
    free(hash);
}

void imprimir(const Hash* hash) {
    int i;
    for (i = 0; i < TAMANHO_TABELA; ++i) {
        printf("[%d] ", i);
        imprime(&hash->vetor[i]);
        putchar('\n');
    }
}

static int funcao_hashing(unsigned chave) { // retorna o indice em funcao da chave
    // Metodo pseudo-aleatorio
    srand(chave); // Ao usar a chave como semente da geracao de numeros
                  // aleatorios, garante-se o valor do retorno dos rand()'s
                  // seguintes
    /*
    int aleatorio = rand();
    int indice = aleatorio % TAMANHO_TABELA;
    return indice;
    */
    return rand() % TAMANHO_TABELA;
}

void inserir(Hash* hash, const R* novo) {
    int onde = funcao_hashing(novo->chave);
    insere(&hash->vetor[onde], novo, CAUDA); // sempre na cauda...
}

void retirar(Hash* hash, unsigned chave) {
    int onde = funcao_hashing(chave);
    R* registro = retira(&hash->vetor[onde], VALOR, chave); // retira por valor
    free(registro); // retira() faz um malloc; aqui faz free() sem usar o registro
}

const R* buscar(const Hash* hash, unsigned chave) {
    int onde = funcao_hashing(chave);
    /*
    R* registro = busca(&hash->vetor[onde], chave);
    return registro;
    */
    return busca(&hash->vetor[onde], chave);
}

