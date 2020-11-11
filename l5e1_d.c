#include <stdio.h>
#include <string.h>
#include "l5e1.h"

struct Node_ {
    Record data;
    struct Node_* next;
    struct Node_* previous;
};
typedef struct Node_ Node;

struct List_ {
    Node* head;
    Node* tail;
    size_t length;
};

List* create(void) {
    List* new_list = malloc(sizeof(List));
    new_list->head = new_list->tail = NULL;
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
    ++list->length;
    new_node->next = list->head;
    new_node->previous = NULL;
    if (new_node->next) {
        Node* second = new_node->next;
        second->previous = new_node;
    } else {
        list->tail = new_node;
    }
    list->head = new_node;
}

Record* discard(List* list) {
    if (underflow(list)) {
        return NULL;
    }
    Record* record = malloc(sizeof(Record));
    --list->length;
    Node* head = list->head;
    list->head = head->next;
    if (head->next) {
        Node* second = head->next;
        second->previous = NULL;
    } else {
        list->tail = NULL;
    }
    memcpy(record, &head->data, sizeof(Record));
    free(head);
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
    printf("(null)");
    while (node != NULL) {
        printf("<-%d@%p->", node->data.key, node);
        //printf("<-%d->", node->data.key);
        node = node->next;
    }
    printf("(null)");
}

static bool terminal(const Node* left, const Node* right) {
    if (left == NULL || right == NULL) {
        return true;
    }
    const Node* node = left;
    while (node != NULL) {
        node = node->previous;
        if (node == right) {
            return true;
        }
    }
    return false;    
}

static void sort_r(Node* left, Node* right) {
    if (terminal(left, right)) {
        return;
    }
    int ref = left->data.key; // escolhe como pivo a chave de uma das pontas
    Node* i = left;
    Node* j = right;
    while (!terminal(i, j)) {
        while (i->data.key < ref) i = i->next;
        while (j->data.key > ref) j = j->previous;
        if (!terminal(i, j)) {
            swap(&i->data, &j->data);
            i = i->next, j = j->previous;
        }
    }
    sort_r(left, j);
    sort_r(i, right);
}

void sort(List* list) {
    sort_r(list->head, list->tail);
}