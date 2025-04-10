#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>


class Matriz {
public:
    int m, n;
    std::vector<std::vector<double>> dados;

    Matriz(int m, int n) : m(m), n(n), dados(m, std::vector<double>(n, 0)) {}

    void imprime() const {
        for (const auto& linha : dados) {
            for (double valor : linha) {
                std::cout << std::fixed << std::setprecision(1) << valor << "|";
            }
            std::cout << "\n";
        }
    }

    void multiplicarEscalar(double escalar) {
        for (auto& linha : dados)
            for (auto& valor : linha)
                valor *= escalar;
    }

    double somaDiagonalSuperior() const {
        double soma = 0;
        for (int i = 0; i < m; i++)
            for (int j = i + 1; j < n; j++)
                soma += dados[i][j];
        return soma;
    }

    static Matriz* multiplicar(const Matriz* A, const Matriz* B) {
        if (A->n != B->m) return nullptr;
        Matriz* C = new Matriz(A->m, B->n);
        for (int i = 0; i < A->m; i++) {
            for (int j = 0; j < B->n; j++) {
                for (int k = 0; k < A->n; k++) {
                    C->dados[i][j] += A->dados[i][k] * B->dados[k][j];
                }
            }
        }
        return C;
    }

    void alteraElemento() {
        int recebe_n = 1;
        while (recebe_n > 0) {
            int linha, coluna;
            double novo_valor;
            std::cout << "\nlinha: ";
            std::cin >> linha;
            std::cout << "coluna: ";
            std::cin >> coluna;
            std::cout << "novo numero: ";
            std::cin >> novo_valor;

            if (linha && coluna == 0) {
                dados[linha][coluna] = novo_valor;
            } else {
                dados[linha - 1][coluna - 1] = novo_valor;
            }

            std::cout << "Deseja ver a matriz ?(1)\nAlterar mais numeros ?(2)\nContinuar com operações ? (0): ";
            std::cin >> recebe_n;

            if (recebe_n == 1) {
                std::cout << "Matriz com novo valor fica:\n";
                imprime();
            }
        }
    }

    static Matriz* lerDoArquivo(std::ifstream& arquivo, int tam) {
        arquivo >> tam;
        Matriz* M = new Matriz(tam, tam);
        for (int i = 0; i < tam; i++)
            for (int j = 0; j < tam; j++)
                arquivo >> M->dados[i][j];
        return M;
    }

    void salvarEmArquivo(const std::string& nomeArquivo) const {
        std::ofstream arquivo(nomeArquivo, std::ios::app);
        if (!arquivo) {
            std::cerr << "Erro ao abrir arquivo.\n";
            return;
        }
        arquivo << m << " " << n << "\n";
        for (const auto& linha : dados) {
            for (double valor : linha) {
                arquivo << std::fixed << std::setprecision(2) << valor << " ";
            }
            arquivo << "\n";
        }
        arquivo << "\n";
    }

    static Matriz* soma(const Matriz* A, const Matriz* B) {
        if (A->m != B->m || A->n != B->n) return nullptr;
        Matriz* C = new Matriz(A->m, A->n);
        for (int i = 0; i < A->m; i++)
            for (int j = 0; j < A->n; j++)
                C->dados[i][j] = A->dados[i][j] + B->dados[i][j];
        return C;
    }

    static Matriz* subtrai(const Matriz* A, const Matriz* B) {
        if (A->m != B->m || A->n != B->n) return nullptr;
        Matriz* C = new Matriz(A->m, A->n);
        for (int i = 0; i < A->m; i++)
            for (int j = 0; j < A->n; j++)
                C->dados[i][j] = A->dados[i][j] - B->dados[i][j];
        return C;
    }

    Matriz* transposta() const {
        Matriz* T = new Matriz(n, m);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                T->dados[j][i] = dados[i][j];
        return T;
    }

    double determinante() const {
        if (m != n) {
            std::cerr << "Erro: Determinante só para matrizes quadradas.\n";
            return 0;
        }

        if (n == 1) return dados[0][0];
        if (n == 2) return dados[0][0] * dados[1][1] - dados[0][1] * dados[1][0];

        double det = 0;
        for (int j = 0; j < n; j++) {
            Matriz subMatriz(n - 1, n - 1);
            for (int i = 1; i < n; i++) {
                int colSub = 0;
                for (int k = 0; k < n; k++) {
                    if (k == j) continue;
                    subMatriz.dados[i - 1][colSub++] = dados[i][k];
                }
            }
            det += ((j % 2 == 0) ? 1 : -1) * dados[0][j] * subMatriz.determinante();
        }
        return det;
    }

    bool ehIdentidade() const {
        if (m != n) return false;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if ((i == j && dados[i][j] != 1) || (i != j && dados[i][j] != 0))
                    return false;
        return true;
    }

    bool ehSimetrica() const {
        if (m != n) return false;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (dados[i][j] != dados[j][i])
                    return false;
        return true;
    }

    double traco() const {
        if (m != n) return 0;
        double soma = 0;
        for (int i = 0; i < m; i++)
            soma += dados[i][i];
        return soma;
    }

    static Matriz* potencia(const Matriz* A, int expoente) {
        if (A->m != A->n) return nullptr;
        Matriz* resultado = new Matriz(A->m, A->n);
        for (int i = 0; i < A->m; i++)
            resultado->dados[i][i] = 1;

        for (int i = 0; i < expoente; i++) {
            Matriz* temp = multiplicar(resultado, A);
            delete resultado;
            resultado = temp;
        }
        return resultado;
    }

    static bool ehNilpotente(const Matriz* A, int k) {
        Matriz* resultado = new Matriz(*A);
        for (int i = 1; i < k; i++) {
            Matriz* temp = multiplicar(resultado, A);
            delete resultado;
            resultado = temp;
        }
        for (const auto& linha : resultado->dados)
            for (double valor : linha)
                if (valor != 0) {
                    delete resultado;
                    return false;
                }
        delete resultado;
        return true;
    }

    Matriz* oposta() const {
        Matriz* O = new Matriz(m, n);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                O->dados[i][j] = -dados[i][j];
        return O;
    }

    static Matriz* hadamard(const Matriz* A, const Matriz* B) {
        if (A->m != B->m || A->n != B->n) return nullptr;
        Matriz* H = new Matriz(A->m, A->n);
        for (int i = 0; i < A->m; i++)
            for (int j = 0; j < A->n; j++)
                H->dados[i][j] = A->dados[i][j] * B->dados[i][j];
        return H;
    }
};
