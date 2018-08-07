/*
 * Definicao do TAD: fila usando um vetor como repositorio dos elementos.
 */

#ifndef _FILA_H_
#define _FILA_H_

/*
 * Estrutura (como fica o TAD na memoria)
 */
typedef struct Fila {
	int* elementos;	/* Exemplo de fila de numeros inteiros */
	size_t tamanho;
	int inicio, fim;
} Fila;

/*
 * Operacoes (interface do TAD)
 * Todas as funcoes recebem o endereco (ponteiro) da fila que deve ser
 * manipulada pela funcao
 */
int f_criar(Fila*, size_t);
void f_destruir(Fila*);
int f_cheia(const Fila*);
int f_vazia(const Fila*);
int f_inserir(Fila*, int);	/* Exemplo (!) para uma fila de inteiros */
int f_remover(Fila*, int*);	/* Guarda no endereco (ponteiro) o valor */

/*
 * Nomes convencionais para algumas funcoes acima
 */
#define f_overflow(f) 	f_cheia(f)
#define f_underflow(f)	f_vazia(f)
#define enqueue(f, e)	f_inserir(f, e)
#define dequeue(f, ev)	f_remover(f, ev)

#endif

