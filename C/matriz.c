#include"matriz.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

Matriz* cria_matriz(int m, int n){
    Matriz *M = (Matriz*)malloc(sizeof(Matriz));
    M->matriz = (double**)malloc(m * sizeof(double*));
    for(int i=0; i < m; i++){
        M->matriz[i] = (double*)malloc(n*sizeof(double));
        for(int j = 0; j < n; j++){
            M->matriz[i][j] = 0;
        }
    }
    M->m = m;
    M->n = n;

    return M;
}

void multiplicacao_escalar(Matriz* M, double escalar){
    for (int i = 0; i < M->m; i++){
        for(int j = 0; j < M->n; j++){
            M->matriz[i][j] = escalar * M->matriz[i][j];
        }
    }
}



double soma_diagonal_superior(Matriz* M){
    double soma = 0;
    for(int i = 0; i<M->m; i++){
        for(int j = i+1; j<M->n; j++){
                soma+=M->matriz[i][j];
        }
    }
    return soma;
}


Matriz* multiplicacao(Matriz* M,Matriz* N){
    Matriz *Z = cria_matriz(M->m, N->n);
    double somaprod=0;
    for(int i=0; i<M->m; i++){
        for(int j=0; j<N->n; j++){
            somaprod = 0;
        for(int k=0; k<M->m; k++)
            somaprod+=M->matriz[i][k]*N->matriz[k][j];
        Z->matriz[i][j] = somaprod;
        }
    }
    return Z;
}



void altera_elemento(Matriz* M){
  
   int recebe_n = 1;
   int m, n;
   double novo_valor;
   while (recebe_n > 0){
        
        printf("\nlinha:");
        scanf("%i",&m);
        
        printf("coluna:");
        scanf("%i",&n);
        
        printf("novo numero:");
        scanf("%lf",&novo_valor);

        if (m && n == 0){
            M->matriz[m][n] = novo_valor;
        }else{
            M->matriz[m-1][n-1] = novo_valor;
        }

        printf("Deseja ver a matriz ?(Digite 1)\nDeseja Alterar mais numeros ?(Digite 2)\nDeseja continuar com as operações digite ? (Digite 0)\n");
        scanf("%i",&recebe_n);
        
        if (recebe_n == 1){
            printf("\nMatriz com novo valor fica:\n");    
            imprime_matriz(M);
        }

    }
}
Matriz* lerMatrizDoArquivo(FILE *arquivo, int tam) {
   
    fscanf(arquivo, "%d", &tam);
    Matriz* M = cria_matriz(tam, tam);
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            fscanf(arquivo, "%lf", &M->matriz[i][j]);
        }
    }

    return M;
}


void destroi_matriz(Matriz* M){
    for(int i = 0; i < M->m; i++){
        free(M->matriz[i]);
    }
    free(M->matriz);
    free(M);
    }

void imprime_matriz(Matriz* M){
    for(int i = 0; i < M->m; i++){
        for(int j = 0; j < M->n; j++){
            printf("%.1lf|",M->matriz[i][j]);
        }
        printf("\n");
    }
}

Matriz* soma_matriz(Matriz* A, Matriz* B) {
    if (A->m != B->m || A->n != B->n) {
        printf("Erro: Matrizes de tamanhos diferentes.\n");
        return NULL;
    }
    Matriz* C = cria_matriz(A->m, A->n);
    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j < A->n; j++) {
            C->matriz[i][j] = A->matriz[i][j] + B->matriz[i][j];
        }
    }
    return C;
}

Matriz* subtrai_matriz(Matriz* A, Matriz* B) {
    if (A->m != B->m || A->n != B->n) {
        printf("Erro: Matrizes de tamanhos diferentes.\n");
        return NULL;
    }
    Matriz* C = cria_matriz(A->m, A->n);
    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j < A->n; j++) {
            C->matriz[i][j] = A->matriz[i][j] - B->matriz[i][j];
        }
    }
    return C;
}


Matriz* transposta(Matriz* M) {
    Matriz* T = cria_matriz(M->n, M->m);
    for (int i = 0; i < M->m; i++) {
        for (int j = 0; j < M->n; j++) {
            T->matriz[j][i] = M->matriz[i][j];
        }
    }
    return T;
}

void salva_matriz_arquivo(Matriz* M, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "a");  
    if (!arquivo) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    fprintf(arquivo, "%d %d\n", M->m, M->n);
    for (int i = 0; i < M->m; i++) {
        for (int j = 0; j < M->n; j++) {
            fprintf(arquivo, "%.2lf ", M->matriz[i][j]);
        }
        fprintf(arquivo, "\n");
    }
    fprintf(arquivo, "\n"); 

    fclose(arquivo);
   
}


double determinante(Matriz* M) {
    if (M == NULL) {
        printf("Erro: Matriz nula.\n");
        return 0;
    }

    if (M->m != M->n) {
        printf("Erro: Determinante só pode ser calculado para matrizes quadradas.\n");
        return 0;
    }

    int n = M->m;


    if (n == 1) {
        return M->matriz[0][0];
    }

  
    if (n == 2) {
        return (M->matriz[0][0] * M->matriz[1][1]) - (M->matriz[0][1] * M->matriz[1][0]);
    }

 
    double det = 0;
    for (int j = 0; j < n; j++) {
        Matriz* subMatriz = cria_matriz(n - 1, n - 1);
        if (subMatriz == NULL) {
            printf("Erro ao alocar submatriz.\n");
            return 0;
        }

        for (int i = 1; i < n; i++) {
            int subCol = 0;
            for (int k = 0; k < n; k++) {
                if (k == j) continue;
                subMatriz->matriz[i - 1][subCol] = M->matriz[i][k];
                subCol++;
            }
        }

        double subDet = determinante(subMatriz);
        destroi_matriz(subMatriz);

        det += ((j % 2 == 0) ? 1 : -1) * M->matriz[0][j] * subDet;
    }

    return det;
}

int eh_identidade(Matriz* M) {
    if (M->m != M->n) return 0;
    for (int i = 0; i < M->m; i++) {
        for (int j = 0; j < M->n; j++) {
            if ((i == j && M->matriz[i][j] != 1) || (i != j && M->matriz[i][j] != 0)) {
                return 0;
            }
        }
    }
    return 1;
}

int eh_nilpotente(Matriz* A, int k) {
    Matriz* resultado = cria_matriz(A->m, A->n);
    for (int i = 0; i < A->m; i++)
        for (int j = 0; j < A->n; j++)
            resultado->matriz[i][j] = A->matriz[i][j];

    for (int i = 1; i < k; i++) {
        Matriz* temp = multiplicacao(resultado, A);
        destroi_matriz(resultado);
        resultado = temp;
    }
    int eh_zero = 1;
    for (int i = 0; i < resultado->m && eh_zero; i++) {
        for (int j = 0; j < resultado->n; j++) {
            if (resultado->matriz[i][j] != 0) {
                eh_zero = 0;
                break;
            }
        }
    }

    destroi_matriz(resultado);
    return eh_zero;
}



double traco(Matriz* M) {
    if (M->m != M->n) {
        printf("Traço só pode ser calculado para matrizes quadradas.\n");
        return 0;
    }
    double soma = 0;
    for (int i = 0; i < M->m; i++) {
        soma += M->matriz[i][i];
    }
    return soma;
}

int eh_simetrica(Matriz* M) {
    if (M->m != M->n) return 0;
    for (int i = 0; i < M->m; i++) {
        for (int j = 0; j < M->n; j++) {
            if (M->matriz[i][j] != M->matriz[j][i])
                return 0;
        }
    }
    return 1;
}

Matriz* potencia(Matriz* A, int expoente) {
    if (A->m != A->n) {
        printf("Erro: Potência só funciona com matrizes quadradas.\n");
        return NULL;
    }

    Matriz* resultado = cria_matriz(A->m, A->n);
    for (int i = 0; i < A->m; i++)
        resultado->matriz[i][i] = 1;

    for (int i = 0; i < expoente; i++) {
        Matriz* temp = multiplicacao(resultado, A);
        destroi_matriz(resultado);
        resultado = temp;
    }

    return resultado;
}

Matriz* oposta(Matriz* M) {
    Matriz* O = cria_matriz(M->m, M->n);
    for (int i = 0; i < M->m; i++) {
        for (int j = 0; j < M->n; j++) {
            O->matriz[i][j] = -M->matriz[i][j];
        }
    }
    return O;
}

Matriz* produto_hadamard(Matriz* A, Matriz* B) {
    if (A->m != B->m || A->n != B->n) {
        printf("Erro: Matrizes devem ter o mesmo tamanho para Hadamard.\n");
        return NULL;
    }

    Matriz* H = cria_matriz(A->m, A->n);
    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j < A->n; j++) {
            H->matriz[i][j] = A->matriz[i][j] * B->matriz[i][j];
        }
    }
    return H;
}
Matriz* inversa_gauss_jordan(Matriz* A) {
    if (A->m != A->n) {
        printf("Erro: A inversa só pode ser calculada para matrizes quadradas.\n");
        return NULL;
    }

    int n = A->m;
    Matriz* I = cria_matriz(n, n);
    Matriz* AI = cria_matriz(n, 2 * n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            AI->matriz[i][j] = A->matriz[i][j];
            AI->matriz[i][j + n] = (i == j) ? 1.0 : 0.0;
        }
    }

    printf("Matriz aumentada inicial [A | I]:\n");
    imprime_matriz(AI);

    for (int i = 0; i < n; i++) {
       
        if (AI->matriz[i][i] == 0.0) {
            int trocou = 0;
            for (int k = i + 1; k < n; k++) {
                if (AI->matriz[k][i] != 0.0) {
                    double* temp = AI->matriz[i];
                    AI->matriz[i] = AI->matriz[k];
                    AI->matriz[k] = temp;
                    trocou = 1;
                    printf("\nTrocou linha %d com linha %d:\n", i + 1, k + 1);
                    imprime_matriz(AI);
                    break;
                }
            }
            if (!trocou) {
                printf("Erro: Matriz singular, não possui inversa.\n");
                destroi_matriz(AI);
                destroi_matriz(I);
                return NULL;
            }
        }

        double pivo = AI->matriz[i][i];
        for (int j = 0; j < 2 * n; j++) {
            AI->matriz[i][j] /= pivo;
        }
        printf("\nLinha %d dividida pelo pivô %.2lf:\n", i + 1, pivo);
        imprime_matriz(AI);

    
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double fator = AI->matriz[k][i];
                for (int j = 0; j < 2 * n; j++) {
                    AI->matriz[k][j] -= fator * AI->matriz[i][j];
                }
                printf("\nEliminou elemento da linha %d usando linha %d (fator: %.2lf):\n", k + 1, i + 1, fator);
                imprime_matriz(AI);
            }
        }
    }

    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            I->matriz[i][j] = AI->matriz[i][j + n];
        }
    }

    destroi_matriz(AI);
    return I;
}
