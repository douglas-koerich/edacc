// Implementacao do TAD List usando a abordagem de encadeamento SIMPLES
// (um link apenas do noh antecessor para o noh sucessor)

#include <stdio.h>
#include <string.h>
#include "list.h"

struct Node_ {
    Record data;        // informacao armazenada neste noh
    struct Node_* next; // link com o proximo noh na lista (sucessor) 
};
typedef struct Node_ Node;

struct List_ {
    Node* head; // ponteiro de acesso externo
};

/*
OBS.: No livro do PEREIRA (e em outros tambem), o tipo List_ acima
eh definido de outra forma, assim:
typedef Node* List; // uma "lista" eh um ponteiro para um noh (o primeiro)
*/

List* create(void) {
    List* new_list = malloc(sizeof(List));
    new_list->head = NULL; // a lista ainda estah vazia (nao existe um primeiro noh)

    return new_list;
}

void destroy(List* list) {
    // Precisa remover todos os nohs alocados na memoria antes!...
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
    }
}

Record* discard(List* list, Where from_where, int search_key) {
    if (underflow(list)) {
        return NULL;
    }
    Record* record = malloc(sizeof(Record));

    switch (from_where) {
        case FRONT: {
            Node* head = list->head;
            list->head = head->next;
            memcpy(record, &head->data, sizeof(Record));
            free(head);
            break;
        }

        case REAR: {
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
    /*
    if (list->head == NULL) {
        return true;
    } else {
        return false;
    }
    */
    return list->head == NULL;
}

Record* find(const List* list, int search_key) {
    Node* node = list->head;
    while (node != NULL) { // enquanto houver um noh para comparar...
        if (node->data.key == search_key) {
            return &node->data; // chave encontrada, devolve ponteiro pro seu registro
        }
        node = node->next;
    }
    return NULL; // chave nao foi encontrada em nenhum noh
}

size_t size(const List* list) {
    size_t counter = 0;
    Node* node = list->head;
    while (node != NULL) { // enquanto houver um noh para contar...
        ++counter;
        node = node->next;
    }
    return counter;
}

void print(const List* list) {
    Node* node = list->head;
    while (node != NULL) {
        printf("%d@%p->", node->data.key, node);
        node = node->next;
    }
}
