#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>
#include <stdlib.h>

enum side {
    FRONT,  // extremidade de inicio do deque
    REAR    // extremidade de fim do deque
};
typedef enum side side;

struct deque; // definicao opaca (oculta) da estrutura de dados "deque"
typedef struct deque deque;

deque* d_create(size_t max); // cria novo deque (de inteiros)
void d_destroy(deque* d); // destroi um deque

void d_insert(deque* d, int v, side s); // adicao de novo elemento no deque na
                                        // extremidade indicada
int d_extract(deque* d, side s); // remocao de um elemento do deque
                                 // na extremidade indicada

int d_inspect(const deque* d, side s); // consulta ao elemento do deque que
                                       // estah na extremidade indicada
size_t d_size(const deque* d); // retorna o comprimento do deque
bool d_underflow(const deque* d); // testa se o deque estah vazia

void d_print(const deque* d); // imprime o conteudo do deque

#endif // DEQUE_H