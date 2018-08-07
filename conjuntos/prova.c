#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "comuns.h"
#include "ponto.h"
#include "data.h"
#include "conjunto.h"

char chars[] = { 'A', 'E', 'I', 'O', 'U' };
int inteiro = 197156;
float simples = 3.1416;
double duplo = 2.71828;

#define MAX_PONTOS 4

int main(int argc, char* argv[]) {
    Ponto* pontos = aloca_pontos(MAX_PONTOS);
    Data* data = aloca_data();

    // Inicializa conjuntos-bases
    Conjunto* C1 = inicializa();
    Conjunto* C2 = inicializa();
    Conjunto* C3 = inicializa();
    Conjunto* C4 = inicializa();

    // Verifica que o primeiro conjunto ainda estah vazio
    if (true == vazio(C1)) {
        puts("Conjunto C1 vazio como esperado...");
    } else {
        puts("ERRO: conjunto C1 nao-vazio!??");
    }
    imprime(C1); putchar('\n');

    // Teste de igualdade entre conjuntos vazios
    if (true == igual(C1, C2)) {
        puts("Conjuntos C1 e C2 iguais (vazios) como esperado...");
    } else {
        puts("ERRO: conjuntos C1 e C2 diferentes!??");
    }

    // Conjunto 1: homogeneo de tipo basico
    int i;
    for (i=0; i<sizeof(chars)/sizeof(char); ++i) {
        adiciona(C1, chars+i, imprime_char);
    }

    // Conjunto 2: homogeneo de tipo nao basico
    Ponto* p = pontos;
    for (i=0; i<MAX_PONTOS; ++i) {
        le_ponto(p);
        adiciona(C2, p, imprime_ponto);
        p = proximo_ponto(p);
    }

    // Conjunto 3: heterogeneo de tipos basicos
    adiciona(C3, &inteiro, imprime_int);
    adiciona(C3, &simples, imprime_float);
    adiciona(C3, &duplo, imprime_double);

    // Conjunto 4: heterogeneo de tipos mistos
    adiciona(C4, &chars, imprime_char);
    adiciona(C4, &pontos, imprime_ponto);
    adiciona(C4, &simples, imprime_float);
    le_data(data);
    adiciona(C4, data, imprime_data);

    // Teste de igualdade entre conjuntos nao-vazios
    if (true == igual(C4, C4)) {
        puts("Conjuntos iguais como esperado...");
    } else {
        puts("ERRO: conjuntos diferentes!??");
    }

    // Imprime os conjuntos
    printf("C1: "); imprime(C1); putchar('\n');
    printf("C2: "); imprime(C2); putchar('\n');
    printf("C3: "); imprime(C3); putchar('\n');
    printf("C4: "); imprime(C4); putchar('\n');

    // Testa pertenca ao conjunto
    if (true == pertence(C1, chars+1, compara_char)) {
        printf("Elemento '%c' pertence a C1 como esperado...\n", chars[1]);
    } else {
        printf("ERRO: elemento '%c' NAO pertence ao conjunto C1!??\n", chars[1]);
    }
    if (true == pertence(C2, proximo_ponto(pontos), compara_pontos)) {
        puts("Elemento pertence a C2 como esperado...");
    } else {
        puts("ERRO: elemento NAO pertence ao conjunto C2!??");
    }

    // Remove alguns elementos
    remover(C1, chars+1, compara_char);
    printf("C1: "); imprime(C1); putchar('\n');
    remover(C2, proximo_ponto(pontos), compara_pontos);
    printf("C2: "); imprime(C2); putchar('\n');

    // Testa pertenca ao conjunto
    if (false == pertence(C1, chars+1, compara_char)) {
        printf("Elemento '%c' NAO pertence mais a C1 como esperado...\n", chars[1]);
    } else {
        printf("ERRO: elemento '%c' AINDA pertence ao conjunto C1!??\n", chars[1]);
    }
    if (false == pertence(C2, proximo_ponto(pontos), compara_pontos)) {
        puts("Elemento NAO pertence a C2 como esperado...");
    } else {
        puts("ERRO: elemento AINDA pertence ao conjunto C2!??");
    }

    // Cria e imprime novos conjuntos a partir das operacoes
    Conjunto* U1 = uniao(C1, C3);
    printf("C1 U C3: "); imprime(U1); putchar('\n');
    Conjunto* U2 = uniao(C3, C4);
    printf("C3 U C4: "); imprime(U2); putchar('\n');
    Conjunto* V1 = interseccao(C1, C3);
    printf("C1 i C3: "); imprime(V1); putchar('\n');
    if (true == vazio(V1)) {
        puts("Conjunto vazio como esperado...");
    } else {
        puts("ERRO: conjunto nao-vazio!??");
    }
    Conjunto* I = interseccao(C3, C4);
    printf("C3 i C4: "); imprime(I); putchar('\n');
    Conjunto* D1 = diferenca(C1, C4);
    printf("C1 \\ C4: "); imprime(D1); putchar('\n');
    Conjunto* D2 = diferenca(C4, C1);
    printf("C4 \\ C1: "); imprime(D2); putchar('\n');
    Conjunto* V2 = diferenca(C2, C2);
    printf("C2 \\ C2: "); imprime(V2); putchar('\n');
    if (true == vazio(V2)) {
        puts("Conjunto vazio como esperado...");
    } else {
        puts("ERRO: conjunto nao-vazio!??");
    }
    Conjunto* S = diferenca_simetrica(C1, C4);
    printf("(C1 U C4) \\ (C1 i C4): "); imprime(S); putchar('\n');
    Conjunto* P = produto_cartesiano(C1, C2);
    printf("C1 x C2: "); imprime(P); putchar('\n'); 

    // Testes finais
    if (true == contem(U2, I)) {
        puts("(C3 U C4) contem (C3 i C4) como esperado...");
    } else {
        puts("ERRO: (C3 U C4) NAO contem (C3 i C4)!??");
    }
    if (true == contido(I, U2)) {
        puts("(C3 i C4) estah contido em (C3 U C4) como esperado...");
        if (true == proprio(I, U2)) {
            puts("... e eh subconjunto proprio...");
        } else {
            puts("... MAS NAO EH subconjunto proprio (ERRO)!???");
        }
    } else {
        puts("ERRO: (C3 i C4) NAO estah contido em (C3 U C4)!??");

    }

    // Finaliza todos os conjuntos
    finaliza(U1);
    finaliza(U2);
    finaliza(V1);
    finaliza(V2);
    finaliza(D1);
    finaliza(D2);
    finaliza(I);
    finaliza(S);
    finaliza(P);
    finaliza(C1);
    finaliza(C2);
    finaliza(C3);
    finaliza(C4);

    free(data);
    free(pontos);

    return EXIT_SUCCESS;
}
