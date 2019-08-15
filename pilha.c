/* Este arquivo-fonte JAMAIS deverah ser publicado para o usuario do TAD,
 * pois ele(a) soh pode usar a Pilha atraves das operacoes definidas no
 * arquivo-cabecalho (underflow, push, etc.) */

#include "pilha.h" // para conhecer a definicao publica do TAD

#include <stdlib.h>
#include <stdio.h>

#define TAM_PILHA   1024 // capacidade de 1024 'char's (1 KiB)

// Definicao explicita do conteudo da struct que implementa o TAD
// (feita aqui num arquivo-fonte .c porque soh eh usada aqui dentro)
struct Pilha {
#ifdef USE_MALLOC
    char* vetor; // vetor alocado dinamicamente com a pilha
#else
    char vetor[TAM_PILHA]; // vetor criado estaticamente com a pilha
#endif
    int topo; // marcacao do fim da pilha (topo) no vetor
};

Pilha* cria(void) {
    // Primeiro, cria a estrutura (struct Pilha) na memoria
    Pilha* p = malloc(sizeof(Pilha));

    // Se houve opcao por alocar o vetor interno tambem dinamicamente,
    // faz isso agora
#ifdef USE_MALLOC
    p->vetor = malloc(sizeof(char) * TAM_PILHA);
#endif

    // Como a pilha eh criada inicialmente vazia, a marca de topo
    // deve ser inicializada num indice (posicao do vetor) invalido
    // (nao existe nenhum elemento ainda)
    p->topo = -1;

    return p;
}

void destroi(Pilha* p) {
    if (p == NULL) {
        return;
    }
    // Se houve opcao por alocar o vetor interno tambem dinamicamente,
    // deve liberar essa area de memoria primeiro (do contrario, ficara perdida)
#ifdef USE_MALLOC
    free(p->vetor);
#endif
    free(p); // note que o free() eh chamado apenas na destruicao da Pilha, e nao
             // proximo ao malloc() na ocasiao da criacao
}

bool underflow(const Pilha* p) {
    if (p == NULL) {
        return false;
    }
    return p->topo == -1; // retorna o resultado da comparacao (se for -1, vai
                          // voltar 'true', i.e., eh verdadeiro que estah vazia)
}

bool push(Pilha* p, char c) {
    if (overflow(p)) { // se pilha cheia...
        return false;  // ... nao ha como empilhar (indica isso pelo retorno)
    }
    /*
    ++p->topo; // incrementa o indice, indo pra proxima posicao livre no vetor
    p->vetor[p->topo] = c; // armazena o elemento na nova posicao do topo
    */
    p->vetor[++p->topo] = c; // em uma unica linha

    return true;
}

bool pop(Pilha* p, char* pc) {
    if (underflow(p)) { // se pilha vazia...
        return false;   // ... nao ha o que desempilhar (indica isso no retorno)
    }
    if (pc == NULL) {   // protege-se contra o uso equivocado do TAD
        return false;
    }
    /*
    *pc = p->vetor[p->topo]; // salva o elemento que estah no topo
    --p->topo; // desloca o topo para baixo, "descartando" o que estava acima
    */
    *pc = p->vetor[p->topo--]; // aqui o -- tem que vir DEPOIS (v. seq. acima)

    return true;
}

bool overflow(const Pilha* p) {
    if (p == NULL) {
        return false;
    }
    return p->topo == TAM_PILHA - 1; // se o topo estiver no ultimo indice
}

#ifdef DEBUG
void imprime(const Pilha* p) {
    if (p == NULL) {
        return;
    }
    printf("\nBASE >> [");
    if (underflow(p)) {
        printf("**vazia**");
    } else {
        int i = 0;
        while (i <= p->topo) {
            putchar(p->vetor[i]);
            if (i < p->topo) {
                putchar(' ');
            }
            ++i;
        }
    }
    printf("] << TOPO\n");
}
#endif

