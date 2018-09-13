#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

struct Noh {
    TipoChave chave;
    TipoReg registro;
    struct Noh* proximo;
};
typedef struct Noh Noh;

struct Lista {
    Noh* cabeca; // noh inicial (primeiro) da lista encadeada
};

Lista* cria(void) {
    Lista* l = malloc(sizeof(Lista));
    l->cabeca = NULL; // indicacao de primeiro noh inexistente (lista vazia)
    return l;
}

bool underflow(const Lista* l) {
    return l->cabeca == NULL;
}

bool overflow(const Lista* l) {
    // Faz uma alocacao "fake" de um noh para verificar
    // condicao da memoria
    Noh* f = malloc(sizeof(Noh));
    if (f == NULL) {
        return true; // "lista" (memoria) estah cheia!
    }
    free(f); // nao deixa lixo para tras
    return false;
}

void inserir(Lista* l, TipoChave x, const TipoReg* r, Posicao p) {
    Noh* n = malloc(sizeof(Noh));
    n->chave = x;
    n->registro = *r; // memcpy(&n->registro, r, sizeof(TipoReg));
    switch (p) {
        case FIM:
            n->proximo = NULL;
            if (!underflow(l)) {
                Noh* u = l->cabeca;
                while (u->proximo != NULL) { // enquanto NAO for o ultimo
                    u = u->proximo;
                }
                // Na saida do laco, 'u' estah apontando para a cauda (ultimo)
                u->proximo = n;
                break; // o 'break' do 'case FIM' soh existe se !underflow
            }
            // ATENCAO: a falta de 'break' aqui eh INTENCIONAL, pois no caso
            // de lista vazia, a insercao no FIM eh igual a insercao no INICIO;
            // sem o 'break', a execucao continua pelo 'case INICIO' abaixo...

        case INICIO:
            // Eh NECESSARIO obedecer a ordem do proximo par de comandos,
            // do contrario - se elas forem invertidas - a referencia anterior
            // ao inicio da lista (e a tudo mais dela) serah perdida (substi-
            // tuida pelo endereco do novo noh)
            n->proximo = l->cabeca;
            l->cabeca = n;
            break;

        case ORDEM: // caso especial onde a posicao tem a ver com o valor
                    // da chave 'x' que estah sendo inserida; eh preciso
                    // percorrer a lista procurando o ponto certo onde o
                    // novo noh vai ser "enxertado"
            break;

        default:
            // Posicao VALOR nao eh valida para insercao
            puts("POSICAO DE INSERCAO INVALIDA!");
    }
}

TipoReg remover(Lista* l, TipoChave x, Posicao p) {
    // Presume-se que houve uma chamada anterior a underflow() para
    // verificar se a lista estava vazia ANTES da chamada a remover()

    TipoReg r = {}; // registro vazio
    Noh* n = l->cabeca; // faz acesso ao primeiro noh da lista
    switch (p) {
        case FIM:
            if (n->proximo != NULL) { // cabeca da lista NAO estah sozinha
                Noh* anterior = NULL; // memoria do endereco do noh anterior a 'n'
                while (n->proximo != NULL) {
                    anterior = n; // lembra quem era o anterior de 'n'
                    n = n->proximo;
                }
                r = n->registro;
                anterior->proximo = NULL; // atualiza o anterior como nova cauda
                                          // (ultimo noh) da lista
                free(n);
                break; // break do 'case FIM' se noh nao era UNICO
            }
            // ATENCAO: a falta de 'break' aqui eh INTENCIONAL, pois no caso
            // de lista com um UNICO noh, a remocao do FIM eh igual a do INICIO;
            // sem o 'break', a execucao continua pelo 'case INICIO' abaixo...

        case INICIO:
            l->cabeca = n->proximo; // indica como nova cabeca aquele que
                                    // era ateh agora o segundo noh da lista
            r = n->registro;
            free(n);
            break;

        case VALOR:
            break;

        default:
            // Posicao ORDEM nao eh valida para remocao
            puts("POSICAO/VALOR DE REMOCAO INVALIDA!");
    }
    return r;
}

void destroi(Lista* l) {
    while (!underflow(l)) {
        Noh* n = l->cabeca;
        l->cabeca = n->proximo; 
        free(n);
    }
}


void imprime(const Lista* l) {
    if (underflow(l)) {
        printf("(VAZIA)");
        return;
    }
    printf("(CABECA) ");
    Noh* n = l->cabeca;
    while (n != NULL) {
        imprime_tipo(n->chave, &n->registro);
        printf("-->");
        n = n->proximo;
    }
    printf("NULL (CAUDA)\n");
}

TipoReg* busca(const Lista* l, TipoChave x) {
    Noh* n = l->cabeca;
    while (n != NULL) { // serve tambem para verificar lista nula
        if (n->chave == x) {
            return &n->registro;
        }
        n = n->proximo; // continua busca pelo proximo noh
    }
    return NULL; // chegou ao fim sem encontrar a chave
}

