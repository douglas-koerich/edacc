int somatorio(int x, int n) {
    int soma, i, j;
    for (soma = 0, i = 1, j = x+1; i <= n; ++i, ++j) {
        soma += j;
    }
    return soma;
}
