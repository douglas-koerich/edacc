void ordenar(Lista* l) {
    if (l == NULL || underflow(l)) {
        return;
    }
    // Esta implementacao utiliza o algoritmo de insercao aplicado aos nohs
    // de uma lista duplamente encadeada
    Noh* p;
    // Comeca no segundo noh da lista pois o primeiro nao tem com quem ser
    // comparado
    for (p = l->cabeca->proximo; p != NULL; p = p->proximo) {
        Reg* aux = malloc(sizeof(Reg));

        // Salva o registro original que vai ser reposicionado,
        // pois ele pode ser sobrescrito pelo deslocamento dos
        // outros
        memcpy(aux, &p->elemento, sizeof(Reg));

        Noh* a = p->anterior;
        while (a != NULL && // nao chegou no inicio E...
               a->elemento.chave > aux->chave) { // ... o anterior eh maior?
            memcpy(&a->proximo->elemento, &a->elemento, sizeof(Reg)); // "empurra"
                                                                      // o maior pra frente
            a = a->anterior;
        }
        // Poe o elemento que estava sendo comparado na sua
        // posicao final
        if (a == NULL) {
            memcpy(&l->cabeca->elemento, aux, sizeof(Reg));
        } else {
            memcpy(&a->proximo->elemento, aux, sizeof(Reg));
        }
        free(aux);
    }
}

