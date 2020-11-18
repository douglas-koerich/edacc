#include <stdlib.h>
#include <string.h>
#include "search.h"

/*
algoritmo busca_sequencial(v, n, k)
  entrada Vetor v de n elementos, e uma chave k
  saida Indice da chave k no vetor v, ou invalido

        (M)   (R)    (M+A) -----------> 1 + (n+1) + 2n
  para i de 1 ateh n passo 1 faca
        (D)(D)   (R) -----------------> 3n
    se v[i].chave = k entao
        (M) --------------------------> 1 (*)
      retorna i
    fim-se
  fim-para
    (M) ------------------------------> 1 (**)
  retorna INV

  Duas situacoes de PIOR caso:
  (*)  A chave eh encontrada na ultima posicao
  (**) A chave nao eh encontrada

  T(n) = 6n + 3 (funcao de complexidade)
  O(n) - linear (ordem de complexidade)
*/

int sequential(const Record* v, size_t n, int k) {
    int i;
    for (i = 0; i < n; ++i) {
        if (v[i].key == k) {
            return i; // retorna indice onde encontrou a chave
        }
    }
    return -1; // indice INVALIDO (chave nao encontrada)
}

int binary(const Record* v, int l, int r, int k) {
    if (l > r) {
        return -1; // pela divisao sucessiva (e recursiva) do vetor, chegou-se a um segmento nulo
    }
    int m = (l + r) / 2; // busca binaria sempre avalia (compara) o elemento do meio do segmento
    if (v[m].key == k) {
        return m;
    }
    if (k < v[m].key) {
        return binary(v, l, m - 1, k);
    } else {
        return binary(v, m + 1, r, k);
    }
}

/*
algoritmo busca_binaria(v, l, r, k)
  entrada Segmento do vetor v do indice l ao indice r, e a chave k
  saida Indice onde a chave foi encontrada, ou INVALIDO

      (R) ----------------------------------> 1
  se l > r entao
      (M) ----------------------------------> 1 (**)
    retorna INV
  fim-se
    (M)  (A)  (A) --------------------------> 3
  m <- (l + r) / 2
      (D) (D)  (R) -------------------------> 3
  se v[m].chave = k entao
      (M) ----------------------------------> 1 (*)
    retorna m
  fim-se
      (R) (D)(D) ---------------------------> 3
  se k < v[m].chave entao
                T(n/2)             (A) -----> T(n/2) + 1
    retorna busca_binaria(v, l, m - 1, k)
  senao
                T(n/2)          (A) --------> T(n/2) + 1 (nao conta porque eh mutuamente exclusiva com acima)
    retorna busca_binaria(v, m + 1, r, k) 

  T(n) = 8          , se n = 1
       = T(n/2) + 11, se n > 1

  T(n) = T(n/2) + 11
       = T(n/4) + 11 + 11
       = T(n/8) + 11 + 11 + 11
       = ...
       = T(n/2^i) + i.11

  Para resolver a equacao, queremos que T(n/2^i) = T(1) = 8, cf. acima. Entao
    n/2^i = 1 --> i = log2(n) = lg(n)

  T(n) = 11.lg(n) + 8
  O(lg(n)) -> logaritmica
*/

int interpolation(const Record* v, int l, int r, int k) {
    if (l > r) {
        return -1;
    }
    /* Calculo de p considera a proporcionalidade entre as "distancias" entre chaves
     * e entre indices:
     * "A distancia de p para l (p - l) estah para a distancia entre k e a chave em l (dlk),
     * "ASSIM COMO
     * "a distancia de r para l (dlr) estah para a distancia entre a chave em r e a chave em l (dklkr)."
     */
    int p = l;
    float dlr = r - l, dklkr = v[r].key - v[l].key, dlk = k - v[l].key;
    if (dklkr > 0.0) { // as chaves nos extremos sao iguais (ou reduziu-se a um tamanho unitario)
        p = dlk * dlr / dklkr + l; // aplicacao da solucao "regra de 3"
    }
    if (v[p].key == k) {
        return p;
    }
    if (k < v[p].key) {
        return interpolation(v, l, p - 1, k);
    } else {
        return interpolation(v, p + 1, r, k);
    }
}

/******************************************************************************/
/* IMPLEMENTACAO DO TAD "Dictionary" (TABELA DE DISPERSAO/ESPALHAMENTO)       */
/******************************************************************************/

struct Dictionary_ {
    Record** vector; // vetor de ponteiros para os registros alocados dinamicamente
    size_t size;
};

Dictionary* create(size_t max_elements) {
    Dictionary* new_dict = malloc(sizeof(Dictionary));
    new_dict->size = max_elements;
    new_dict->vector = calloc(max_elements, sizeof(Record*)); // calloc() zera a memoria alocada
    return new_dict;
}

void destroy(Dictionary* dictionary) {
    int i;
    for (i = 0; i < dictionary->size; ++i) {
        free(dictionary->vector[i]); // se for NULL, nao acontece nada (v. man 3 free)
    }
    free(dictionary->vector);
    free(dictionary);
}

static int hashing(int key, size_t size) {
    int position;

    /*
    // Metodo da divisao
    position = key % size;
    */

    // Metodo pseudo-aleatorio
    srand(key); // usa a chave como semente
    position = rand() % size;

    return position;
}

void insert(Dictionary* dictionary, const Record* new_element) {
    int index = hashing(new_element->key, dictionary->size);
    dictionary->vector[index] = malloc(sizeof(Record));
    memcpy(dictionary->vector[index], new_element, sizeof(Record));
}

Record* discard(Dictionary* dictionary, int search_key) {
    int index = hashing(search_key, dictionary->size);
    Record* record = dictionary->vector[index];
    dictionary->vector[index] = NULL;
    return record; // a funcao que recebe esse ponteiro (para o registro) deve chamar free()
                   // ao nao precisar mais dele
}

Record* find(const Dictionary* dictionary, int search_key) {
    int index = hashing(search_key, dictionary->size);
    Record* duplicate = malloc(sizeof(Record));
    memcpy(duplicate, dictionary->vector[index], sizeof(Record));
    return duplicate; // a funcao que recebe esse ponteiro (para a duplicata) deve chamar free()
}
