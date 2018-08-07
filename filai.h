#ifndef FILAI_H
#define FILAI_H

#include <stdbool.h>

struct FilaI;

struct FilaI* cria(void);
void destroi(struct FilaI*);
bool underflow(const struct FilaI*);
void enqueue(struct FilaI*, int);
int dequeue(struct FilaI*);

#endif

