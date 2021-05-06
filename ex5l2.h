#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>

struct lista;
typedef struct lista Lista;

Lista* create(void);
void destroy(Lista*);
bool underflow(const Lista*);
void print(const Lista*);
void insert(Lista*, int);
int extract(Lista*);

// Objeto do exercicio
void delete_range(Lista*, int, int);

#endif