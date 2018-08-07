#ifndef TAD_DEQUE_H
#define TAD_DEQUE_H

#include <stdbool.h>

enum LadoDeque {
    INICIO, // = 0
    FIM     // = 1
};
typedef enum LadoDeque LadoDeque;

struct DequeInt;
typedef struct DequeInt DequeInt;

DequeInt* cria_deque(void);
void destroi_deque(DequeInt* d);
void imprime_deque(const DequeInt* d);
bool dunderflow(const DequeInt* d);
bool doverflow(const DequeInt* d);
void d_enqueue(DequeInt* d, int n, LadoDeque l);    // indica o lado da operacao
int d_dequeue(DequeInt* d, LadoDeque l);            // idem

#endif
