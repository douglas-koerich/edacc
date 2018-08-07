#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define RAND_DIR    3
#define RAND_PRINT  5
#define RAND_NMB    30
#define RAND_SIZE   4096

void gera_arvore(const char*, int);
int cria_arquivo(const char*);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Numero insuficiente de parametros");
        printf("Uso: %s <niveis-da-arvore>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int niveis = atoi(argv[1]);
    if (niveis > 5) {
        puts("CUIDADO! O numero de arquivos e diretorios pode ser muito grande!");
        char opcao;
        do {
            printf("Deseja continuar (S/N)? ");
            __fpurge(stdin);
            opcao = toupper(getchar());
        } while (opcao != 'S' && opcao != 'N');
        if (opcao == 'N') {
            return EXIT_FAILURE;
        }
    }
    srand((unsigned) time(NULL));
    char* raiz = strdup(getenv("PWD"));
    gera_arvore(raiz, niveis);
    free(raiz);

    return EXIT_SUCCESS;
}

void gera_arvore(const char* raiz, int niveis) {
    if (niveis == 0) {
        return;
    }
    int i, n = rand() % RAND_NMB;
    for (i=1; i<=n; ++i) {
        unsigned long long int iname = rand();
        char* sname;
        asprintf(&sname, "%s/%llx", raiz, iname);
        if (rand() % RAND_DIR == 0) {
            char* mdcmd;
            asprintf(&mdcmd, "mkdir -p %s", sname);
            system(mdcmd);
            free(mdcmd);

            gera_arvore(sname, niveis - 1);
            if (rand() % RAND_PRINT == 0) {
                puts(sname);
            }
        }
        else {
            int tamanho = cria_arquivo(sname);
            if (tamanho >= 0 && rand() % RAND_PRINT == 0) {
                printf("%s %d\n", sname, tamanho);
            }
        }
        free(sname);
    }
}

int cria_arquivo(const char* nome) {
    FILE* arquivo = fopen(nome, "wb");
    if (arquivo == NULL) {
        return -1;
    }
    int i, n = rand() % RAND_SIZE;
    for (i=0; i<n; ++i) {
        if (fputc(rand() % 0x100, arquivo) == EOF) {
            break;
        }
    }
    fclose(arquivo);
    return i;
}
