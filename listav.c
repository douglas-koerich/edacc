#include <stdio.h>
#include "listav.h"

// Definicao do TAD: Lista linear de elementos
struct Lista {
    tipo* vetor;        // vetor serah alocado dinamicamente
    int inicio, fim;    // como os indices do deque
    size_t tamanho;     // como o maximo eh definido na criacao, tem que ser lembrado aqui
};

struct Lista* cria(size_t max) {
    // Alocacao da estrutura do TAD na memoria
    struct Lista* l = (struct Lista*) malloc(sizeof(struct Lista));

    // Alocacao dinamica do vetor
    l->tamanho = max;
    l->vetor = (tipo*) malloc(l->tamanho * sizeof(tipo));

    // Inicializa indices como no deque
    l->inicio = l->fim = l->tamanho - 1;

    return l;
}

void destroi(struct Lista* l) {
    free(l->vetor);
    free(l);
}

bool underflow(const struct Lista* l) {
    return l->inicio == l->fim; // como no deque
}

bool overflow(const struct Lista* l) {
    return l->fim == (l->inicio > 0? l->inicio-1: l->tamanho-1); // como no deque
}

void imprime(const struct Lista* l) {
    // Como na fila circular (e no deque, por consequencia)...
    printf("(Inicio) ");
    if (!underflow(l)) {
        int i = l->inicio==l->tamanho-1? 0: l->inicio+1;
        for (;;) {
            printf("%u ", l->vetor[i]);
            if (i == l->fim) {
                break;
            }
            i = i==l->tamanho-1? 0: i+1;
        }
    }
    printf("(Fim)\n");
}

tipo* busca(const struct Lista* l, tipo val) {
    if (underflow(l)) {
        return NULL;    // lista vazia, nao ha o que procurar
    }
    int i = l->inicio==l->tamanho-1? 0: l->inicio+1;
    for (;;) {
        if (l->vetor[i] == val) {   // compara com o elemento da vez
            return l->vetor + i;    // achei, devolve o seu endereco
        }
        if (i == l->fim) {
            break;
        }
        i = i==l->tamanho-1? 0: i+1;
    }
    return NULL;    // terminei de percorrer a lista sem encontrar
}

bool inserirInicio(struct Lista* l, tipo val) {
    if (overflow(l)) {
        return false;
    }
    // Como a insercao no inicio do deque
    l->vetor[l->inicio] = val;  // 'inicio' ja estah na posicao ANTERIOR ao primeiro
    l->inicio = l->inicio==0? l->tamanho-1: l->inicio-1;  // retrocede o inicio
    return true;
}

bool inserirFim(struct Lista* l, tipo val) {
    if (overflow(l)) {
        return false;
    }
    // Como a insercao no fim do deque (e da fila)
    l->fim = l->fim==l->tamanho-1? 0: l->fim+1;   // 'fim' estah na posicao do ultimo, incrementa
    l->vetor[l->fim] = val;
    return true;
}

bool inserirPosicao(struct Lista* l, tipo val, size_t pos) {
    if (overflow(l)) {
        return false;
    }
    // Contador de posicao
    size_t p;

    // Cursor de posicao: comeca o percurso pelo indice de inicio
    int i = l->inicio==l->tamanho-1? 0: l->inicio+1;
    for (p=1; p<pos; ++p) {
        if (i == l->fim) {
            // Posicao pretendida estah alem do fim da lista
            return false;
        }
        i = i==l->tamanho-1? 0: i+1;
    }
    // Comecando do fim da lista, desloca cada elemento uma posicao para frente, a fim de
    // abrir uma posicao livre
    int j = l->fim;
    l->fim = l->fim==l->tamanho-1? 0: l->fim+1;
    for (;;) {
        int k = j==l->tamanho-1? 0: j+1;
        l->vetor[k] = l->vetor[j];
        if (j == i) {
            break;
        }
        j = j==0? l->tamanho-1: j-1;
    }
    // Agora que a posicao estah livre, insere novo valor no meio da lista
    l->vetor[i] = val;
    return true;
}

bool inserirOrdem(struct Lista* l, tipo val) {
    if (overflow(l)) {
        return false;
    }
    // Cursor de varredura: comeca pelo indice de inicio
    int i = l->inicio==l->tamanho-1? 0: l->inicio+1;
    while (l->vetor[i] < val) {
        if (i == l->fim) {
            // O novo valor eh o maior da lista, insere no fim
            return inserirFim(l, val);
        }
        i = i==l->tamanho-1? 0: i+1;
    }
    // Comecando do fim da lista, desloca cada elemento uma posicao para frente, a fim de
    // abrir uma posicao livre
    int j = l->fim;
    l->fim = l->fim==l->tamanho-1? 0: l->fim+1;
    for (;;) {
        int k = j==l->tamanho-1? 0: j+1;
        l->vetor[k] = l->vetor[j];
        if (j == i) {
            break;
        }
        j = j==0? l->tamanho-1: j-1;
    }
    // Agora que a posicao estah livre, insere novo valor no meio da lista
    l->vetor[i] = val;
    return true;
}

bool removerInicio(struct Lista* l, tipo* pval) {
    if (underflow(l)) {
        return false;
    }
    // Como a remocao do inicio do deque (e da fila)
    l->inicio = l->inicio==l->tamanho-1? 0: l->inicio+1;
    *pval = l->vetor[l->inicio];
    return true;
}

bool removerFim(struct Lista* l, tipo* pval) {
    if (underflow(l)) {
        return false;
    }
    // Como a remocao do fim no deque
    *pval = l->vetor[l->fim];
    l->fim = l->fim==0? l->tamanho-1: l->fim-1;
    return true;
}

bool removerPosicao(struct Lista* l, tipo* pval, size_t pos) {
    if (underflow(l)) {
        return false;
    }
    // Contador de posicao
    size_t p;

    // Cursor de posicao: comeca o percurso pelo indice de inicio
    int i = l->inicio==l->tamanho-1? 0: l->inicio+1;
    for (p=1; p<pos; ++p) {
        if (i == l->fim) {
            // Posicao pretendida estah alem do fim da lista
            return false;
        }
        i = i==l->tamanho-1? 0: i+1;
    }
    // Devolve o valor que estah sendo removido desta posicao
    *pval = l->vetor[i];

    // Deste ponto ateh o fim da lista, move cada elemento para a posicao
    // anterior
    for (;;) {
        int j = i==l->tamanho-1? 0: i+1;
        l->vetor[i] = l->vetor[j];
        if (j == l->fim) {
            break;
        }
        i = i==l->tamanho-1? 0: i+1;
    }
    l->fim = l->fim==0? l->tamanho-1: l->fim-1;
    return true;
}

bool removerValor(struct Lista* l, tipo val, size_t* ppos) {
    if (underflow(l)) {
        return false;
    }
    // Contador de posicao
    size_t p = 1;

    // Cursor de posicao: comeca o percurso pelo indice de inicio
    int i = l->inicio==l->tamanho-1? 0: l->inicio+1;
    while (l->vetor[i] != val) {
        if (i == l->fim) {
            // Nao existe o valor na lista
            *ppos = 0;
            return false;
        }
        i = i==l->tamanho-1? 0: i+1;
        ++p;
    }
    // Devolve a posicao onde encontrou o valor
    *ppos = p;

    // Deste ponto ateh o fim da lista, move cada elemento para a posicao
    // anterior
    for (;;) {
        int j = i==l->tamanho-1? 0: i+1;
        l->vetor[i] = l->vetor[j];
        if (j == l->fim) {
            break;
        }
        i = i==l->tamanho-1? 0: i+1;
    }
    l->fim = l->fim==0? l->tamanho-1: l->fim-1;
    return true;
}

