#include <stdio.h>
#include "lista.h"

struct Noh {
    char elemento; // valor armazenado na lista (lista de caracteres)
    struct Noh* proximo; // endereco do noh sucessor (seguinte) na lista
};
typedef struct Noh Noh;

struct Lista {
    Noh* cabeca; // endereco do primeiro noh da lista

    // Campos adicionais que comporiam um noh-cabecalho da lista
    size_t tamanho; // numero de nohs (evita percorrer para contar)
    Noh* cauda; // leva diretamente ao ultimo noh da lista
};

Lista* criar(void) {
    Lista* l = malloc(sizeof(Lista));
    l->cabeca = NULL;

    // Preenche os campos adicionais do noh-cabecalho
    l->tamanho = 0;
    l->cauda = NULL;

    return l;
}

void destruir(Lista* l) {
    if (l == NULL) { // protecao contra parametro invalido
        return;
    }
    // Eh importante (seria um ERRO nao faze-lo) liberar todos os
    // nohs da memoria antes de perder os enderecos de referencia a eles
    while (!underflow(l)) {
        remover(l, NULL, CABECA, 0); // NULL e 0 serao ignorados
    }
    free(l); // somente apos remover da cabeca em diante...
}

bool underflow(const Lista* l) {
    if (l == NULL) {
        return false;
    }
    return l->cabeca == NULL; // ou: return l->tamanho == 0;
}

size_t comprimento(const Lista* l) {
    if (l == NULL) {
        return 0;
    }
    return l->tamanho;
}

void inserir(Lista* l, char c, Posicao p, int i) {
    // Se 'p' nao for igual a FIXA, o parametro 'i' (numero da
    // posicao onde deveria ser inserido) eh ignorado
    if (l == NULL) {
        return;
    }
    Noh* n = malloc(sizeof(Noh));
    n->elemento = c;
    switch (p) {
        case CABECA:
            n->proximo = l->cabeca; // salva o endereco do antigo primeiro
                                    // noh no novo noh (agora, o primeiro)
            l->cabeca = n;
            if (l->cauda == NULL) {
                l->cauda = n;
            }
            break;

        case CAUDA: {
            n->proximo = NULL; // o novo noh sempre terah NULL como seu proximo
            // TODO: usar o ponteiro 'cauda' disponivel no noh-cabecalho para
            // buscar (sem um laco) o ultimo noh da lista
            // ...

            // Se a lista estah vazia, inserir no FIM eh a mesma operacao que
            // inserir no INICIO
            if (l->cabeca == NULL) {
                l->cabeca = n;
                break; // interrompe o case
            }
            Noh* u = l->cabeca;
            while (u->proximo != NULL) { // enquanto nao encontra o ULTIMO da lista
                u = u->proximo; // ... vai "caminhando" ao longo da lista
            }
            u->proximo = n; // o proximo do antigo ultimo eh o novo ultimo
            break;
        }

        case CRESCENTE:
            break;

        case DECRESCENTE:
            break;

        case FIXA:
            break;

        default:
            puts("Posicao INVALIDA!");
            free(n); // libera o noh alocado!
    }
    ++l->tamanho;
}

bool remover(Lista* l, char* pc, Posicao p, int i) {
    if (l == NULL || underflow(l)) {
        return false;
    }
    Noh* n;
    switch (p) {
        case CABECA:
            n = l->cabeca;
            l->cabeca = n->proximo;
            if (l->cabeca == NULL) {
                l->cauda = NULL;
            }
            break;

        case CAUDA: {
            Noh* ant = NULL; // Eh preciso um ponteiro para o noh anterior...
            n = l->cabeca;
            while (n->proximo != NULL) {
                ant = n; // ... que lembre o endereco do PENULTIMO quando achar
                         // o ultimo
                n = n->proximo;
            }
            // Se de fato existe um anterior a este noh (n) que eh o ultimo...
            if (ant != NULL) {
                ant->proximo = NULL;
            } else { // Se nao existe, entao o ultimo eh o UNICO!
                l->cabeca = NULL; // lista volta a ficar vazia
            }
            l->cauda = ant;
            break;
        }

        case FIXA:
            break;

        default: // inclui CRESCENTE e DECRESCENTE
            puts("Posicao INVALIDA!");
            return false;
    }
    // Se o ponteiro 'pc' for NULL, quem chamou 'remover' nao estah
    // interessado em obter o elemento que estava no noh removido
    if (pc != NULL) {
        *pc = n->elemento;
    }
    free(n);
    --l->tamanho;
    return true;
}

bool buscar(const Lista* l, char x) {
    if (l == NULL || underflow(l)) {
        return false;
    }
    Noh* n = l->cabeca;
    while (n != NULL) { // enquanto houver noh para inspecionar...
        if (n->elemento == x) { // compara o elemento com a busca
            return true;
        }
        n = n->proximo;
    }
    return false; // percorreu toda a lista sem encontrar o valor
}

#ifdef DEBUG
void imprimir(const Lista* l) {
    if (l == NULL) {
        puts("Lista INVALIDA");
        return;
    }
    if (underflow(l)) {
        puts("Lista VAZIA");
        return;
    }
    Noh* n = l->cabeca;
    printf("[CABECA] ");
    while (n != NULL) {
        printf("%c@%p-->", n->elemento, n);
        n = n->proximo;
    }
    puts(" [CAUDA]");
}
#endif

bool comparar(const Lista* l1, const Lista* l2) {
    // Retorna true se as duas listas NAO existem
    if (l1 == NULL) {
        return l2 == NULL;
    } else if (l2 == NULL) {
        return false;
    }
    // Retorna true se as duas listas estao vazias
    if (underflow(l1)) {
        return underflow(l2);
    } else if (underflow(l2)) {
        return false;
    }
    // Percorre as duas listas ao mesmo tempo, comparando o conteudo de
    // cada noh das mesmas; se houver diferenca OU se encontrar o fim
    // de uma delas antes da outra, as listas nao sao iguais
    Noh* n1 = l1->cabeca;
    Noh* n2 = l2->cabeca;

    while (n1 != NULL && n2 != NULL) {
        if (n1->elemento != n2->elemento) {
            return false; // diferenca encontrada entre dois nohs!
        }
        n1 = n1->proximo;
        n2 = n2->proximo; // avanca nas duas listas simultaneamente
    }
    if (n1 == NULL) {
        return n2 == NULL; // retorna true se chegou ao fim nas DUAS listas
    }
    return false; // saiu do laco por n2 == NULL, mas n1 NAO EH!...
}

