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


void altera_elemento(Matriz* M, int m, int n, double novo_valor){
    M->matriz[m][n] = novo_valor;
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
            printf("%.1lf-",M->matriz[i][j]);
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
