#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "record.h"
#include "search.h"

int main(void) {
    const size_t TAMANHO_DICIO = 13, // recomendavel que seja um numero primo
                 NUM_REGISTROS = 40;

    puts("Criando dicionario:");
    Dictionary* dicio = create(TAMANHO_DICIO);

    puts("Gerando registros:");
    int n;
    for (n = 1; n <= NUM_REGISTROS; ++n) {
        srand((unsigned) time(NULL));
        Record registro = { rand() % 99 + 1, rand() % 26 + 'A' };
        printf("{%d,%c} ", registro.key, registro.value);
        fflush(stdout);
        insert(dicio, &registro);
        sleep(1);
    }

    puts("\n\nConteudo do dicionario");
    print(dicio);

    printf("Digite uma chave para buscar: ");
    int chave;
    scanf("%d", &chave);

    Record* registro = find(dicio, chave);
    if (registro == NULL) {
        puts("Chave nao encontrada");
    } else {
        printf("O caractere correspondente eh %c\n", registro->value);
    }

    destroy(dicio);

    return EXIT_SUCCESS;
}