#ifndef MATRIZ_H
#define MATRIZ_H
#include <stdio.h> 
typedef struct {
    int m;
    int n;
    double **matriz;
} Matriz;

Matriz* cria_matriz(int m, int n);
void destroi_matriz(Matriz* M);
void imprime_matriz(Matriz* M);
void multiplicacao_escalar(Matriz* M, double escalar);
double soma_diagonal_superior(Matriz* M);
Matriz* multiplicacao(Matriz* M, Matriz* N);
void altera_elemento(Matriz* M);
Matriz* soma_matriz(Matriz* A, Matriz* B);
Matriz* subtrai_matriz(Matriz* A, Matriz* B);
Matriz* transposta(Matriz* M);
double determinante(Matriz* M);
void salva_matriz_arquivo(Matriz* M, const char* nomeArquivo);
Matriz* lerMatrizDoArquivo(FILE *arquivo, int tam);
int eh_identidade(Matriz* M);
int eh_nilpotente(Matriz* A, int k);
double traco(Matriz* M);
int eh_simetrica(Matriz* M);
Matriz* potencia(Matriz* A, int expoente);
Matriz* oposta(Matriz* M);
Matriz* produto_hadamard(Matriz* A, Matriz* B);
Matriz* inversa_gauss_jordan(Matriz* A) ;
#endif
