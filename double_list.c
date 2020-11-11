// Implementacao do TAD List usando a abordagem de encadeamento DUPLO
// (um link do noh antecessor para o noh sucessor, e outro no sentido inverso)

#include <stdio.h>
#include <string.h>
#include "list.h"

struct Node_ {
    Record data;            // informacao armazenada neste noh
    struct Node_* next;     // link com o proximo noh na lista (sucessor)
    struct Node_* previous; // link com o noh anterior da lista (antecessor)
};
typedef struct Node_ Node;

struct List_ {
    Node* head; // ponteiro de acesso externo, para o inicio (cabeca) da lista
    Node* tail; // novo ponteiro de acesso, para o fim (cauda) da lista
    size_t size; // indicacao do tamanho da lista
};

List* create(void) {
    List* new_list = malloc(sizeof(List));
    new_list->head = new_list->tail = NULL; // a lista ainda estah vazia
    new_list->size = 0;
    return new_list;
}

void destroy(List* list) {
    // Precisa remover todos os nohs alocados na memoria antes!...
    while (!underflow(list)) {
        int dummy_key = 0;
        free(discard(list, FRONT, dummy_key));
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

    // Incrementa o contador interno do numero de nohs/elementos
    ++list->size;

    switch (to_where) {
        case FRONT: // no inicio
            new_node->next = list->head; // quem eh o primeiro atualmente (se existir), passa a ser
                                         // o proximo deste novo noh-cabeca da lista
            new_node->previous = NULL;
            if (new_node->next) { // existe um noh seguinte (agora passando a ser o segundo da lista)?
                Node* second = new_node->next;
                second->previous = new_node; // ele deve ter o novo noh como antecessor (era NULL)
            } else { // nao existe um noh seguinte, este eh o primeiro...
                // ... e tambem o ultimo (por enquanto)!
                list->tail = new_node;
            }
            list->head = new_node;
            break;

        case REAR:  // no fim
            new_node->next = NULL;
            Node* last = list->tail;
            last->next = new_node;
            new_node->previous = last;
            list->tail = new_node;
            break;

        case N_POS: // como N-esimo noh (ou como ultimo se a lista ainda nao tem N nohs)
            break;

        case IN_ORDER:  // em uma posicao relativa as demais chaves ja armazenadas
            break;

        default:    // operacao invalida para a insercao
            free(new_node); // desfaz a alocacao para o noh que nao vai ser mais inserido
            --list->size; // desfaz tambem o incremento do numero de nohs
    }
}

Record* discard(List* list, Where from_where, int search_key) {
    if (underflow(list)) {
        return NULL;
    }
    Record* record = malloc(sizeof(Record));

    // Decrementa o contador interno do numero de nohs
    --list->size;

    switch (from_where) {
        case FRONT: {
            Node* head = list->head;
            list->head = head->next;
            if (head->next) { // se existe um segundo noh que vai se tornar o primeiro...
                // ... anula o ponteiro para o antecessor dele
                Node* second = head->next;
                second->previous = NULL;
            } else { // se nao existe um segundo noh, entao o primeiro eh (era) o ultimo...
                // ... entao precisa anular o ponteiro da cauda
                list->tail = NULL;
            }
            memcpy(record, &head->data, sizeof(Record));
            free(head);
            break;
        }

        case REAR: {
            Node* tail = list->tail;
            list->tail = tail->previous;
            if (tail->previous) { // se existe um penultimo noh que vai se tornar o ultimo...
                // ... anula o ponteiro para o seu sucessor
                Node* before_last = tail->previous;
                before_last->next = NULL;
            } else { // se nao existe um penultimo, entao o ultimo eh (era) o primeiro...
                // ... entao precisa anular o ponteiro da cabeca
                list->head = NULL;
            }
            memcpy(record, &tail->data, sizeof(Record));
            free(tail);
            break;
        }

        case N_POS: // se nao houver o N-esimo noh, retorna NULL
            break;

        case KEY:   // se a chave nao for encontrada para remover, retorna NULL
            break;

        default:    // operacao invalida para a remocao
            free(record); // nao vai devolver o registro alocado
            ++list->size; // desfaz o decremento no tamanho da lista
            return NULL;
    }
    return record;
}

bool underflow(const List* list) {
    return list->size == 0;
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
    return list->size;
}

void print(const List* list) {
    Node* node = list->head;
    while (node != NULL) {
        printf("<-%d@%p->", node->data.key, node);
        node = node->next;
    }
}
