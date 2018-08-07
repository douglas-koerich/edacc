#ifndef PILHACHAR_H
#define PILHACHAR_H

#include <stdbool.h>

struct PilhaChar;
typedef struct PilhaChar PilhaChar;

PilhaChar* cria(void);
void destroi(PilhaChar*);
bool underflow(const PilhaChar*);
bool overflow(const PilhaChar*);
void push(PilhaChar*, char);
char pop(PilhaChar*);

#endif // PILHACHAR_H
