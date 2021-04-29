#include <stdio.h>
#include <string.h> // para usar memcmp() em compare()
#include "lista.h"

struct noh {
    Registro dado;          // elemento armazenado neste noh da lista
    struct noh* proximo;    // referencia/ligacao com o noh seguinte
};
typedef struct noh Noh;

struct lista {
    Noh* cabeca;     // ponteiro para o primeiro noh da lista ("acesso externo")
    size_t contador; // numero de nohs da lista no momento
};

Lista* create(void) {
    /*
    Lista* nova = malloc(sizeof(Lista));
    nova->cabeca = NULL; // lista nao possui um primeiro noh (vazia)
    nova->contador = 0;
    */
    Lista* nova = calloc(1, sizeof(Lista));
    return nova;
}

void destroy(Lista* a_lista) {
    // Antes de apagar a estrutura (struct lista) que faz referencia aos
    // nohs da lista, preciso apagar esses nohs da memoria!
    while (!underflow(a_lista)) {
        Registro nao_usado;
        extract(a_lista, &nao_usado, CABECA, 0);
    }
    free(a_lista);
}

bool underflow(const Lista* a_lista) {
    return a_lista->contador == 0;
}

size_t size(const Lista* a_lista) {
    return a_lista->contador;
}

void print(const Lista* a_lista) {
    Noh* noh = a_lista->cabeca;
    printf("(INICIO) ");
    while (noh != NULL) {
        // Noh eh valido, imprime-o...
        printf("{%d,%c} ", noh->dado.chave, noh->dado.valor);
        noh = noh->proximo;
    }
    printf("(FIM)");
}

void rprint(const Lista* a_lista) {
    puts("Operacao NAO SUPORTADA em lista simples");
}

void insert(Lista* a_lista, const Registro* novo_elemento, Criterio forma,
            unsigned posicao) {
    Noh* novo_noh = malloc(sizeof(Noh));
    novo_noh->dado = *novo_elemento;

    if (underflow(a_lista)) { // se a lista ainda estiver vazia...
        forma = CABECA; // ... vamos inserir usando o criterio mais "facil"
    }
    Noh* noh = a_lista->cabeca;
    switch (forma) {
        case CABECA:    // novo elemento no inicio
            novo_noh->proximo = a_lista->cabeca;
            a_lista->cabeca = novo_noh;
            break;

        case CAUDA: {   // novo elemento no fim da lista
            while (noh->proximo != NULL) { // enquanto nao for o ultimo...
                // ... vai para o proximo
                noh = noh->proximo;
            }
            noh->proximo = novo_noh;
            novo_noh->proximo = NULL;          
            break;
        }

        case CRESCENTE: { // novo elemento em ordem crescente relativo aos
                          // vizinhos
            Noh* anterior = NULL; // (sobre o uso deste ponteiro, veja a
                                  // remocao da CAUDA abaixo...)
            while (noh != NULL // Enquanto nao passo do fim da lista...
                   // ... E o noh da vez tem um valor menor que o novo
                   && noh->dado.chave < novo_noh->dado.chave) {
                // ... procuro o ponto de insercao no proximo noh
                anterior = noh;
                noh = noh->proximo;
            }
            novo_noh->proximo = noh;
            if (anterior != NULL) {
                anterior->proximo = novo_noh;
            } else {
                a_lista->cabeca = novo_noh;
            }
            break;
        }
        case DECRESCENTE: { // idem, em ordem decrescente
            Noh* anterior = NULL;
            while (noh != NULL
                   && noh->dado.chave > novo_noh->dado.chave) {
                anterior = noh;
                noh = noh->proximo;
            }
            novo_noh->proximo = noh;
            if (anterior != NULL) {
                anterior->proximo = novo_noh;
            } else {
                a_lista->cabeca = novo_noh;
            }
            break;
        }
        case ORDINAL:   // na primeira, segunda, ..., n-esima posicao
            break;

        default:
            puts("ERRO: criterio de insercao INVALIDO!");
            destroy(a_lista);

            // Nao esquecer de apagar tambem o noh que foi recem-criado
            // nesta mesma funcao
            free(novo_noh);

            exit(EXIT_FAILURE);
    }
    ++a_lista->contador;
}

void extract(Lista* a_lista, Registro* removido, Criterio forma,
             unsigned posicao) {
    if (underflow(a_lista)) {
        puts("ERRO: lista vazia!");
        destroy(a_lista);
        exit(EXIT_FAILURE);
    }
    Noh* noh = a_lista->cabeca;
    switch (forma) {
        case CABECA:    // remove do inicio
            a_lista->cabeca = noh->proximo;
            *removido = noh->dado;
            free(noh);
            break;

        case CAUDA: {   // remove do fim da lista
            Noh* anterior = NULL;
            while (noh->proximo != NULL) { // como na insercao...
                anterior = noh; // ("lembra" quem eh o noh anterior
                                //  antes de avancar)
                // ... procura o ultimo noh (cauda) da lista
                noh = noh->proximo;
            }
            *removido = noh->dado;
            if (anterior != NULL) {
                // Ok, existe um noh anterior e ele passa a ser a
                // cauda da lista
                anterior->proximo = NULL;
            } else {
                // A cauda da lista eh o UNICO noh da mesma, entao
                // remove-lo deve tornar a lista vazia novamente
                a_lista->cabeca = NULL;
            }
            free(noh);
            break;
        }
        case ORDINAL:   // remove o primeiro, segundo, ..., n-esimo noh
            break;

        case VALOR: {   // remove baseado na chave
            Noh* anterior = NULL;
            while (noh != NULL) {
                if (noh->dado.chave == removido->chave) {
                    *removido = noh->dado;
                    if (anterior != NULL) {
                        anterior->proximo = noh->proximo;
                    } else {
                        a_lista->cabeca = noh->proximo;
                    }
                    free(noh);

                    --a_lista->contador;
                    break; // jah encontrou e removeu
                }
                anterior = noh;
                noh = noh->proximo;
            }
            // Se chegou neste ponto eh porque a chave nao foi encontrada
            // para ser removida, ou se encontrada jah foi removida
            return; // para nao decrementar o contador novamente
        }
        default:
            puts("ERRO: criterio de remocao INVALIDO!");
            destroy(a_lista);
            exit(EXIT_FAILURE);
    }
    --a_lista->contador;
}

bool search(const Lista* a_lista, int chave_x, Registro* p_reg) {
    Noh* noh = a_lista->cabeca;
    while (noh != NULL) {
        if (noh->dado.chave == chave_x) {
            *p_reg = noh->dado; // copia todo o registro para o endereco
                                // (no ponteiro) passado pra funcao 
            return true;
        }
        noh = noh->proximo;
    }
    return false; // chave_x nao foi encontrada
}

bool compare(const Lista* lista_1, const Lista* lista_2) {
    Noh* noh1 = lista_1->cabeca,
       * noh2 = lista_2->cabeca;
    while (noh1 != NULL && noh2 != NULL) {
        // Comparacao entre nohs eh possivel
        if (memcmp(&noh1->dado, &noh2->dado, sizeof(Registro)) != 0) {
            return false; // conteudos sao diferentes!
        }
        noh1 = noh1->proximo; // avanca pelas duas listas simultaneamente
        noh2 = noh2->proximo;
    }
    // Espera-se que tenhamos chegado ao fim de ambas as listas ao mesmo tempo
    // (se uma for mais longa que a outra entao sao diferentes)
    return noh1 == NULL && noh2 == NULL;
}