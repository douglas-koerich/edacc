#ifndef FILA_H
#define FILA_H

#include <stdbool.h>
#include <stdlib.h>

struct fila; // definicao opaca (oculta) da estrutura de dados "fila"
typedef struct fila fila;

fila* create(size_t max); // cria nova fila (de inteiros)
void destroy(fila* f); // destroi uma fila

void insert(fila* f, int v); // adicao de novo elemento na fila
int extract(fila* f); // remocao de um elemento da fila

int inspect(const fila* f); // consulta ao elemento do INICIO da fila
size_t size(const fila* f); // retorna o comprimento da fila
bool underflow(const fila* f); // testa se a fila estah vazia

void print(const fila* f); // imprime o conteudo da fila

void save(const fila* f, const char* a); // para salvar a fila num arquivo a
fila* restore(const char* a); // para criar nova fila a partir de um arquivo a

#endif // FILA_H