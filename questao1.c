#include <stdbool.h>

bool funcao(int* A, size_t n, int i) {
	if (i >= n) {							// 1
		return false;
	}
	if (i >= 2) {							// 1
		int j = i-1, k = i-2;				// 2
		if (A[i] == A[j] + A[k])			// 5
			return true;
	}
	return funcao(A, n, i+1);				// FC(n-1) + 1
}											// ----------------------
											// FC(n) = FC(n-1) + 3
