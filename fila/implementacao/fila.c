#include <stdlib.h>
#include <limits.h>
#include "fila.h" // definicao externa do TAD
#include "fila_uso_interno.h" // definicao da estrutura interna

Fila* cria(size_t tamanho) {
    Fila* nova = malloc(sizeof(Fila));
    nova->vetor = malloc(sizeof(int)*(tamanho+1)); // uma posicao eh *perdida* no
                                                   // vetor circular (v. TENENBAUM)

    // Considerando o vetor como "circular", i.e., no qual a posicao seguinte
    // ah ultima eh a primeira (TAMANHO -> 0), os indices devem ser
    // posicionados *antes* da extremidade inicial do vetor
    nova->inicio = nova->fim = tamanho;
    nova->tamanho = tamanho; // para controle da recirculacao dos indices
                             // (v. funcoes 'insere' e 'retira')
    return nova; // retorna o endereco da estrutura recem-criada
}

void destroi(Fila* fila) {
    free(fila->vetor);
    free(fila);
}

// Uma funcao static soh eh visivel dentro da mesma unidade
// de compilacao (arquivo .c)
static bool overflow(const Fila* fila) {
    // Testa se o indice 'fim' alcancou o indice 'inicio' ao "dar a volta" por
    // todo o vetor preenchendo-o com elementos (funcao 'insere')
    if (fila->inicio == 0) {
        return fila->fim == fila->tamanho;
    }
    return fila->fim == fila->inicio - 1;
}

bool underflow(const Fila* fila) {
    return fila->inicio == fila->fim; // 'inicio' (retiradas) alcancou o 'fim'
                                      // (insercoes)
}

void insere(Fila* fila, int elemento) {
    if (overflow(fila)) {
        return; // nao faz nada :-(
    }
    // Assim como o 'topo' avancava na pilha pra inserir um novo elemento,
    // o 'fim' avanca aqui tambem; mas, como existe o carater circular do vetor,
    // pode ser que esse avanco signifique voltar para a extremidade inicial
    if (fila->fim == fila->tamanho) {
        fila->fim = 0;
    } else {
        ++fila->fim;
    }
    fila->vetor[fila->fim] = elemento; // o indice 'fim' reflete a posicao da
                                       // ultima insercao
}

int retira(Fila* fila) {
    if (underflow(fila)) {
        return INT_MIN; // retorna o extremo inferior da faixa de inteiros
    }
    // Note que, assim como o indice 'fim' avanca pela fila em novas insercoes, o
    // 'inicio' tambem avanca para remocoes; em outras palavras, o 'inicio' da
    // fila persegue o 'fim'
    if (fila->inicio == fila->tamanho) {
        fila->inicio = 0;
    } else {
        ++fila->inicio;
    }
    return fila->vetor[fila->inicio]; // o indice 'inicio' reflete a posicao da
                                      // ultima remocao
}

