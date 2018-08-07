struct pilhaD {
	int* vetor;
	int max;
	int topo_inf, topo_sup;
};
typedef struct pilhaD DPilha;
enum lado { INFERIOR, SUPERIOR };
typedef enum lado Lado;

void inicia(DPilha* p, size_t N) {
	p->vetor = (int*) malloc(N * sizeof(int));
	p->max = N;
	p->topo_inf = -1;
	p->topo_sup = N;
}

void finaliza(DPilha* p) {
	p->max = 0;
	p->topo_inf = p->topo_sup = -1;
	free(p->vetor);
}

bool underflow(const DPilha* p, Lado l) {
	if (l == INFERIOR) return p->topo_inf == -1;
	else return p->topo_sup == p->max;
}

bool overflow(const DPilha* p) {
	return p->topo_sup-p->topo_inf == 1;
}

bool push(DPilha* p, Lado l, int novo) {
	if (overflow(p)) {
		return false;
	}
	if (l == INFERIOR) {
		p->vetor[++p->topo_inf] = novo;
	}
	else {
		p->vetor[--p->topo_sup] = novo;
	}
	return true;
}

bool pop(DPilha* p, Lado l, int* valor) {
	if (underflow(p, l)) {
		return false;
	}
	if (l == INFERIOR) {
		*valor = p->vetor[p->topo_inf--];
	}
	else {
		*valor = p->vetor[p->topo_sup++];
	}
	return true;
}

