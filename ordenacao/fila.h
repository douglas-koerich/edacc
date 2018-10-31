#ifndef _FILA_H_
#define _FILA_H_

#include <stdbool.h>
#include "registro.h" 

struct Fila;
typedef struct Fila Fila;

Fila* cria(void);
void destroi(Fila*);
bool underflow(const Fila*);
bool overflow(const Fila*);
void enqueue(Fila*, const Registro*);
const Registro* dequeue(Fila*); // quem chama 'dequeue' tem que
                                // copiar o conteudo do ponteiro
                                // retornado pela funcao!

#endif

