// Versao iterativa (usual)
int maior(const int* v, size_t n) {
         // (M) (D) ------------------> 2
    int i, m = v[0];
       // (M) ------------------------> 1
    for (i = 1;//(R) -----------------> n (n-1 testes V + 1 teste F)
                i < n;//(M+A: i=i+1) -> n-1
                       ++i) {
          // (D)(R) ------------------> 2(n-1)
        if (v[i] > m) {
          // (M) (D) -----------------> 2(n-1)
            m = v[i];
        }
    }
    // (M) ---------------------------> 1
    return m;
}

// T(n) = 5(n-1) + n + 4 = 6n - 1
// Complexidade linear O(n)

/***********************************************************/

// Versao recursiva
int maior(const int* v, size_t n) {
      //  (R) -----------------------------> 1
    if (n == 1) {
        // (M)  (D) -----------------------> 2 // soh em condicao terminal
        return v[0];
    } else {
             // (M) (D) -------------------> 2 // soh em fase ativa
        int val1 = v[0];
             // (M)       (A)    (A) ------> 3 + T(n-1)
        int val2 = maior(v + 1, n - 1);
             // (R) -----------------------> 1
        if (val1 > val2) {
           // (M) -------------------------> 1
            return val1;
        } else {
           // NAO considera essa instrucao em T(n)
           // pois ela eh mutuamente exclusiva com
           // a instrucao: return val1;
            return val2;
        }
    }
}

// T(n) = 8 + T(n-1), se n > 1 ---> EQUACAO DE RECORRENCIA LINEAR (n diminui por subtracao)
//      = 3, caso contrario

// Metodo da expansao telescopica
// T(n) = 8 + T(n-1)
//            8 + T(n-2)
//                8 + T(n-3)
//                    8 + T(n-4)
// T(n) = 8 + 8 + 8 + 8 + T(n-4)
// T(n) = 8.i + T(n-i) ---> EXPRESSAO GERAL DE RECORRENCIA

// Se a formula acima eh valida ("geral") para todo T(n), entao
// eh valida tambem quando T(n-i) = T(1); nesse caso, T(1) = 3
// Entao, nesse caso, i deveria valer n-1, pois n-i=n-(n-1)=1
// Fazendo i = n-1 na expressao geral:

// T(n) = 8(n-1) + T(n-(n-1)) = 8n - 8 + T(1) = 8n - 5
// Complexidade linear O(n)

int maior2(const int* v, int i, int s) {
       // (R) -------------------------------> 1
    if (i == s) {
        // (M)  (D) -------------------------> 2 (condicao terminal)
        return v[i];
    } else {
          // (M)  (A)  (A) ------------------> 3 (fase ativa)
        int m = (i + s) / 2;
                // (M) ----------------------> 1 + T(n/2)
        int maior_i = maior2(v, i, m);
                // (M)          (A) ---------> 2 + T(n/2)
        int maior_s = maior2(v, m+1, s);
                // (R) ----------------------> 1
        if (maior_i > maior_s) {
            // (M) --------------------------> 1
            return maior_i;
        } else {
            return maior_s;
        }
    }
}

// T(n) = 9 + 2T(n/2), se n > 1 --> EQUACAO DE RECORRENCIA GEOMETRICA (n diminui por divisao)
//      = 3, caso contrario

// Novamente, usamos expansao telescopica
// T(n) = 9 + 2(9 + 2T(n/4)), ou 9 + (18 + 4T(n/4)) = 9(1 + 2) + 4T(n/4)
//      = 9 + 2(9 + 2(9 + 2T(n/8))), ou 9 + 2(9 + (18 + 4T(n/8))) = 9 + 18 + 36 + 8T(n/8) = 9(1 + 2 + 4) + 8T(n/8)
//      = 9 + 2(9 + 2(9 + 2(9 + 2T(n/16))))
// T(n) = 9(1 + 2 + 4 + ... + 2^(i-1)) + (2^i).T(n/(2^i))
//      = 9(2^0 + 2^1 + 2^2 + ... + 2^(i-1)) + (2^i).T(n/(2^i))
//      = 9(1.(2^i - 1)/(2-1)) + (2^i).T(n/(2^i))
//      = 9(2^i - 1) + (2^i).T(n/(2^i))
// T(n) = (2^i).T(n/(2^i)) + 9.2^i - 9 --> EXPRESSAO GERAL DE RECORRENCIA

// Se a formula acima eh valida ("geral") para todo T(n), entao
// eh valida tambem quando T(n/(2^i)) = T(1); nesse caso, T(1) = 3
// Entao, nesse caso, i deveria valer lg(n), pois n/(2^lg(n))=n/n=1
// Fazendo i = lg(n) na expressao geral:

// T(n) = (2^lg(n)).T(n/n) + 9.2^lg(n) - 9
//      = n.T(1) + 9.n - 9
// T(n) = 12n - 9
// Complexidade linear O(n)
