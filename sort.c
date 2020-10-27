#include <stdlib.h>
#include <string.h>
#include "sort.h"

static void swap(Record* r1, Record* r2) {
    Record* rtemp = malloc(sizeof(Record));

    // Movimentacao de registros para ordenacao segundo a estrategia
    // de *contiguidade fisica*, i.e., todo o registro eh movido na memoria
    // junto com a chave que estah sendo reposicionada em relacao as demais

    memcpy(rtemp, r1, sizeof(Record));
    memcpy(r1, r2, sizeof(Record));
    memcpy(r2, rtemp, sizeof(Record));

    free(rtemp);
}

void bubble(Record* v, size_t n) {
    int r;
    for (r = 1; r < n; ++r) {
        int i;
        for (i = n - 1; i > 0; --i) {
            if (v[i - 1].key > v[i].key) {
                swap(v + i - 1, v + i);
            }
        }
    }
}

void selection(Record* v, size_t n) {
    int i;
    for (i = 0; i < n - 1; ++i) {
        int s = i, j;
        for (j = i + 1; j < n; ++j) {
            if (v[j].key < v[s].key) {
                s = j;
            }
        }
        swap(v + i, v + s);
    }
}

void insertion(Record* v, size_t n) {
    Record* r = malloc(sizeof(Record));
    int i;
    for (i = 1; i < n; ++i) {
        memcpy(r, v + i, sizeof(Record));
        int j;
        for (j = i - 1; j >= 0 && v[j].key > r->key; --j) {
            memcpy(v + j + 1, v + j, sizeof(Record));
        }
        memcpy(v + j + 1, r, sizeof(Record));
    }
    free(r);
}
