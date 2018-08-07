#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "pilha.h"

// Funcoes requeridas pelo tipo generico
void imprime_letra(void*);
int compara_letra(void*, void*);

// Funcao que implementa o exercicio: repare que ela recebe o elemento
// atraves do seu endereco em tipo void*
bool retira(Pilha*, void*);

int main(int argc, char* argv[]) {
    char conjunto[] = { 'E', 'S', 'T', 'R', 'U', 'T', 'U', 'R', 'A', 'S',
                        'D', 'E', 'D', 'A', 'D', 'O', 'S', ' ' };

    Pilha* pilha = cria();

    int i = 0;
    while (isalpha(conjunto[i])) {
        generico g = {
            .coisa = &conjunto[i],
            .imprime = &imprime_letra,
            .compara = &compara_letra
        };
        push(pilha, &g);
        ++i;
    }
    puts("Pilha ANTES da remocao:");
    imprime(pilha);
    putchar('\n');

    printf("Digite um elemento para buscar e remover: ");
    char elemento;
    scanf(" %c", &elemento);
    elemento = toupper(elemento);

    if (retira(pilha, &elemento) == true) {
        puts("Pilha DEPOIS da remocao:");
        imprime(pilha);
        putchar('\n');
    } else {
        puts("Nao encontrou o elemento na pilha!");
    }

    destroi(pilha);

    return EXIT_SUCCESS;
}

void imprime_letra(void* pv) {
    char* pc = pv;
    putchar(*pc);
}

int compara_letra(void* pv1, void* pv2) {
    char* pc1 = pv1;
    char* pc2 = pv2;
    if (*pc1 > *pc2) {
        return 1;
    } else if (*pc1 < *pc2) {
        return -1;
    } else {
        return 0;
    }
}

bool retira(Pilha* p, void* x) {
    bool achou = false;
    Pilha* aux = cria();    // pilha auxiliar para armazenar os elementos
                            // que nao forem removidos
    while (!underflow(p)) { // nao pahra se encontrar, pode haver repetidos
        generico* g = pop(p);
        if (g->compara(g->coisa, x) != 0) { // nao eh o elemento?
            push(aux, g);   // salva na auxiliar pra recuperar depois
        } else {
            achou = true;
        }
        free(g);
    }
    while (!underflow(aux)) {
        generico* g = pop(aux);
        push(p, g);
        free(g);
    }
    destroi(aux);
    return achou;
}

