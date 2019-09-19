/* Este exercicio aproveita a definicao (prototipo) da operacao "comprimento"
 * definida no arquivo-cabecalho do TAD (v. lista.h). Sua implementacao deve
 * ser incluida no(s) arquivo(s)-fonte(s) lista_xxx.c, uma vez que a operacao
 * precisa conhecer a estrutura interna <Lista>. */

size_t comprimento(const Lista* l) {
    if (l == NULL) {
        return 0;
    }
    // Chamada a operacao recursiva de calculo do comprimento da lista
    return comprimento_r(l->cabeca);
}

/* Esta funcao eh a verdadeira operacao recursiva solicitada pelo exercicio,
 * e pra isso percorre os nohs da lista em sequencia recursiva */
size_t comprimento_r(const Noh* n) {
    if (n == NULL) {
        return 0;
    }
    return 1 + comprimento_r(n->proximo);
}

