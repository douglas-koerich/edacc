/*
 * Definicao do TAD: lista encadeada (original e algumas variacoes).
 */

#ifndef _LISTA_H_
#define _LISTA_H_

/*
 * Estrutura (como fica o TAD na memoria)
 */
typedef struct No {		/* No de lista encadeada simples */
	int elemento;		/* Exemplo de fila de numeros inteiros */
	struct No* proximo;
} No;

typedef struct DNo {	/* No de lista encadeada dupla */
	int elemento;
	struct DNo *proximo, *anterior;
} DNo;

typedef struct Cabecalho {
	size_t tamanho;		/* Exemplo de no-cabecalho p/ gerencia da lista */
	No* cabeca;
} Cabecalho;

typedef No* Lista;			/* Lista encadeada simples */
typedef Cabecalho ListaH;	/* Lista encadeada com cabecalho */
typedef Lista ListaC;		/* Lista encadeada circular */
typedef DNo* ListaD;		/* Lista encadeada dupla */

/*
 * Operacoes (interface do TAD)
 * Todas as funcoes recebem o endereco (ponteiro) da lista que deve ser
 * manipulada pela funcao
 */
void ls_criar(Lista*);
void ls_destruir(Lista*);
No* ls_buscar(Lista, int);	/* Exemplo para uma lista de inteiros */
int ls_insInicio(Lista*, int);
int ls_insFim(Lista*, int);
int ls_remInicio(Lista*, int*);
int ls_remFim(Lista*, int*);

void lh_criar(ListaH*);
void lh_destruir(ListaH*);
No* lh_buscar(const ListaH*, int);	/* Exemplo para uma lista de inteiros */
int lh_insInicio(ListaH*, int);
int lh_insFim(ListaH*, int);
int lh_remInicio(ListaH*, int*);
int lh_remFim(ListaH*, int*);

void lc_criar(ListaC*);
void lc_destruir(ListaC*);
No* lc_buscar(ListaC, int);	/* Exemplo para uma lista de inteiros */
int lc_insInicio(ListaC*, int);
int lc_insFim(ListaC*, int);
int lc_remInicio(ListaC*, int*);
int lc_remFim(ListaC*, int*);

void ld_criar(ListaD*);
void ld_destruir(ListaD*);
DNo* ld_buscar(ListaD, int);	/* Exemplo para uma lista de inteiros */
int ld_insInicio(ListaD*, int);
int ld_insFim(ListaD*, int);
int ld_remInicio(ListaD*, int*);
int ld_remFim(ListaD*, int*);

#endif

