#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include "record.h"

// Definicao opaca (encapsulada) do TAD
struct List_;
typedef struct List_ List;

// Enumeracao das posicoes/dos modos de insercao e remocao
enum Where_ {
    FRONT,  // na cabeca (inicio) da lista
    REAR,   // na cauda (fim) da lista
    N_POS,  // na N-esima posicao (1a., 2a., etc.)

    IN_ORDER,   // (apenas para insercao) em qualquer posicao, desde que em ordem
                // com as outras chaves

    KEY     // (apenas para remocao) operacao sobre um registro especificado pela chave
};
typedef enum Where_ Where;

// Operacoes com o TAD: Lista Linear (de registros)
List* create(void);
void destroy(List* list);
void insert(List* list, const Record* new_element, Where to_where);
Record* discard(List* list, Where from_where, int search_key); // usa 'search_key' se 'from_where'=KEY
                                                               // quem recebe deve chamar free() para o ponteiro devolvido
bool underflow(const List* list);
Record* find(const List* list, int search_key); 
size_t size(const List* list);
void print(const List* list); // vai imprimir apenas a chave de cada noh

#endif  // LIST_H