#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>

enum where {
    HEAD,  // operacao no inicio ("cabeca") da lista
    TAIL,  // operacao no fim ("cauda") da lista
    POSN   // operacao na posicao N da lista
};
typedef enum where where;

struct list; // definicao opaca (oculta) da estrutura de dados "list"
typedef struct list list;

list* l_create(void);       // cria nova lista (de inteiros)
void l_destroy(list* l);    // destroi uma lista

void l_insert(list* l, int v, where w, unsigned n); // adicao de novo
                                                    // elemento na lista na
                                                    // posicao indicada (se
                                                    // for POSN, n >= 1)
int l_extract(list* l, where s, unsigned n);    // remocao de um elemento da
                                                // lista na posicao indicada

bool l_search(const list* l, int v); // busca pelo valor na lista
size_t l_size(const list* l); // retorna o comprimento da lista
bool l_underflow(const list* l); // testa se a lista estah vazia

void l_print(const list* l); // imprime o conteudo (valores) da lista

#endif // LISTA_H