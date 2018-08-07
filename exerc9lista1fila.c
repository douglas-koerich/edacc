#include <stdio.h>
#include "exerc9lista1fila.h"

struct Fila {
    int* vetor;
    size_t max;
    int inicio, fim;
};

struct Fila* f_cria(size_t tamanho) {
    struct Fila* f = (struct Fila*) malloc(sizeof(struct Fila));
    f->vetor = (int*) malloc(tamanho * sizeof(int));
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

bool enqueue(struct Fila* f, int v) {
    if (f_overflow(f)) {
        return false;
    }
    f->fim = f->fim==f->max-1? 0: f->fim+1;
    f->vetor[f->fim] = v;
    return true;
}

bool dequeue(struct Fila* f, int* pv) {
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

void f_limpa_menores(struct Fila* f, int limite) {
    int var;

    // Cria uma outra fila como estrutura de dados auxiliar, definindo o seu
    // tamanho como o maximo desta fila a ser filtrada
    // Sendo uma outra fila, e nao uma pilha, garante-se que os elementos
    // serao restaurados na mesma ordem em que foram armazenados durante a
    // varredura na fila original
    struct Fila* aux = f_cria(f->max);

    // Transfere TODOS os elementos da fila para a outra, com excecao daqueles
    // valores menores que o limite
    while (!f_underflow(f)) {
        dequeue(f, &var);
        if (var >= limite) {
            enqueue(aux, var);
        }
    }

    // Agora fazemos o oposto: transferimos TODOS os elementos da fila auxiliar
    // e reinserimos na fila, e eles virao na mesma ordem em que os salvamos
    while (!f_underflow(aux)) {
        dequeue(aux, &var);
        enqueue(f, var);
    }

    // Nao posso sair sem destruir a fila auxiliar que criei na memoria
    f_destroi(aux);
}

