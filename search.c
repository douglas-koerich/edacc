#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "search.h"

/*
algoritmo busca_sequencial(v, n, k)
  entrada Vetor v de n elementos, e uma chave k
  saida Indice da chave k no vetor v, ou invalido

        (M)   (R)    (M+A) -----------> 1 + (n+1) + 2n
  para i de 1 ateh n passo 1 faca
        (D)(D)   (R) -----------------> 3n
    se v[i].chave = k entao
        (M) --------------------------> 1 (*)
      retorna i
    fim-se
  fim-para
    (M) ------------------------------> 1 (**)
  retorna INV

  Duas situacoes de PIOR caso:
  (*)  A chave eh encontrada na ultima posicao
  (**) A chave nao eh encontrada

  T(n) = 6n + 3 (funcao de complexidade)
  O(n) - linear (ordem de complexidade)
*/

int sequential(const Record* v, size_t n, int k) {
    int i;
    for (i = 0; i < n; ++i) {
        if (v[i].key == k) {
            return i; // retorna indice onde encontrou a chave
        }
    }
    return -1; // indice INVALIDO (chave nao encontrada)
}

int binary(const Record* v, int l, int r, int k) {
    if (l > r) {
        return -1; // pela divisao sucessiva (e recursiva) do vetor, chegou-se a um segmento nulo
    }
    int m = (l + r) / 2; // busca binaria sempre avalia (compara) o elemento do meio do segmento
    if (v[m].key == k) {
        return m;
    }
    if (k < v[m].key) {
        return binary(v, l, m - 1, k);
    } else {
        return binary(v, m + 1, r, k);
    }
}

/*
algoritmo busca_binaria(v, l, r, k)
  entrada Segmento do vetor v do indice l ao indice r, e a chave k
  saida Indice onde a chave foi encontrada, ou INVALIDO

      (R) ----------------------------------> 1
  se l > r entao
      (M) ----------------------------------> 1 (**)
    retorna INV
  fim-se
    (M)  (A)  (A) --------------------------> 3
  m <- (l + r) / 2
      (D) (D)  (R) -------------------------> 3
  se v[m].chave = k entao
      (M) ----------------------------------> 1 (*)
    retorna m
  fim-se
      (R) (D)(D) ---------------------------> 3
  se k < v[m].chave entao
                T(n/2)             (A) -----> T(n/2) + 1
    retorna busca_binaria(v, l, m - 1, k)
  senao
                T(n/2)          (A) --------> T(n/2) + 1 (nao conta porque eh mutuamente exclusiva com acima)
    retorna busca_binaria(v, m + 1, r, k) 

  T(n) = 8          , se n = 1
       = T(n/2) + 11, se n > 1

  T(n) = T(n/2) + 11
       = T(n/4) + 11 + 11
       = T(n/8) + 11 + 11 + 11
       = ...
       = T(n/2^i) + i.11

  Para resolver a equacao, queremos que T(n/2^i) = T(1) = 8, cf. acima. Entao
    n/2^i = 1 --> i = log2(n) = lg(n)

  T(n) = 11.lg(n) + 8
  O(lg(n)) -> logaritmica
*/

int interpolation(const Record* v, int l, int r, int k) {
    if (l > r) {
        return -1;
    }
    /* Calculo de p considera a proporcionalidade entre as "distancias" entre chaves
     * e entre indices:
     * "A distancia de p para l (p - l) estah para a distancia entre k e a chave em l (dlk),
     * "ASSIM COMO
     * "a distancia de r para l (dlr) estah para a distancia entre a chave em r e a chave em l (dklkr)."
     */
    int p = l;
    float dlr = r - l, dklkr = v[r].key - v[l].key, dlk = k - v[l].key;
    if (dklkr > 0.0) { // as chaves nos extremos sao iguais (ou reduziu-se a um tamanho unitario)
        p = dlk * dlr / dklkr + l; // aplicacao da solucao "regra de 3"
    }
    if (v[p].key == k) {
        return p;
    }
    if (k < v[p].key) {
        return interpolation(v, l, p - 1, k);
    } else {
        return interpolation(v, p + 1, r, k);
    }
}

/******************************************************************************/
/* IMPLEMENTACAO DO TAD "Dictionary" (TABELA DE DISPERSAO/ESPALHAMENTO)       */
/******************************************************************************/

// Utiliza a estrategia de encadeamento exterior (com lista encadeada) para o
// tratamento de colisao de chaves sinonimas
struct Node_ {
    Record data;
    struct Node_* next;
};
typedef struct Node_ Node;

struct List_ {
    Node* head;
};
typedef struct List_ List;

// Enumeracao das posicoes/dos modos de insercao e remocao na lista encadeada
enum Where_ {
    FRONT,  // na cabeca (inicio) da lista
    REAR,   // na cauda (fim) da lista
    KEY     // (apenas para remocao) operacao sobre um registro especificado pela chave
};
typedef enum Where_ Where;

struct Dictionary_ {
    List* vector; // vetor de listas encadeadas
    size_t size;
};

static bool underflow(const List* list) {
    return list->head == NULL;
}

static void l_insert(List* list, const Record* new_element) {
    Node* new_node = malloc(sizeof(Node));
    memcpy(&new_node->data, new_element, sizeof(Record));

    if (underflow(list)) {
        new_node->next = list->head;
        list->head = new_node;
        return;
    }
    new_node->next = NULL;
    Node* node = list->head;
    while (node->next != NULL && node->data.key != new_element->key) {
        node = node->next;
    }
    if (node->data.key == new_element->key) { // a chave jah existia na lista?
        memcpy(&node->data, new_element, sizeof(Record));
        free(new_node); // nao foi necessario criar um novo noh
    } else {
        node->next = new_node;
    }
}

static Record* l_discard(List* list, Where from_where, int search_key) {
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

        case KEY: {
            Node* previous = NULL;
            Node* node = list->head;
            while (node != NULL && node->data.key != search_key) {
                previous = node;
                node = node->next;
            }
            if (node == NULL) {
                return NULL;
            }
            memcpy(record, &node->data, sizeof(Record));
            if (previous != NULL) {
                previous->next = node->next;
            } else {
                list->head = node->next;
            }
            free(node);
            break;
        }

        default:
            free(record);
            return NULL;
    }
    return record;
}

static Record* l_find(const List* list, int search_key) {
    Node* node = list->head;
    while (node != NULL) {
        if (node->data.key == search_key) {
            return &node->data;
        }
        node = node->next;
    }
    return NULL;
}

static size_t size(const List* list) {
    size_t counter = 0;
    Node* node = list->head;
    while (node != NULL) {
        ++counter;
        node = node->next;
    }
    return counter;
}

static void l_print(const List* list) {
    Node* node = list->head;
    while (node != NULL) {
        printf("%d,%c->", node->data.key, node->data.value);
        node = node->next;
    }
}

Dictionary* create(size_t max_elements) {
    Dictionary* new_dict = malloc(sizeof(Dictionary));
    new_dict->size = max_elements;
    new_dict->vector = calloc(max_elements, sizeof(List)); // calloc() zera a memoria alocada
    return new_dict;
}

void destroy(Dictionary* dictionary) {
    int i;
    for (i = 0; i < dictionary->size; ++i) {
        while (!underflow(&dictionary->vector[i])) {
            int dummy_key = 0;
            free(l_discard(&dictionary->vector[i], FRONT, 0));
        }
    }
    free(dictionary->vector);
    free(dictionary);
}

static int hashing(int key, size_t size) {
    int position;

    /*
    // Metodo da divisao
    position = key % size;
    */

    // Metodo pseudo-aleatorio
    srand(key); // usa a chave como semente
    position = rand() % size;

    return position;
}

void insert(Dictionary* dictionary, const Record* new_element) {
    int index = hashing(new_element->key, dictionary->size);
    l_insert(&dictionary->vector[index], new_element);
}

Record* discard(Dictionary* dictionary, int search_key) {
    int index = hashing(search_key, dictionary->size);
    return l_discard(&dictionary->vector[index], KEY, search_key);
}

Record* find(const Dictionary* dictionary, int search_key) {
    int index = hashing(search_key, dictionary->size);
    return l_find(&dictionary->vector[index], search_key);
}

void print(const Dictionary* dictionary) {
    int i;
    for (i = 0; i < dictionary->size; ++i) {
        if (underflow(&dictionary->vector[i])) {
            puts("(vazio)");
        } else {
            l_print(&dictionary->vector[i]);
            putchar('\n');
        }
    }
}