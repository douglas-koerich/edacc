#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "fila.h"
#include "deque.h"

struct fila {
    deque* d;
};

fila* create(size_t max) {
    fila* nova = malloc(sizeof(fila));
    nova->d = d_create(max);
    return nova;
}

void destroy(fila* f) {
    if (f == NULL) {
        return;
    }
    d_destroy(f->d);
    free(f);
}

void insert(fila* f, int v) {
    if (f == NULL) {
        return;
    }
    d_insert(f->d, v, REAR);
}

int extract(fila* f) {
    if (d_underflow(f->d)) {
        return INT_MIN;
    }
    return d_extract(f->d, FRONT);
}

int inspect(const fila* f) {
    if (d_underflow(f->d)) {
        return INT_MIN;
    }
    return d_inspect(f->d, FRONT);
}

size_t size(const fila* f) {
    if (f == NULL) {
        return 0;
    }
    return d_size(f->d);
}

bool underflow(const fila* f) {
    return f == NULL || d_underflow(f->d);
}

void print(const fila* f) {
    if (f == NULL) {
        return;
    }
    if (d_underflow(f->d)) {
        puts("(VAZIA)");
        return;
    }
    d_print(f->d);
}

void save(const fila* f, const char* a) {
    if (f == NULL || a == NULL) {
        return;
    }
    FILE* s = fopen(a, "wb");
    if (s == NULL) {
        perror("Nao foi possivel criar o arquivo da fila");
        return;
    }
    // TODO: implementar usando o deque...

    fclose(s);
}

fila* restore(const char* a) {
    if (a == NULL) {
        return NULL;
    }
    FILE* s = fopen(a, "rb");
    if (s == NULL) {
        perror("Nao foi possivel abrir o arquivo da fila");
        return NULL;
    }
    const int MAX_FILA = 1000;
    fila* nova = create(MAX_FILA);
    while (!feof(s)) {
        int num;
        if (fread(&num, sizeof(int), 1, s) < 1) {
            if (ferror(s)) {
                perror("Erro na leitura do arquivo");
                return NULL;
            }
        } else {
            // TODO: implementar usando deque...
        }
    }
    fclose(s);

    return nova;
}
