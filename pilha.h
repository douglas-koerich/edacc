#ifndef PILHA_H_
#define PILHA_H_

#include <stdbool.h>
#include <stdlib.h>

// Toda definicao de TAD eh feita de maneira "oculta" para o usuario
// do mesmo
struct Pilha; // declaracao opaca da estrutura
typedef struct Pilha Pilha;

// Seguem os prototipos das funcoes, isto eh, as operacoes definidas
// na interface do TAD
Pilha* cria(size_t tamanho); // cria uma nova pilha e retorna seu endereco
void destroi(Pilha* pilha);
void push(Pilha* pilha, int elemento); // insere um novo elemento no topo
int pop(Pilha* pilha); // remove o elemento do topo
bool underflow(const Pilha* pilha); // funcao de teste nao altera conteudo

#endif // PILHA_H_

