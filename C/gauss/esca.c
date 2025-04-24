#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 10
#define EPS 1e-6

void print_matriz(float mat[MAX][MAX], int lin, int col) {
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            printf("%7.2f ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void troca_linhas(float mat[MAX][MAX], int col, int l1, int l2) {
    float temp;
    for (int j = 0; j < col; j++) {
        temp = mat[l1][j];
        mat[l1][j] = mat[l2][j];
        mat[l2][j] = temp;
    }
    printf("L%d <-> L%d\n", l1+1, l2+1);
}

void multiplica_linha(float mat[MAX][MAX], int col, int l, float fator) {
    for (int j = 0; j < col; j++) {
        mat[l][j] *= fator;
    }
    printf("L%d <- %.2f * L%d\n", l+1, fator, l+1);
}

void soma_linha(float mat[MAX][MAX], int col, int l1, int l2, float fator) {
    for (int j = 0; j < col; j++) {
        mat[l1][j] += fator * mat[l2][j];
    }
    printf("L%d <- L%d + %.2f.L%d\n", l1+1, l1+1, fator, l2+1);
}

void escalonar_reduzida(float mat[MAX][MAX], int lin, int col) {
    int linha_pivo = 0;

    for (int j = 0; j < col && linha_pivo < lin; j++) {
        // Achar pivô
        int i_max = linha_pivo;
        for (int i = linha_pivo; i < lin; i++) {
            if (fabs(mat[i][j]) > fabs(mat[i_max][j])) {
                i_max = i;
            }
        }

        if (fabs(mat[i_max][j]) < EPS) continue; // coluna já zerada

        if (i_max != linha_pivo) {
            troca_linhas(mat, col, linha_pivo, i_max);
            print_matriz(mat, lin, col);
        }

        // Tornar pivô = 1
        float pivo = mat[linha_pivo][j];
        if (fabs(pivo - 1.0) > EPS) {
            multiplica_linha(mat, col, linha_pivo, 1.0 / pivo);
            print_matriz(mat, lin, col);
        }

        // Zerar acima e abaixo do pivô
        for (int i = 0; i < lin; i++) {
            if (i != linha_pivo && fabs(mat[i][j]) > EPS) {
                float fator = -mat[i][j];
                soma_linha(mat, col, i, linha_pivo, fator);
                print_matriz(mat, lin, col);
            }
        }

        linha_pivo++;
    }
}

int main() {
    int lin = 3, col = 5;
    float matriz[MAX][MAX] = {
        {0, 3, 5, 2, -1},
        {2, -1, 0, 1, -2},
        {3, 2, 3, 0, 0}
    };

    printf("Matriz original:\n");
    print_matriz(matriz, lin, col);

    escalonar_reduzida(matriz, lin, col);

    printf("Matriz escalonada reduzida:\n");
    print_matriz(matriz, lin, col);

    return 0;
}
