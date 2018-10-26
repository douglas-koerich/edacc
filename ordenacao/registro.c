#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "registro.h"

void preenche_registro_aleatorio(Registro* r) {
    srand((unsigned) r); // usa o valor do endereco como semente do rand()
    r->chave = rand() % 10000;
    int i;
    for (i=0; i<MAX-1; ) {
        do {
            r->campo_1[i] = rand() % 128; // codigo ASCII aleatorio
        } while (!isgraph(r->campo_1[i]));
        ++i;
    }
    r->campo_1[MAX-1] = '\0'; // terminador nulo no campo string
    r->campo_2 = (float) rand() / pow(10, rand() % 6); // gera um numero real aleatorio
    r->campo_3 = rand() % 2;
}

void imprime_registro(const Registro* r) {
    printf("[%u];%s;%f;%d\n", r->chave, r->campo_1, r->campo_2, r->campo_3);
}

void troca_registros(Registro* r1, Registro* r2) {
    Registro temp;
    /*
     * temp = *r1;
     * *r1 = *r2;
     * *r2 = temp;
     */
    memcpy(&temp, r1, sizeof(Registro)); // copia TODOS os bytes de r1 pra temp
    memcpy(r1, r2, sizeof(Registro));
    memcpy(r2, &temp, sizeof(Registro));
}

