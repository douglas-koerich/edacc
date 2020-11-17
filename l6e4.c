#include <stdlib.h>
#include "record.h"

size_t count(const Record* v, int l, int r, int k) {
    if (l > r) {
        return 0; // nenhuma ocorrencia pois chegou-se a um segmento nulo
    }
    int m = (l + r) / 2; // busca binaria sempre avalia (compara) o elemento do meio do segmento
    size_t c = 0;
    if (v[m].key == k) {
        size_t c = 1; // contabiliza esta ocorrencia (em m)
        int i = m - 1; // contabiliza as ocorrencias ah esquerda
        while (i >= l && v[i].key == k) {
            ++c, --i;
        }
        i = m + 1; // contabiliza as ocorrencias ah direita
        while (i <= r && v[i].key == k) {
            ++c, ++i;
        }
        return c;
    }
    if (k < v[m].key) {
        return count(v, l, m - 1, k);
    } else {
        return count(v, m + 1, r, k);
    }
}
