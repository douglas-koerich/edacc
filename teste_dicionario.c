#include <stdlib.h>
#include <stdio.h>
#include "registro.h"
#include "dicionario.h"

void imprime(Registro* v, size_t n) {
    int i = 0;
    while (i < n) {
        printf("<%d,%c> ", (v+i)->chave, (v+i)->valor);
        // printf("<%d,%c> ", v[i].chave, v[i].valor);
        ++i;
    }
    putchar('\n');
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de parametros");
        printf("Uso: %s <numero-de-registros>\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t num_registros = atoi(argv[1]);

    Registro* vetor = malloc(sizeof(Registro) * num_registros);
    srand(20210609);
    int i;
    for (i = 0; i < num_registros; ++i) {
        vetor[i].chave = rand() % 999 + 1; // faixa de 1 a 999
        vetor[i].valor = rand() % 26 + 'A'; // faixa de 'A' a 'Z'
    }
    imprime(vetor, num_registros);

    Hash* dicionario = h_create();

    for (i = 0; i < num_registros; ++i) {
        h_insert(dicionario, vetor + i);
    }

    free(vetor);

    puts("Conteudo do dicionario:");
    h_print(dicionario);

    printf("Digite uma chave para buscar no conjunto de elementos: ");
    int chave;
    scanf("%d", &chave);

    Registro* r = h_search(dicionario, chave);
    if (r == NULL) {
        puts("Chave nao encontrada no conjunto de dados");
    } else {
        printf("Chave encontrada com valor associado '%c'\n", r->valor);
    }

    h_destroy(dicionario);

    return EXIT_SUCCESS;
}