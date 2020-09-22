// Implementacao do TAD List usando a abordagem de encadeamento CIRCULAR
// (um link apenas do noh antecessor para o noh sucessor, a cauda tendo como
// proximo noh a cabeca da lista - anel de nohs)

#include <stdio.h>
#include <string.h>
#include "list.h"

struct Node_ {
    Record data;        // informacao armazenada neste noh
    struct Node_* next; // link com o proximo noh na lista (sucessor) 
};
typedef struct Node_ Node;

struct List_ {
    Node* tail; // ponteiro de acesso externo
};

List* create(void) {
    List* new_list = malloc(sizeof(List));
    new_list->tail = NULL;

    return new_list;
}

void destroy(List* list) {
    while (!underflow(list)) {
        int dummy_key = 0;
        discard(list, FRONT, dummy_key);
    }
    free(list);
}

void insert(List* list, const Record* new_element, Where to_where) {
    // Toda insercao comeca com a alocacao de um novo noh na memoria
    Node* new_node = malloc(sizeof(Node));
    memcpy(&new_node->data, new_element, sizeof(Record)); // copia de uma area de memoria para outra

    if (underflow(list)) { // se a lista estiver vazia...
        // ... qualquer opcao de lugar significa inserir no inicio
        to_where = FRONT;
    }

    switch (to_where) {
        // TODO:
        case FRONT: // no inicio
            new_node->next = list->head; // quem eh o primeiro atualmente (se existir), passa a ser
                                         // o proximo deste novo noh-cabeca da lista
            list->head = new_node;
            break;

        case REAR:  // no fim
            new_node->next = NULL;
            Node* node = list->head;
            while (node->next != NULL) { // enquanto nao encontra o ultimo noh da lista...
                // ... vai para o proximo
                node = node->next;
            }
            node->next = new_node;
            break;

        case N_POS: // como N-esimo noh (ou como ultimo se a lista ainda nao tem N nohs)
            break;

        case IN_ORDER:  // em uma posicao relativa as demais chaves ja armazenadas
            break;

        default:    // operacao invalida para a insercao
            free(new_node); // desfaz a alocacao para o noh que nao vai ser mais inserido
            return;
    }
}

Record* discard(List* list, Where from_where, int search_key) {
    if (underflow(list)) {
        return NULL;
    }
    Record* record = malloc(sizeof(Record));

    switch (from_where) {
        case FRONT: {
            // TODO: 
            Node* head = list->head;
            list->head = head->next;
            memcpy(record, &head->data, sizeof(Record));
            free(head);
            break;
        }

        case REAR: {
            // TODO:
            Node* previous = NULL;
            Node* node = list->head;
            while (node->next != NULL) {
                previous = node; // mantem um ponteiro para este noh antes de ir para o proximo
                node = node->next;
            }
            memcpy(record, &node->data, sizeof(Record));
            free(node);
            if (previous != NULL) {
                previous->next = NULL; // marca o penultimo (anterior) como nova cauda da lista
            } else {
                // Se previous eh nulo, entao o noh que foi removido era o primeiro (e unico)
                list->head = NULL; // lista voltou a ficar vazia
            }
            break;
        }

        case N_POS: // se nao houver o N-esimo noh, retorna NULL
            break;

        case KEY:   // se a chave nao for encontrada para remover, retorna NULL
            break;

        default:    // operacao invalida para a remocao
            free(record); // nao vai devolver o registro alocado
            return NULL;
    }
    return record;
}

bool underflow(const List* list) {
    return list->tail == NULL;
}

Record* find(const List* list, int search_key) {
    if (underflow(list)) {
        return NULL;
    }
    Node* node = list->tail;
    do {
        node = node->next;
        if (node->data.key == search_key) {
            return &node->data; // chave encontrada, devolve ponteiro pro seu registro
        }
    } while (node != list->tail);

    return NULL; // chave nao foi encontrada em nenhum noh
}

size_t size(const List* list) {
    if (underflow(list)) {
        return 0;
    }
    size_t counter = 0;
    Node* node = list->tail;
    do {
        node = node->next;
        ++counter;
    } while (node != list->tail);
    return counter;
}

void print(const List* list) {
    if (underflow(list)) {
        return;
    }
    Node* node = list->tail;
    do {
        node = node->next;
        printf("%d@%p->", node->data.key, node);
    } while (node != list->tail);
}
