#ifndef FILAINT_H
#define FILAINT_H

#include <stdbool.h>

struct FilaInt;
typedef struct FilaInt FilaInt;

FilaInt* cria(void);
void destroi(FilaInt*);
bool underflow(const FilaInt*);
bool overflow(const FilaInt*);
void enqueue(FilaInt*, int);
int dequeue(FilaInt*);

// Operacao extra
void print(const FilaInt*);

#endif // FILAINT_H
