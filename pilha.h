#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>
#include <stdlib.h>

struct pilha; // definicao opaca (oculta) da estrutura de dados "pilha"
typedef struct pilha pilha;

pilha* create(size_t max); // cria nova pilha (de inteiros)
void destroy(pilha* p); // destroi uma pilha

void push(pilha* p, int v); // adicao de novo elemento na pilha
int pop(pilha* p); // remocao de um elemento da pilha

int top(const pilha* p); // consulta ao elemento do topo da pilha (unico acessivel)
size_t size(const pilha* p); // retorna o comprimento da pilha
bool underflow(const pilha* p); // testa se a pilha estah vazia

void print(const pilha* p); // imprime o conteudo da pilha (para depuracao 

#endif // PILHA_H