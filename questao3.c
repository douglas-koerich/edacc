void ordInsercao(struct inteiro* lista) {
	if (lista == NULL) return;
	struct inteiro* desord = lista->proximo;
	while (desord != NULL) {
        struct inteiro* orden;
		int aux = desord->numero;
		orden = desord->anterior;
		while (orden != NULL && aux > orden->numero) {
			orden->proximo->numero = orden->numero;
			orden = orden->anterior;
		}
		if (orden != NULL) {
			orden->proximo->numero = aux;
		}
		else {
			lista->numero = aux;
		}
		desord = desord->proximo;
	}
}

