int somatorio(int x, int n) {
    // Condicao terminal
    if (n == 0) {
        return 0; // nao existe chamada recursiva
    }
    // Fase ativa da recursividade
    int soma = (x+1) + somatorio(x+1, n-1); // chamada ah propria funcao
    return soma;
}

