int soma(int* vetor, size_t tamanho) { // tamanho = "n"
    // (E) (L)
    int s = 0; /* 2 */
    int i; // simples declaracao nao eh considerada
    //  (E) (L) <-- apenas 1 vez, no inicio do laco
    //         (L) (C) (L) <-- (tamanho+1) vezes
    //                      (E) (L) (A) (L) <-- (tamanho) vezes
    for (i = 0; i < tamanho; i = i + 1) { /* 2 + 3(n+1) + 4n */
    // (E) (L) (A) ...
        s = s + vetor[i]; /* 7n */
              // (L) do vetor (endereco do inicio)
              // (L) de i para alcancar a posicao
              // (I) para atingir a posicao desejada
              // (L) de vetor[i], i.e., do valor na posicao
    }
    // (R) (L)
    return s; /* 2 */
}

// T(n) = 14n + 9 <-- funcao de complexidade do algoritmo "soma"
// Analise do pior caso (assintotica): complexidade O(n)

/* Categorias de operacoes fundamentais:
 * (A)ritmeticas
 * (C)omparacoes
 * Algebra (B)ooleana (operacoes logicas)
 * (E/L) escrita ou leitura na/da memoria
 * [I]ndexacao/enderecamento (acesso a um campo de struct)
 * Chamada de (F)uncao
 * (R)etorno de funcao
