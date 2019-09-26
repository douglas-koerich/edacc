bool eh_palindromo(unsigned numero) {
    bool palindromo = true;
    Pilha* aux = cria();
    unsigned digito, num = numero;
    while (num > 0) {
        digito = num % 10; // pega o digito da direita (menos significativo)
        push(aux, digito); // empilha o digito da vez
        num = num / 10;    // prepara para analisar o proximo
    }
    while (!underflow(aux)) {
        pop(aux, &digito); // retira o digito da vez (do ultimo para o primeiro)
        if (digito != numero % 10) { // digito nao bate com o seu
                                     // "equidistante" no numero?
            palindromo = false;
            break; // nao precisa mais continuar testando...
        }
        numero = numero / 10; // proximo algarismo do numero para comparar
                              // com o que tirar da pilha
    }
    destroi(aux);
    return palindromo;
}

