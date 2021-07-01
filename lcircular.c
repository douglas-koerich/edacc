#include <stdio.h>
#include "lista.h"

struct noh {
    Registro dado;
    struct noh* proximo;
};
typedef struct noh Noh;

struct lista {
    Noh* cauda; // na lista circula a referencia externa eh para a cauda
                // porque a partir dela chega-se facilmente ah cabeca
    size_t contador;
};

Lista* create(void) {
    Lista* nova = calloc(1, sizeof(Lista));
    return nova;
}

void destroy(Lista* a_lista) {
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
    if (underflow(a_lista)) {
        printf("(VAZIA)");
        return;
    }
    Noh* noh = a_lista->cauda;
    printf("(INICIO) ");
    do {
        noh = noh->proximo; // vai ao proximo antes de imprimi-lo
        printf("{%d,%c} ", noh->dado.chave, noh->dado.valor);
    } while (noh != a_lista->cauda);
    printf("(FIM)");
}

void rprint(const Lista* a_lista) {
    puts("Operacao NAO SUPORTADA em lista circular");
}

void insert(Lista* a_lista, const Registro* novo_elemento, Criterio forma,
            unsigned posicao) {
    Noh* novo_noh = malloc(sizeof(Noh));
    novo_noh->dado = *novo_elemento;

    if (underflow(a_lista)) {
        novo_noh->proximo = novo_noh; // o unico noh aponta pra sim mesmo
        a_lista->cauda = novo_noh;
        ++a_lista->contador;
        return;
    }
    Noh* anterior;
    Noh* noh = a_lista->cauda;
    switch (forma) {
        case CABECA: // Na lista circular ambos os tipos de insercao: CABECA
        case CAUDA:  // e CAUDA sao implementados pelos mesmos passos (porque
                     // o novo noh fica na mesma posicao em relacao aos demais)
            novo_noh->proximo = a_lista->cauda->proximo;
            a_lista->cauda->proximo = novo_noh;
            if (forma == CAUDA) {
                a_lista->cauda = novo_noh;
            }
            break;

        case CRESCENTE:
            // Prossiga pela lista...
            do {
                anterior = noh;
                noh = noh->proximo;
            }
            // ... enquanto nao retorna para a cauda E ...
            while (noh != a_lista->cauda &&
                   // ... o noh da vez tem um valor menor que o novo
                   noh->dado.chave < novo_noh->dado.chave);
            
            // Se ao fim do laco o noh da vez ainda tem valor menor, entao eh
            // porque voltou para a cauda e o novo noh tem valor maior que todos
            if (noh->dado.chave < novo_noh->dado.chave) {
                // O anterior do novo noh eh a cauda atual
                anterior = a_lista->cauda;

                // A nova cauda serah o novo noh
                a_lista->cauda = novo_noh;
            }
            novo_noh->proximo = anterior->proximo;
            anterior->proximo = novo_noh;
            break;

        case DECRESCENTE:
            do {
                anterior = noh;
                noh = noh->proximo;
            }
            // ... enquanto nao retorna para a cauda E ...
            while (noh != a_lista->cauda &&
                   // ... o noh da vez tem um valor maior que o novo
                   noh->dado.chave > novo_noh->dado.chave);
            
            // Se ao fim do laco o noh da vez ainda tem valor maior, entao eh
            // porque voltou para a cauda e o novo noh tem valor menor que todos
            if (noh->dado.chave > novo_noh->dado.chave) {
                anterior = a_lista->cauda;
                a_lista->cauda = novo_noh;
            }
            novo_noh->proximo = anterior->proximo;
            anterior->proximo = novo_noh;
            break;

        case ORDINAL:   // na primeira, segunda, ..., n-esima posicao
            break;

        default:
            puts("ERRO: criterio de insercao INVALIDO!");
            destroy(a_lista);

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
    Noh* anterior;
    Noh* noh = a_lista->cauda;
    switch (forma) {
        case CABECA: {
            Noh* cabeca = a_lista->cauda->proximo;
            if (cabeca == a_lista->cauda) {
                // A cabeca e a cauda sao o mesmo noh (unico na lista)
                a_lista->cauda = NULL;
            } else {
                a_lista->cauda->proximo = cabeca->proximo;
            }
            *removido = cabeca->dado;
            free(cabeca);
            break;
        }

        case CAUDA:
            // Procura o penultimo noh da lista...
            anterior = a_lista->cauda;
            do {
                anterior = anterior->proximo;
            } while (anterior->proximo != a_lista->cauda);
            if (anterior == a_lista->cauda) {
                // A cauda e seu noh anterior sao o mesmo (e unico) noh da lista
                a_lista->cauda = NULL;
            } else {
                anterior->proximo = a_lista->cauda->proximo;
                a_lista->cauda = anterior;
            }
            *removido = noh->dado;
            free(noh);
            break;

        case ORDINAL:   // remove o primeiro, segundo, ..., n-esimo noh
            break;

        case VALOR:
            do {
                anterior = noh;
                noh = noh->proximo;
                if (noh->dado.chave == removido->chave) {
                    anterior->proximo = noh->proximo;
                    if (noh == a_lista->cauda) {
                        a_lista->cauda = anterior;
                    }
                    *removido = noh->dado;
                    free(noh);

                    --a_lista->contador;
                    break; // jah encontrou e removeu
                }
            } while (noh != a_lista->cauda);

            // Se chegou neste ponto eh porque a chave nao foi encontrada
            // para ser removida, ou se encontrada jah foi removida
            return; // para nao decrementar o contador novamente

        default:
            puts("ERRO: criterio de remocao INVALIDO!");
            destroy(a_lista);
            exit(EXIT_FAILURE);
    }
    --a_lista->contador;
}

Registro* search(const Lista* a_lista, int chave_x) {
    if (underflow(a_lista)) {
        return NULL;
    }
    Noh* noh = a_lista->cauda;
    do {
        noh = noh->proximo;
        if (noh->dado.chave == chave_x) {
            return &noh->dado;
        }
    } while (noh != a_lista->cauda);

    return NULL;
}
