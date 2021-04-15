#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>
#include <stdlib.h>
#include "elemento.h"

/*
#define INICIO 0
#define FIM 1
*/
enum lado { // Definicao do "tipo" lado
    INICIO, // padrao eh assumir o valor 0
    FIM     // assume o valor seguinte (1)
};
typedef enum lado Lado;

struct deque;
typedef struct deque Deque;

void d_enqueue(Deque*, TipoElemento, Lado);
TipoElemento d_dequeue(Deque*, Lado);
TipoElemento d_front(const Deque*);
TipoElemento d_rear(const Deque*);
size_t d_size(const Deque*);
bool d_underflow(const Deque*);

Deque* d_create(void);
void d_destroy(Deque*);
void d_print(const Deque*);

#endif // DEQUE_H