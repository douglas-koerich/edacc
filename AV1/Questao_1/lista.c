#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"
#include "fila.h"

/* AS DEFINICOES DE ESTRUTURAS ABAIXO FORAM REPRODUZIDAS NO
   ENUNCIADO DA QUESTAO 1 DA PROVA */

struct Palavra {
    char* palavra;
    struct Palavra* proxima;
    struct Palavra* anterior;
};
typedef struct Palavra Palavra;
struct ListaPalavras {
    Palavra* primeira;
};

/* AS PROXIMAS FUNCOES //NAO// FAZIAM PARTE DA QUESTAO 1, PODIAM SER CONSULTADAS
   NO MATERIAL PROPRIO (v. arquivo-fonte impl_lista_dupla.c ) E ESTAO SENDO
   INCLUIDAS AQUI APENAS PARA O CORRETO FUNCIONAMENTO DO PROGRAMA DEMONSTRATIVO
   DA SOLUCAO APRESENTADA */

ListaPalavras* criar(void) {
    ListaPalavras* l = (ListaPalavras*) malloc(sizeof(ListaPalavras));
    l->primeira = NULL;
    return l;
}

void destruir(ListaPalavras* l) {
    if (l == NULL) {
        return;
    }
    while (!underflow(l)) {
        Palavra* x = l->primeira;
        l->primeira = x->proxima;
        free(x->palavra);
        free(x);
    }
    free(l);
}

bool underflow(const ListaPalavras* l) {
    return l == NULL || l->primeira == NULL;
}

void imprimir(const ListaPalavras* l) {
    if (underflow(l)) {
        printf("(Vazia)");
        return;
    }
    printf("(Primeira) ||<");
    Palavra* i = l->primeira;
    while (i != NULL) {
        printf("-->[%s]<", i->palavra);
        i = i->proxima;
    }
    printf("-->|| (Ultima)");
}

void inserir(ListaPalavras* l, const char* s) {
    if (l == NULL) {
        return;
    }
    Palavra* p = (Palavra*) malloc(sizeof(Palavra));
    p->palavra = (char*) malloc(strlen(s)+1);
    strcpy(p->palavra, s);  // poderia usar a funcao strdup() tambem...
    Palavra* i = l->primeira;
    Palavra* anterior_i = NULL;
    while (i != NULL && strcmp(i->palavra, p->palavra) < 0) {
        anterior_i = i;
        i = i->proxima;
    }
    p->proxima = i;
    if (i != NULL) {
        i->anterior = p;
    }
    p->anterior = anterior_i;
    if (anterior_i == NULL) {
        l->primeira = p;
    } else {
        anterior_i->proxima = p;
    }
}

void remover(ListaPalavras* l, const char* s) {
    if (underflow(l)) {
        return;
    }
    Palavra* i = l->primeira;
    while (i != NULL && strcmp(i->palavra, s) != 0) {
        i = i->proxima;
    }
    if (i == NULL) {
        return;
    }
    if (i->anterior == NULL) {
        l->primeira = i->proxima;
    } else {
        i->anterior->proxima = i->proxima;
    }
    if (i->proxima != NULL) {
        i->proxima->anterior = i->anterior;
    }
    free(i->palavra);
    free(i);
}

/* AS PROXIMAS FUNCOES SAO UMA RESPOSTA DA QUESTAO 1; A IMPLEMENTACAO DA FUNCAO
   insere_inicio JUSTIFICA-SE PELO REUSO NA FUNCAO mesclar_inversa, MAS NAO ERA
   OBRIGATORIA (SEU CODIGO PODERIA ESTAR NA PROPRIA FUNCAO mesclar_inversa) */

void insere_inicio(ListaPalavras* l, Fila* f) {
    Palavra* n = (Palavra*) malloc(sizeof(Palavra));
    const char* p = dequeue(f);
    n->palavra = (char*) malloc(strlen(p)+1);
    strcpy(n->palavra, p);
    n->anterior = NULL;
    n->proxima = l->primeira;
    if (l->primeira != NULL) {
        l->primeira->anterior = n;
    }
    l->primeira = n;
}

ListaPalavras* mesclar_inversa(const ListaPalavras* l1, const ListaPalavras* l2) {
    if ((l1 == NULL || l1->primeira == NULL) && (l2 == NULL || l2->primeira == NULL)) {
        return NULL;
    }
    ListaPalavras* lm = (ListaPalavras*) malloc(sizeof(ListaPalavras));
    lm->primeira = NULL;
    Fila* auxiliar = cria_fila();
    if (l1 == NULL || l1->primeira == NULL) {
        Palavra* p = l2->primeira;
        while (p != NULL) {
            enqueue(auxiliar, p->palavra);
            p = p->proxima;
        }
        while (!fila_vazia(auxiliar)) {
            insere_inicio(lm, auxiliar);
        }
    } else if (l2 == NULL || l2->primeira == NULL) {
        Palavra* p = l1->primeira;
        while (p != NULL) {
            enqueue(auxiliar, p->palavra);
            p = p->proxima;
        }
        while (!fila_vazia(auxiliar)) {
            insere_inicio(lm, auxiliar);
        }
    } else {
        Palavra* p1 = l1->primeira;
        Palavra* p2 = l2->primeira;
        while (p1 != NULL && p2 != NULL) {
            if (strcmp(p1->palavra, p2->palavra) < 0) {
                enqueue(auxiliar, p1->palavra);
                p1 = p1->proxima;
            } else {
                enqueue(auxiliar, p2->palavra);
                p2 = p2->proxima;
            }
        }
        while (p1 != NULL) {
            enqueue(auxiliar, p1->palavra);
            p1 = p1->proxima;
        }
        while (p2 != NULL) {
            enqueue(auxiliar, p2->palavra);
            p2 = p2->proxima;
        }
        while (!fila_vazia(auxiliar)) {
            insere_inicio(lm, auxiliar);
        }
    }
    destroi_fila(auxiliar);
    return lm;
}
