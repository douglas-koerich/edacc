#ifndef EXERC1_LISTA_H
#define EXERC1_LISTA_H

#include <stdbool.h>

// O noh da lista de inteiros
struct inteiro {
	int numero;
	struct inteiro* proximo;
};
typedef struct inteiro NohLista;

// Um ponteiro para o noh vai ser usado para apontar
// para o primeiro noh da lista, ou seja, para ela (a lista)
// Entao, vamos apelidar esse ponteiro de noh como "lista"
typedef NohLista* Lista;

// Operacoes do TAD: lista encadeada
void inicia(Lista* l);		// vai receber o endereco inicial da lista
void finaliza(Lista* l);	// obrigatorio ter por causa da aloc. dinamica
void insInicio(Lista* l, int novo);
void insFim(Lista* l, int novo);
bool remInicio(Lista* l, int* removido);
bool remFim(Lista* l, int* removido);
bool underflow(Lista* l);	// como nao altera, poderia ser underflow(Lista l);

#endif

