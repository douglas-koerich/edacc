#ifndef LDUPLA_H
#define LDUPLA_H

#include <stdbool.h>

struct Lista;

struct Lista* cria(void);
void destroi(struct Lista*);
void imprime(struct Lista*);
bool insFim(struct Lista*, int);

bool insAntes(struct Lista*, int, int);
bool insDepois(struct Lista*, int, int);

#endif
