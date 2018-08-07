#include <stdio.h>
#include "exerc8lista1fila.h"
#include "exerc8lista1pilha.h"  // para usar a pilha na funcao f_inverte

struct Fila {
    tipo* vetor;
    size_t max;
    int inicio, fim;
};

struct Fila* f_cria(size_t tamanho) {
    struct Fila* f = (struct Fila*) malloc(sizeof(struct Fila));
    f->vetor = (tipo*) malloc(tamanho * sizeof(tipo));
    f->max = tamanho;
    f->inicio = f->fim = tamanho-1;
    return f;
}

void f_destroi(struct Fila* f) {
    free(f->vetor);
    free(f);
}

bool f_underflow(const struct Fila* f) {
    return f->inicio == f->fim;
}

bool f_overflow(const struct Fila* f) {
    if (f->inicio == 0) return f->fim == f->max - 1;
    else return f->fim == f->inicio - 1;
}

bool enqueue(struct Fila* f, tipo v) {
    if (f_overflow(f)) {
        return false;
    }
    f->fim = f->fim==f->max-1? 0: f->fim+1;
    f->vetor[f->fim] = v;
    return true;
}

bool dequeue(struct Fila* f, tipo* pv) {
    if (f_underflow(f)) {
        return false;
    }
    f->inicio = f->inicio==f->max-1? 0: f->inicio+1;
    *pv = f->vetor[f->inicio];
    return true;
}

void f_imprime(const struct Fila* f) {
    printf("(Inicio) ");
    if (!f_underflow(f)) {
        int i = f->inicio==f->max-1? 0: f->inicio+1;
        for (;;) {
            printf("%u ", f->vetor[i]);
            if (i == f->fim) {
                break;
            }
            i = i==f->max-1? 0: i+1;
        }
    }
    printf("(Fim)\n");
}

void f_inverte(struct Fila* f) {
    tipo var;

    // Cria uma pilha como estrutura de dados auxiliar, definindo o seu
    // tamanho como o maximo desta fila a ser invertida
    struct Pilha* p = p_cria(f->max);

    // Transfere TODOS os elementos da fila para a pilha
    while (!f_underflow(f)) {
        dequeue(f, &var);
        push(p, var);
    }

    // Agora fazemos o oposto: transferimos TODOS os elementos da pilha
    // e reinserimos na fila, mas eles virao na ordem inversa em que foram
    while (!p_underflow(p)) {
        pop(p, &var);
        enqueue(f, var);
    }

    // Nao posso sair sem destruir a pilha que criei na memoria
    p_destroi(p);
}

