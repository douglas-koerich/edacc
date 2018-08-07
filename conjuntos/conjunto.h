#ifndef CONJUNTO_H
#define CONJUNTO_H

#include <stdbool.h>

struct Conjunto;
typedef struct Conjunto Conjunto;

Conjunto* inicializa(void);
void finaliza(Conjunto* C);
void imprime(const Conjunto* C);
bool vazio(const Conjunto* C);
void adiciona(Conjunto* C, const void* c, void (*imprime)(void*));
void remover(Conjunto* C, const void* c, bool (*compara)(void*, void*));
bool pertence(const Conjunto* C, const void* c, bool (*compara)(void*, void*));
bool contido(const Conjunto* A, const Conjunto* B);
bool proprio(const Conjunto* A, const Conjunto* B);
bool igual(const Conjunto* A, const Conjunto* B);
bool contem(const Conjunto* A, const Conjunto* B);
Conjunto* uniao(const Conjunto* A, const Conjunto* B);
Conjunto* interseccao(const Conjunto* A, const Conjunto* B);
Conjunto* diferenca(const Conjunto* A, const Conjunto* B);
Conjunto* diferenca_simetrica(const Conjunto* A, const Conjunto* B);
Conjunto* produto_cartesiano(const Conjunto* A, const Conjunto* B);

#endif // CONJUNTO_H
