#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Definicao do registro com a chave de busca
typedef struct Registro {
	int chave;
} Registro;

// Definicao de uma lista encadeada com nos de registros
typedef struct Noh {
	Registro elemento;
	struct Noh* proximo;
} Noh;

typedef struct Lista {
	Noh* cabeca;
} Lista;

Lista* cria(void) {
	Lista* l = (Lista*) malloc(sizeof(Lista));
	l->cabeca = NULL;
	return l;
}

void destroi(Lista* l) {
	while (l->cabeca != NULL) {
		Noh* p = l->cabeca;
		l->cabeca = p->proximo;
		free(p);
	}
	free(l);
}

void inserir_i(Lista* l, const Registro* r) {
	Noh* n = (Noh*) malloc(sizeof(Noh));
	memcpy(&n->elemento, r, sizeof(Registro));
	n->proximo = l->cabeca;
	l->cabeca = n;
}

// A operacao de insercao no fim retorna o endereco do novo
// noh criado - "sentinela" (mas que podera ser cancelado se
// a chave for encontrada em outro noh que nao o sentinela)
Noh* inserir_f(Lista* l, const Registro* r) {
	Noh* n = (Noh*) malloc(sizeof(Noh));
	memcpy(&n->elemento, r, sizeof(Registro));
	n->proximo = NULL;
	if (l->cabeca == NULL) {
		l->cabeca = n;
	}
	else {
		Noh* i = l->cabeca;
		while (i->proximo != NULL) {
			i = i->proximo;
		}
		i->proximo = n;
	}
	return n;
}

void remover_f(Lista* l) {
	// Neste caso particular, o fim NUNCA sera igual ao inicio da lista,
	// porque a remocao se dah por conta do sentinela ser uma duplicata
	// de outro noh, portanto a lista teria no minimo dois nos, a cabeca
	// e o sentinela (que serah removido)
	Noh* i = l->cabeca, *anterior = NULL;
	while (i->proximo != NULL) {
		anterior = i;
		i = i->proximo;
	}
	anterior->proximo = NULL;
	free(i);
}

int v_busca_seq(Registro [*], size_t, int);	// devolve o indice no vetor
Noh* l_busca_seq(Lista*, int);				// devolve o endereco do noh

Noh* l_sentinela(Lista*, const Registro*);	// com registro a ser adicionado/
											// atualizado
int v_sentinela(Registro [*], size_t, size_t*, const Registro*);

#define TAMANHO 100

int main() {
	srand(time(0));

	size_t tamanho;
	do {
		printf("Digite o numero de registros: ");
		scanf("%u", &tamanho);
	} while (tamanho >= TAMANHO);

	Registro vetor[TAMANHO];
	Lista* lista = cria();

	int i;
	for (i=0; i<tamanho; ++i) {
		int chave = rand() % 1000 + 1;
		vetor[i].chave = chave;		// salva um registro no vetor
		inserir_i(lista, vetor+i);	// inclui o mesmo registro na lista

		// Para podermos saber o que foi colocado na serie, vamos imprimir
		// a chave gerada
		printf("%d ", chave);
	}
	
	// Vamos fazer uma busca SEQUENCIAL nesse vetor e nessa lista
	printf("\n\nDigite a chave procurada: ");
	int x;
	scanf("%d", &x);

	int indice = v_busca_seq(vetor, tamanho, x);
	printf("Encontrou a chave no indice %d do vetor.\n", indice);

	Noh* noh = l_busca_seq(lista, x);
	printf("Encontrou a chave no noh localizado em %p.\n", noh);

	// Insercao/atualizacao com sentinela
	Registro novo;
	printf("Digite uma nova chave (de registro): ");
	scanf("%d", &novo.chave);
	noh = l_sentinela(lista, &novo);
	printf("Registro atualizado (ou adicionado) em %p.\n", noh);

	indice = v_sentinela(vetor, TAMANHO, &tamanho, &novo);
	printf("Registro atualizado (ou adicionado) na posicao %d.\n", indice);
	printf("O vetor tem agora %u elementos.\n", tamanho);

	destroi(lista);

	return 0;
}

int v_busca_seq(Registro v[], size_t t, int x) {
	int i = 0;
	while (i < t) {
		if (v[i].chave == x) {
			return i;	// Retorna o primeiro indice que for encontrado
		}
		++i;
	}
	return -1;			// Retorna um indice INVALIDO se nao achou
}

Noh* l_busca_seq(Lista* l, int x) {
	Noh *i = l->cabeca;
	while (i != NULL) {
		if (i->elemento.chave == x) {
			return i;	// Retorna o primeiro noh que for encontrado
		}
		i = i->proximo;
	}
	return NULL;		// Retorna um ponteiro/noh INVALIDO se nao achou
}

Noh* l_sentinela(Lista* l, const Registro* r) {
	Noh* sentinela = inserir_f(l, r);
	Noh* i = l_busca_seq(l, r->chave);	// com certeza irah encontrar!
	if (i != sentinela) {	// nao existia esse registro em outro noh
		// Faz nada, o sentinela eh um novo noh
	}
	else {	// encontrei em um noh anterior, atualiza esse noh e remove o sentinela
		memcpy(&i->elemento, r, sizeof(Registro));	// registro atualizado no noh!
		remover_f(l);
	}
	return i;
}

int v_sentinela(Registro v[], size_t max, size_t* atual, const Registro* r) {
	size_t tam = *atual;
	if (tam == max) {
		// Nao ha espaco para o sentinela
		return -1;
	}
	memcpy(v+tam, r, sizeof(Registro));	// copia o novo registro para a proxima
										// posicao livre do vetor (indice 'tam')
	int i = v_busca_seq(v, tam+1, r->chave);
	if (i == tam) {	// nao existia esse registro em outro indice anterior
		// O sentinela eh um novo elemento do vetor, deve ser contado a partir
		// de agora
		++(*atual);	// por isso que 'atual' precisa ser ponteiro, para atualizar
					// o comprimento do vetor conhecido pela funcao que chamou
	}
	else {
		memcpy(v+i, r, sizeof(Registro));	// atualiza no indice correto
	}
	return i;
}

