#include <stdio.h>

double dobro(double);
double triplo(double);

struct dicio_funcoes {
    double fator;               // valor real
    double (*funcao)(double);   // ENDERECO da funcao correspondente
};
typedef struct dicio_funcoes dicio_funcoes;

int main(void) {
    dicio_funcoes tabela[] = {
        { 2.0, dobro },         // o valor 2.0 e o endereco de sua funcao
        { 3.0, triplo },        // o valor 3.0 e o endereco de sua funcao
        { 0.0, NULL }
    };
    printf("Digite um numero qualquer: ");
    double n;
    scanf("%lf", &n);
    int i = 0;
    while (tabela[i].fator != 0.0) {
        double multiplo = tabela[i].funcao(n); // chamada da funcao pelo seu ENDERECO
        printf("%lf multiplicado por %lf resulta em %lf.\n",
               n, tabela[i].fator, multiplo);
        ++i;
    }
    return 0;
}

double dobro(double n) {
    double d;
    d = n * 2;
    return d;
}

double triplo(double n) {
    double t;
    t = n * 3;
    return t;
}