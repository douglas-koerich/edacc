void i_ordMerge(Registro_Exemplo vetor[], int n) {
	int comprimento = 2, segmentos;
	while (comprimento <= n) {
		segmentos = n / comprimento;
		if (n % comprimento > 0) ++segmentos;

		int s;
		for (s=0; s<segmentos; ++s) {
			int esq = s*comprimento,
				meio = esq + comprimento/2 - 1,
				dir = esq + comprimento - 1;
			if (dir >= n) dir = n-1;
			intercala(vetor, esq, meio, dir);
		}
		comprimento *= 2;
	}
	if (segmentos > 1) {
		intercala(vetor, 0, comprimento/2-1, n-1);
	}
}

