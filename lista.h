#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include "registro.h"

struct lista;
typedef struct lista lista;

lista* cria(void);
void destroi(lista* l);
bool underflow(const lista* l);
void insere_atualiza(lista* l, const registro* r);
registro* busca(const lista* l, unsigned short x);
void imprime(const lista* l);

#endif  // LISTA_H
