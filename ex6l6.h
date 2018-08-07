#ifndef EX6L6_H
#define EX6L6_H

// Definicao do tipo de registro que sera armazenado na tabela hashing
struct Registro {
    int chave;
    /* ... outros campos viriam na sequencia ... */
};
typedef struct Registro Registro;

// Definicao do TAD: tabela hashing
struct TabelaHashing;

struct TabelaHashing* cria(size_t);
void destroi(struct TabelaHashing*);
void insere(struct TabelaHashing*, const Registro*);
Registro* busca(struct TabelaHashing*, int);
void imprime(const struct TabelaHashing*);

#endif
