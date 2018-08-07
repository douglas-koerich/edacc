#include <stdlib.h>
#include <stdio.h>
#include "tad.h"

struct complexo {
    long x;
    long y;
};

complexo global;

complexo* inicia(int a, int b) {
    /* Nao posso usar/devolver uma variavel local porque ela eh DESTRUIDA da
    memoria ao sair da funcao 'inicia'...
    complexo local = { .x = a, .y = b };
    return &local;
    */
    /* Nao posso usar uma variavel global porque, apesar de ser permanente no
    programa, eh UNICA e portanto toda chamada de 'inicia' mudaria seus valores
    para os novos parametros
    global.x = a;
    global.y = b;
    return &global;
    */
    // SOLUCAO: "criar" sob demanda (i.e., cada vez que a funcao 'inicia' eh chamada)
    // uma nova "variavel permanente", que soh pode ser assim se for alocada dinamicamente
    complexo* nova = (complexo*) malloc(sizeof(complexo));   // cria uma variavel na memoria e devolve seu endereco (como faz o &)
    (*nova).x = a;  // (pouco usado) aplica o operador * para acessar o conteudo da memoria e vai com o '.' ateh o campo 'x'
    nova->y = b;    // o operador -> eh usado pra ir ao campo 'y' tendo da estrutura apenas o endereco dela
    return nova;
}

void libera(complexo* c) {
    if (NULL == c) {
        return;
    }
    free(c);
}

complexo* duplica(const complexo* c) {
    return inicia(c->x, c->y);
}

void conjugado(complexo* c) {
    c->y = -(c->y);
}

complexo* soma(const complexo* i1, const complexo* i2) {
    complexo* s = duplica(i1);
    s->x += i2->x;
    s->y += i2->y;
    return s;
}

void imprime(const complexo* c) {
    printf("%ld %ldi", c->x, c->y);
}
