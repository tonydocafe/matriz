
#include "matriz.h"
#include <stdio.h>

int main() {
    FILE *arquivo = fopen("entrada.txt", "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    int tamA = 0;
    int tamB = 0;

    
     Matriz* A = lerMatrizDoArquivo(arquivo, tamA);
     Matriz* B = lerMatrizDoArquivo(arquivo, tamB);
   
    fclose(arquivo);

    printf("Matriz A:\n");
    imprime_matriz(A);

    printf("\nMatriz B:\n");
    imprime_matriz(B);

    Matriz* Z = multiplicacao(A, B);
    
    printf("\nResultado da multiplicacao:\n");
    imprime_matriz(Z);
    
    
    double diagoA = soma_diagonal_superior(A);
    double diagoB = soma_diagonal_superior(B);
    printf("\na soma da diagonal superior da matriz \nA : %.1lf \nB : %.1lf\n",diagoA,diagoB);
  
    
    
    printf("\naltere um numero na matriz A:");
 
    
    altera_elemento(A);

    
    printf("\naltere um numero na matriz B:");

    
    altera_elemento(B);

    printf("\ndigite um escalar para multiplicar as matrizes:\n");
    double escalar;
    scanf("%lf",&escalar);
    multiplicacao_escalar(A,escalar);
    imprime_matriz(A);
    printf("\n");
    multiplicacao_escalar(B,escalar);
    imprime_matriz(B);
    printf("\n");
    Matriz* transpostaA = transposta(A);
    Matriz* transpostaB = transposta(B);
    
    printf("\nTransposta A:\n");
    imprime_matriz(transpostaA);

    printf("\nTransposta B:\n");
    imprime_matriz(transpostaB);

    Matriz* S = soma_matriz(A,B);
    printf("\nA soma das matrizes fica:\n");
    imprime_matriz(S);

    Matriz* T = subtrai_matriz(A,B);
    printf("\n A subtração das matrizes fica:\n");
    imprime_matriz(T);

    double determinanteA = determinante(A);
    printf("\n O determinante da Matriz A é:\n %lf", determinanteA);
    
    double determinanteB = determinante(B);
    printf("\n O determinante da Matriz A é:\n %lf", determinanteB);

    

    
    destroi_matriz(A);
    destroi_matriz(B);
    destroi_matriz(Z);

    return 0;
}
