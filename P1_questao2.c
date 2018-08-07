/* struct no {
 * 	int valor;
 * 	struct no* proximo;
 * };
 * typedef struct no No;
 * typedef struct no* Lista;
 */

void minmax(const Lista* l, No** min, No** max) {
	No* q = *l;
	*min = *max = *l;
	while (q != NULL) {
		if (q->valor > (*max)->valor) {
			*max = q;
		}
		if (q->valor < (*min)->valor) {
			*min = q;
		}
		q = q->proximo;
	}
}

