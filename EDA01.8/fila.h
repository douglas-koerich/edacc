#ifndef _FILA_H_
#define _FILA_H_

#include <stdbool.h>

struct Fila;
typedef struct Fila Fila;

Fila* criaf(void);
void destroif(Fila*);
void imprimef(const Fila*);
bool underflowf(const Fila*);
bool overflowf(const Fila*);
void enqueuef(Fila*, int);
int dequeuef(Fila*);

#endif

