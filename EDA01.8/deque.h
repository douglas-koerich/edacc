#ifndef _DEQUE_H_
#define _DEQUE_H_

#include <stdbool.h>

struct Deque;
typedef struct Deque Deque;

enum Extremo { FRENTE, TRAS };
typedef enum Extremo Extremo;

Deque* cria(void);
void destroi(Deque*);
void imprime(const Deque*); 
bool underflow(const Deque*);
bool overflow(const Deque*);
void enqueue(Deque*, int, Extremo);
int dequeue(Deque*, Extremo);

#endif

