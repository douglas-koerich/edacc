#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "listah.h"

struct Entrada {
    ListaReg* lista_sinonimas;
};
typedef struct Entrada Entrada;

// Definicao concreta da tabela hash de registros do tipo Reg
struct HashReg {
    Entrada* tabela;
    size_t tamanho; // valor de M do qual falamos na teoria
};

HashReg* cria(size_t tamanho_tabela) {
    HashReg* hash = malloc(sizeof(HashReg));
    hash->tamanho = tamanho_tabela;
    hash->tabela = malloc(sizeof(Entrada) * hash->tamanho);
    int i;
    for (i=0; i<hash->tamanho; ++i) {
        hash->tabela[i].lista_sinonimas = l_cria(); // cria lista de chaves
    }
    return hash;
}

void destroi(HashReg* hash) {
    int i;
    for (i=0; i<hash->tamanho; ++i) {
        l_destroi(hash->tabela[i].lista_sinonimas);
    }
    free(hash->tabela);
    free(hash);
}

// Funcao de hashing nao precisa ser conhecida de fora do TAD,
// por isso fazemo-la uma funcao 'static' do modulo de implementacao
static int funcao_hash(const char* chave, size_t tamanho) {
    int soma = 0, i = 0;
    while (chave[i] != '\0') {
        soma += chave[i] * (i+1);
        ++i;
    }
    return soma % tamanho;
}

void insere(HashReg* hash, const Reg* reg) {
    int posicao = funcao_hash(reg->chave, hash->tamanho);
    l_insere(hash->tabela[posicao].lista_sinonimas, INICIO, reg);
}

const Reg* busca(const HashReg* hash, const char chave[]) {
    int posicao = funcao_hash(chave, hash->tamanho);
    return l_busca(hash->tabela[posicao].lista_sinonimas, chave);
}

Reg exclui(HashReg* hash, const char chave[]) {
    int posicao = funcao_hash(chave, hash->tamanho);
    return l_exclui_chave(hash->tabela[posicao].lista_sinonimas, chave);
}

static void imprime_barra(void) {
    putchar('+');
    int j;
    for (j=0; j<16; ++j) {
        putchar('-');
    }
    puts("+");
}

void imprime(const HashReg* hash) {
    int i;
    for (i=0; i<hash->tamanho; ++i) {
        imprime_barra();
        printf("|%16p| ", hash->tabela[i].lista_sinonimas);
        l_imprime(hash->tabela[i].lista_sinonimas);
        putchar('\n');
    }
    imprime_barra();
}

