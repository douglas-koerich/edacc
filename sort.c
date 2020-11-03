#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "queue_rec.h"
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

void shell(Record* v, size_t n) {
    const size_t NUM_INCREMENTS = 32;
    int increments[NUM_INCREMENTS], i, h;
    for (i = 0, h = 1; i < NUM_INCREMENTS; ++i) {
        increments[i] = h;
        h = 3 * h + 1;
        if (h > n) {
            break;
        }
    }
    Record* r = malloc(sizeof(Record));
    while (--i >= 0) {
        h = increments[i];
        int s;
        for (s = 0; s < h; ++s) {
            int j;
            for (j = s; j < n; j += h) {
                memcpy(r, v + j, sizeof(Record));
                int k;
                for (k = j - h; k >= s && v[k].key > r->key; k -= h) {
                    memcpy(v + k + h, v + k, sizeof(Record));
                }
                memcpy(v + k + h, r, sizeof(Record));
            }
        }
    }
    free(r);
}

void radix(Record* v, size_t n) {
    const size_t NUM_QUEUES = 10;
    Queue* queues[NUM_QUEUES];
    int i;
    for (i = 0; i < NUM_QUEUES; ++i) {
        queues[i] = create(n);
    }

    const int MAX_DIGITS = log10(INT_MAX) + 1;
    for (i = 1; i <= MAX_DIGITS; ++i) {
        int j;
        for (j = 0; j < n; ++j) {
            int digit = (v[j].key / (int) pow(10, i - 1)) % 10;
            enqueue(queues[digit], v + j);
        }
        int d;
        for (d = j = 0; d < NUM_QUEUES; ++d) {
            while (!underflow(queues[d])) {
                Record* record = dequeue(queues[d]);
                memcpy(v + j, record, sizeof(Record));
                free(record);
                ++j;
            }
        }
    }

    for (i = 0; i < NUM_QUEUES; ++i) {
        destroy(queues[i]);
    }
}

void merge(Record* v, int l, int u) {
    if (l >= u) {
        return;
    }
    int m = (l + u) / 2;
    merge(v, l, m);
    merge(v, m + 1, u);

    size_t s = u - l + 1;
    Record* w = malloc(sizeof(Record) * s);
    int i = l, j = m + 1, k = 0;
    while (i <= m && j <= u) {
        if (v[i].key < v[j].key) {
            memcpy(w + k++, v + i++, sizeof(Record));
        } else {
            memcpy(w + k++, v + j++, sizeof(Record));
        }
    }
    while (i <= m) {
        memcpy(w + k++, v + i++, sizeof(Record));
    }
    while (j <= u) {
        memcpy(w + k++, v + j++, sizeof(Record));
    }
    memcpy(v + l, w, sizeof(Record) * s);
    free(w);
}

void quick(Record* v, int l, int u) {
    if (l > u) {
        return;
    }
    int ref = v[(l + u) / 2].key;
    int i = l, j = u;
    while (i <= j) {
        while (v[i].key < ref) ++i;
        while (v[j].key > ref) --j;
        if (i <= j) {
            swap(v + i++, v + j--);
        }
    }
    quick(v, l, j);
    quick(v, i, u);
}
