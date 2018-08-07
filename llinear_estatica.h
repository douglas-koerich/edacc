#ifndef LLINEAR_ESTATICA_H
#define LLINEAR_ESTATICA_H

// Tipo do elemento armazenado na sequencia/lista
struct Elemento {
	unsigned int chave;
	int campo;	// um ou mais campos adicionais quaisquer
};
typedef struct Elemento TipoElemento;

// Definicao do TAD: lista linear alocada estaticamente
struct ListaEstatica {
	TipoElemento* sequencia;	// vetor alocado estaticamente na criacao
	unsigned num_elementos;		// quantos elementos estao na lista
	unsigned max_elementos;		// numero maximo de elementos
};
typedef struct ListaEstatica ListaEstatica;

// Operacoes permitidas/validas para o TAD (lista linear estatica)
ListaEstatica iniciaLista(unsigned max);	// aloc. dinamica do vetor
void finalizaLista(ListaEstatica* lista);	// liberacao do vetor (free)
void imprimir(const ListaEstatica* lista);
TipoElemento* busca(const ListaEstatica* lista, unsigned int chave);	// onde esta o elemento "chave"
int inserir(ListaEstatica* lista, TipoElemento novo);	// copia novo para dentro da lista
void remover(ListaEstatica* lista, unsigned int chave);		// tira elemento "chave" da lista

#endif 

