#include <stdlib.h>
#include <limits.h>
#include "deque.h" // definicao externa do TAD
#include "deque_uso_interno.h" // definicao da estrutura interna

Deque* cria(size_t tamanho) {
    Deque* novo = malloc(sizeof(Deque));
    novo->vetor = malloc(sizeof(int)*(tamanho+1)); // uma posicao eh *perdida* no
                                                   // vetor circular (v. TENENBAUM)

    // Considerando o vetor como "circular", i.e., no qual a posicao seguinte
    // ah ultima eh a primeira (TAMANHO -> 0), os indices devem ser
    // posicionados *antes* da extremidade inicial do vetor
    novo->inicio = novo->fim = tamanho;
    novo->tamanho = tamanho; // para controle da recirculacao dos indices
                             // (v. funcoes 'insere' e 'retira')
    return novo; // retorna o endereco da estrutura recem-criada
}

void destroi(Deque* deque) {
    free(deque->vetor);
    free(deque);
}

// Uma funcao static soh eh visivel dentro da mesma unidade
// de compilacao (arquivo .c)
static bool overflow(const Deque* deque) {
    // Testa se o indice 'fim' alcancou o indice 'inicio' ao "dar a volta" por
    // todo o vetor preenchendo-o com elementos (funcao 'insere'), ou o 'inicio'
    // alcancou o 'fim' ao "dar a volta" no sentido contrario, inserindo novos
    // elementos de um modo que a fila tradicional nao fazia
    if (deque->inicio == 0) {
        return deque->fim == deque->tamanho;
    }
    return deque->fim == deque->inicio - 1;
}

bool underflow(const Deque* deque) {
    return deque->inicio == deque->fim; // 'inicio' (retiradas) alcancou o 'fim'
                                        // (insercoes); ou 'fim' (retiradas)
                                        // alcancou o 'inicio' (insercoes)
}

void insere(Deque* deque, int elemento, Lado onde) {
    if (overflow(deque)) {
        return; // nao faz nada :-(
    }
    // Se a insercao no deque estah sendo feita na mesma extremidade que na
    // fila tradicional, i.e., no 'fim', o codigo eh o mesmo daquela estrutura
    if (onde == FIM) {
        if (deque->fim == deque->tamanho) {
            deque->fim = 0;
        } else {
            ++deque->fim;
        }
        deque->vetor[deque->fim] = elemento;
    } else { // insercao pelo lado do 'inicio' eh uma novidade do deque
        deque->vetor[deque->inicio] = elemento; // aqui um ponto importante: 'inicio'
                                                // sempre estah "atras" do "primeiro"
                                                // elemento no deque (na fila), entao
                                                // essa posicao estah LIVRE pra ser
                                                // usada na insercao
        if (deque->inicio == 0) {
            deque->inicio = deque->tamanho;
        } else {
            --deque->inicio;
        }
    }
}

int retira(Deque* deque, Lado onde) {
    if (underflow(deque)) {
        return INT_MIN; // retorna o extremo inferior da faixa de inteiros
    }
    // Se a retirada do deque estah sendo feita na mesma extremidade que na
    // fila tradicional, i.e., no 'inicio', o codigo eh o mesmo daquela estrutura
    if (onde == INICIO) {
        if (deque->inicio == deque->tamanho) {
            deque->inicio = 0;
        } else {
            ++deque->inicio;
        }
        return deque->vetor[deque->inicio];
    } else { // retirada do 'fim', exclusividade do deque
        int elemento = deque->vetor[deque->fim]; // 'fim' estah "sobre" o "ultimo"
                                                 // elemento no deque (na fila),
                                                 // entao *jah estah* na posicao do
                                                 // elemento que vai ser removido
        if (deque->fim == 0) {
            deque->fim = deque->tamanho;
        } else {
            --deque->fim;
        }
        return elemento;
    }
}

