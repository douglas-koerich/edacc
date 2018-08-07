/*
 * Definicao do TAD: deque usando um vetor como repositorio dos elementos.
 */

#ifndef _DEQUE_H_
#define _DEQUE_H_

/*
 * Extremidades do deque, onde as operacoes sao permitidas
 */
typedef enum Lado { ESQUERDO, DIREITO } Lado;

/*
 * Estrutura (como fica o TAD na memoria)
 */
typedef struct Deque {
	int* elementos;	/* Exemplo de deque de numeros inteiros */
	size_t tamanho;
	int esq, dir;
} Deque;

/*
 * Operacoes (interface do TAD)
 * Todas as funcoes recebem o endereco (ponteiro) do deque que deve ser
 * manipulado pela funcao
 */
int d_criar(Deque*, size_t);
void d_destruir(Deque*);
int d_cheio(const Deque*);
int d_vazio(const Deque*);
int d_inserir(Deque*, Lado, int);	/* Exemplo (!) para um deque de inteiros */
int d_remover(Deque*, int*);	/* Guarda no endereco (ponteiro) o valor */

/*
 * Nomes convencionais para algumas funcoes acima
 */
#define d_overflow(f) 		d_cheio(f)
#define d_underflow(f)		d_vazio(f)
#define d_enqueue(f, e)		d_inserir(f, e)
#define d_dequeue(f, ev)	d_remover(f, ev)

#endif

