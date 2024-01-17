#ifndef MATRIZ_H
#define MATRIZ_H
#include <stdio.h> 
typedef struct {
    int m;
    int n;
    double **matriz;
} Matriz;

Matriz* cria_matriz(int m, int n);
void multiplicacao_escalar(Matriz* M, double escalar);
double soma_diagonal_superior(Matriz* M);
Matriz* multiplicacao(Matriz* M, Matriz* N);
void altera_elemento(Matriz* M, int m, int n, double novo_valor);
void destroi_matriz(Matriz* M);
void imprime_matriz(Matriz* M);
Matriz* lerMatrizDoArquivo(FILE *arquivo, int tam);
   

#endif
