#ifndef TAD_FILA_H
#define TAD_FILA_H

#include <stdbool.h>

struct FilaInt;
typedef struct FilaInt FilaInt;

FilaInt* cria_fila(void);
void destroi_fila(FilaInt* f);
void imprime_fila(const FilaInt* f);
bool funderflow(const FilaInt* f);
bool foverflow(const FilaInt* f);
void enqueue(FilaInt* f, int n);
int dequeue(FilaInt* f);

// Nova operacao do TAD cf. pedido do exercicio 8
void inverte(FilaInt* f);

#endif
