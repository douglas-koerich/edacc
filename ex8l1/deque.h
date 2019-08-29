#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>

struct Deque;
typedef struct Deque Deque;

/* Se enqueue/dequeue recebessem um 'int' pra indicar o lado da operacao
#define INICIO 0
#define FIM    1
*/
enum Extremidade { // 'enum' eh um tipo /inteiro/ com "nomes" pre-definidos
                   // para seus valores
    INICIO,        // se nao for especificado (= valor), o primeiro nome eh 0
    FIM            // os nomes seguintes incrementam o valor (nesse caso, FIM=1)
};
typedef enum Extremidade Extremidade; // pra nao ter que usar 'enum' no tipo

Deque* cria(void);
void destroi(Deque*);
bool underflow(const Deque*);
bool enqueue(Deque*, char, Extremidade);  // enqueue no INICIO ou no FIM
bool dequeue(Deque*, char*, Extremidade); // dequeue do INICIO ou do FIM

// EXTRA
bool overflow(const Deque*);
#ifdef DEBUG
void imprime(const Deque*);
#endif

#endif // DEQUE_H
