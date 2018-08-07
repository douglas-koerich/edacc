// Do enunciado...
struct noh {
    int valor;
    struct noh* proximo;
};
typedef struct noh noh;

// Neste exercicio, nao vamos elaborar uma estrutura a parte para
// definir o TAD; ao inves, uma lista pode ser simplesmente vista
// como o ponteiro do primeiro 'noh'
typedef noh lista;  // ponteiro pra lista eh o ponteiro pra cabeca

// (... demais operacoes do TAD: cria, destroi, insere, etc. ...)

bool eh_igual(const lista* l1, const lista* l2) {
    if (underflow(l1)) {        // se a primeira lista estah vazia
        return underflow(l2);   // considera 'igual' se a segunda
                                // tambem estah...
    } else if (underflow(l2)) {
        return false;           // soh existe a primeira lista
    }
    // Ambas nao estao vazias...
    noh* n1 = (noh*) l1;    // apesar da linha 11, evitamos warnings
    noh* n2 = (noh*) l2;    // idem
    while (n1 != NULL && n2 != NULL) {
        if (n1->valor != n2->valor) {
            return false;   // encontrei discrepancia entre valores
        }
        n1 = n1->proximo;
        n2 = n2->proximo;
    }
    return n1 == NULL && n2 == NULL;    // testa pra ver se alguma
                                        // lista ainda ficou por
                                        // ser percorrida, i.e., eh
                                        // maior que a outra
}

