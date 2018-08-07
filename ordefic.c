#include <stdbool.h>
#include <stdlib.h>		// malloc() / free()
#include <string.h>		// memcpy()
#include "registro.h"
#include "ordenacao.h"

void shell(Registro a[], size_t n) {
	// Cria a sequencia de incrementos (k's) cf. Shell
	int serie[20], j = 0, k = 1;
	while (k < n) {
		serie[j++] = k;
		k = 3*k + 1;
	}
	// Ao final do laco, k > n; esse eh o k_j, entao o ultimo que
	// foi armazenado no laco era o k_(j-1); o indice 'j' estah apontando
	// para a posicao do k_j que nao foi gerado, portanto temos que voltar
	// duas posicoes no vetor
	j -= 2;
	while (j >= 0) {	// enquanto tiver um incremento menor a ser usado
		// Para cada segmento ("sub-vetor"), faz a ordenacao dele pelo
		// algoritmo de insercao
		int i;
		k = serie[j];	// incremento da vez
		for (i=0; i<k; ++i) {
			int d;	// indice do primeiro elemento ainda nao ordenado
			for (d=i+k; d<n; d+=k) {
				int o = d-k; // indice dos elementos que ja foram ordenados
				Registro backup = a[d];
				while (o >= i && a[o].chave > backup.chave) {
					a[o+k] = a[o];	// desloca o maior para a posicao da direita
					--o;
				}
				a[o+k] = backup;
			}
		}
		// Usa o incremento anterior na serie (decrescente)
		--j;
	}
}

/******************************************************************************
 * Definicao do TAD auxiliar: fila de registros, usado pelo algoritmo radixsort
 */

// No da fila na forma encadeada
struct No {
	Registro elemento;
	struct No* proximo;
	struct No* anterior;
};
typedef struct No No;

struct Fila {
	No* inicio;
	No* fim;
};

static struct Fila* criar(void) {
	struct Fila* f = (struct Fila*) malloc(sizeof(struct Fila));
	f->inicio = f->fim = NULL;
	return f;
}

static void destruir(struct Fila* f) {
	while (f->inicio != NULL) {
		No* p = f->inicio;
		f->inicio = p->proximo;
		free(p);
	}
	free(f);
}

static bool underflow(struct Fila* f) {
	return f->inicio == NULL;
}

static bool enqueue(struct Fila* f, const Registro* reg) {
	No* p = (No*) malloc(sizeof(No));
	p->proximo = NULL;
	p->anterior = f->fim;
	memcpy(&p->elemento, reg, sizeof(Registro));
	if (f->fim != NULL) {
		(f->fim)->proximo = p;	// f->fim eh o ultimo noh atual, que deve passar
								// a apontar para o NOVO ultimo noh (criado)
	}
	if (f->inicio == NULL) {	// fila estava vazia antes desse novo elemento?
		f->inicio = p;			// entao o novo noh eh inicio e fim ao mesmo tempo
	}
	f->fim = p;
	return true;
}

static bool dequeue(struct Fila* f, Registro* reg) {
	if (underflow(f)) {
		return false;
	}
	No* p = f->inicio;		// salva o ponteiro para o primeiro noh que sera removido
	f->inicio = p->proximo;	// novo inicio sera o proximo (segundo) noh
	if (f->inicio != NULL) {	// existe de fato esse segundo noh (nao salvou NULL)?
		f->inicio->anterior = NULL;
	}
	else {	// fila ficou vazia, marca isso tambem no ponteiro para o ultimo
		f->fim = NULL;
	}
	memcpy(reg, &p->elemento, sizeof(Registro));
	free(p);
	return true;
}

/*
 * Fim do TAD
 *****************************************************************************/

void radix(Registro a[], size_t n) {
	// Como a chave eh um 'int' e esse valor tem, no maximo, 9 digitos
	// (max = 2 bilhoes e ...), vamos limitar a varredura de "casas" decimais
	// no algoritmo
	const MAX_DIGITOS_CHAVE = 9;
	int dig, peso;
	for (dig = peso = 1 /* "casa" das unidades da chave */;
		 dig <= MAX_DIGITOS_CHAVE; ++dig, peso *= 10) {	// cada digito tem peso x 10
		// Criamos 10 filas, uma para cada digito
		struct Fila* aux[10];
		int f;
		for (f=0; f<10; ++f) {
			aux[f] = criar();
		}
		// Varre todos os elementos do banco de dados/vetor, determinando o valor
		// do digito na posicao atual de interesse
		int i, digito;
		for (i=0; i<n; ++i) {
			digito = (a[i].chave / peso) % 10;	// extrai o digito

			// Armazena o registro na fila correspondente ao digito determinado
			enqueue(aux[digito], a+i);
		}
		// Agora que todos os registros foram separados por seus digitos nas filas
		// correspondentes, recupero fila por fila (desde a 0 ateh a 9) para o vetor
		for (i=f=0; f<10; ++f) {
			while (!underflow(aux[f])) {
				dequeue(aux[f], a+i);
				++i;
			}
		}
		// Remove filas auxiliares da memoria
		for (f=0; f<10; ++f) {
			destruir(aux[f]);
		}
	}
}

static void intercala(Registro a[], int inf, int meio, int sup) {
	// Onde vamos colocar os valores/registros ordenados temporariamente
	int tamanho = sup-inf+1;
	Registro* r = (Registro*) malloc(sizeof(Registro)*tamanho);

	// Indices de percurso nas 'metades'
	int rasc=0, esq=inf, dir=meio+1;

	// Enquanto as duas 'metades' ainda deve ser percorridas
	while (esq <= meio && dir <= sup) {
		if (a[esq].chave < a[dir].chave) {
			memcpy(r+rasc, a+esq, sizeof(Registro));
			++esq;
		}
		else {
			memcpy(r+rasc, a+dir, sizeof(Registro));
			++dir;
		}
		++rasc;
	}
	// Continua copiando para rascunho o restante da metade maior...
	while (esq <= meio) {
		memcpy(r+rasc, a+esq, sizeof(Registro));
		++esq, ++rasc;
	}
	while (dir <= sup) {
		memcpy(r+rasc, a+dir, sizeof(Registro));
		++dir, ++rasc;
	}
	// Retorna para o vetor original o conteudo ordenado presente no rascunho
	memcpy(a+inf, r, sizeof(Registro)*tamanho);
	free(r);
}

void merge(Registro a[], int inf, int sup) {
	if (inf < sup) {
		int meio = (inf+sup)/2;
		merge(a, inf, meio);
		merge(a, meio+1, sup);
		intercala(a, inf, meio, sup);
	}
}

void quick(Registro a[], int inf, int sup) {
	if (inf < sup) {
		int pivo = a[(inf+sup)/2].chave;
		int esq = inf, dir = sup;
		while (esq <= dir) {
			while (a[esq].chave < pivo) ++esq;
			while (a[dir].chave > pivo) --dir;
			if (esq <= dir) {
				swap(a+esq, a+dir);
				++esq, --dir;
			}
		}
		quick(a, inf, dir);
		quick(a, esq, sup);
	}
}

