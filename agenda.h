#define MAX_EMPRESA	30
#define MAX_NOME 40
#define MAX_FONES 3

struct telefone {
	int ddd;
	int numero;
};

struct contato {
	char empresa[MAX_EMPRESA+1];
	char responsavel[MAX_NOME+1];
	struct telefone lista[MAX_FONES];
};

/*
 * struct contato {
 *     char empresa[MAX_EMPRESA+1], responsavel[MAX_NOME+1];
 *     struct telefone {
 *         int ddd, numero;
 *     } lista[MAX_FONES];
 * };
 */
