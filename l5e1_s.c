#include <stdio.h>
#include <string.h>
#include "l5e1.h"

struct Node_ {
    Record data;
    struct Node_* next;
};
typedef struct Node_ Node;

struct List_ {
    Node* head;
    size_t length;
};

List* create(void) {
    List* new_list = malloc(sizeof(List));
    new_list->head = NULL;
    new_list->length = 0;
    return new_list;
}

void destroy(List* list) {
    while (!underflow(list)) {
        free(discard(list));
    }
    free(list);
}

void insert(List* list, const Record* new_element) {
    Node* new_node = malloc(sizeof(Node));
    memcpy(&new_node->data, new_element, sizeof(Record));
    new_node->next = list->head;
    list->head = new_node;
    ++list->length;
}

Record* discard(List* list) {
    if (underflow(list)) {
        return NULL;
    }
    Record* record = malloc(sizeof(Record));
    Node* head = list->head;
    list->head = head->next;
    memcpy(record, &head->data, sizeof(Record));
    free(head);
    --list->length;
    return record;
}

bool underflow(const List* list) {
    return list->length == 0;
}

size_t size(const List* list) {
    return list->length;
}

void print(const List* list) {
    Node* node = list->head;
    while (node != NULL) {
        //printf("%d@%p->", node->data.key, node);
        printf("%d->", node->data.key);
        node = node->next;
    }
    printf("(null)");
}

void sort(List* list) {
    int i, n = list->length;
    Node* pi;
    for (i = 0, pi = list->head; i < n - 1; ++i, pi = pi->next) {
        Node* pj;
        Node* ps = pi;
        int j;
        for (j = i + 1, pj = pi->next; j < n; ++j, pj = pj->next) {
            if (pj->data.key < ps->data.key) {
                ps = pj;
            }
        }
        swap(&pi->data, &ps->data);
    }
}