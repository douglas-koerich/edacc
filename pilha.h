/*
 * Definicao do TAD: pilha usando um vetor como repositorio dos elementos.
 */

#ifndef _PILHA_H_
#define _PILHA_H_

/*
 * Estrutura (como fica o TAD na memoria)
 */
typedef struct Pilha {
	int* elementos;	/* Exemplo para uma pilha de numeros inteiros */
	size_t tamanho;
	int topo;
} Pilha;

/*
 * Operacoes (interface do TAD)
 * Todas as funcoes recebem o endereco (ponteiro) da pilha que deve ser
 * manipulada pela funcao
 */
int p_criar(Pilha*, size_t);
void p_destruir(Pilha*);
int p_cheia(const Pilha*);
int p_vazia(const Pilha*);
int p_inserir(Pilha*, int);		/* Exemplo (!) para uma pilha de inteiros */
int p_remover(Pilha*, int*);	/* Guarda no endereco (ponteiro) o valor */

/*
 * Nomes convencionais para algumas funcoes acima
 */
#define p_overflow(p) 	p_cheia(p)
#define p_underflow(p)	p_vazia(p)
#define push(p, v)		p_inserir(p, v)
#define pop(p, ev)		p_remover(p, ev)

#endif

