#ifndef _EXERC6_7_HASHING_H_
#define _EXERC6_7_HASHING_H_

#include <stdbool.h>

// TAD: Tabela hashing com enderecamento aberto
#define M	17		// numero de posicoes da tabela hashing

enum en_Estado {
	VAZIA,			// indicativo que a posicao nunca foi ocupada e 
					// nao ha chaves sinonimas na sequencia
	OCUPADA,		// posicao esta ocupada, *pode* haver sinonima
	LIBERADA		// posicao foi liberada, mas *pode* haver sinonima
};
typedef enum en_Estado en_Estado;

struct st_Posicao {
	en_Estado	estado;	// qual o estado dessa posicao (vazia, ...)
	int			chave;	// chave armazenada nesta posicao
	//			...		// outros campos do registro armazenado aqui
};
typedef struct st_Posicao st_Posicao;
typedef st_Posicao* TabelaHashing;

int h(int x);			// funcao de hashing (x eh a chave, retorna posicao)
int h_(int x, int i);	// tratamento da colisao (tentativa linear a partir de i)
TabelaHashing criar(void);	// cria nova tabela hashing
int inserir(TabelaHashing t, int x);	// nova chave x na tabela t
int remover(TabelaHashing t, int x);	// remove chave x da tabela t
int buscar(TabelaHashing t, int x);		// busca chave x na tabela t
void destruir(TabelaHashing t);			// destroi tabela t

#endif

