#ifndef FILA_H_
#define FILA_H_

#include <stdbool.h>
#include <stdlib.h>

// Toda definicao de TAD eh feita de maneira "oculta" para o usuario
// do mesmo
struct Fila; // declaracao opaca da estrutura
typedef struct Fila Fila;

// Seguem os prototipos das funcoes, isto eh, as operacoes definidas
// na interface do TAD
Fila* cria(size_t tamanho); // cria uma nova fila e retorna seu endereco
void destroi(Fila* fila);
void insere(Fila* fila, int elemento); // insere um novo elemento no fim
int retira(Fila* fila); // remove o elemento do inicio
bool underflow(const Fila* fila); // funcao de teste nao altera conteudo

#endif // FILA_H_

