#include "Matriz.hpp"
#include <iostream>
#include <fstream>

int main() {
    std::ifstream arquivo("entrada.txt");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    int tamA = 0;
    int tamB = 0;

    Matriz* A = Matriz::lerDoArquivo(arquivo, tamA);
    Matriz* B = Matriz::lerDoArquivo(arquivo, tamB);
    arquivo.close();

    std::cout << "Matriz A:\n";
    A->imprime();

    std::cout << "\nMatriz B:\n";
    B->imprime();

    Matriz* Z = Matriz::multiplicar(A, B);
    std::cout << "\nResultado da multiplicação:\n";
    Z->imprime();

    std::cout << "\nSoma da diagonal superior da matriz A: " << A->somaDiagonalSuperior() << "\n";
    std::cout << "Soma da diagonal superior da matriz B: " << B->somaDiagonalSuperior() << "\n";

    std::cout << "\nAltere um número na matriz A:\n";
    A->alteraElemento();

    std::cout << "\nAltere um número na matriz B:\n";
    B->alteraElemento();

    double escalar;
    std::cout << "\nDigite um escalar para multiplicar as matrizes:\n";
    std::cin >> escalar;

    A->multiplicacaoEscalar(escalar);
    A->imprime();

    B->multiplicacaoEscalar(escalar);
    B->imprime();

    Matriz* transpostaA = A->transposta();
    Matriz* transpostaB = B->transposta();

    std::cout << "\nTransposta A:\n";
    transpostaA->imprime();
    transpostaA->salvarEmArquivo("saida.txt");

    std::cout << "\nTransposta B:\n";
    transpostaB->imprime();
    transpostaB->salvarEmArquivo("saida.txt");

    Matriz* S = Matriz::soma(A, B);
    std::cout << "\nA soma das matrizes:\n";
    S->imprime();
    S->salvarEmArquivo("saida.txt");

    Matriz* T = Matriz::subtrai(A, B);
    std::cout << "\nA subtração das matrizes:\n";
    T->imprime();
    T->salvarEmArquivo("saida.txt");

    std::cout << "\nDeterminante da matriz A: " << A->determinante() << "\n";
    std::cout << "Determinante da matriz B: " << B->determinante() << "\n";

    std::cout << (A->ehIdentidade() ? "A matriz A é identidade.\n" : "A matriz A não é identidade.\n");
    std::cout << (Matriz::ehNilpotente(A, 3) ? "A matriz A é nilpotente até k=3.\n" : "A matriz A não é nilpotente.\n");

    std::cout << (A->ehSimetrica() ? "A matriz A é simétrica.\n" : "A matriz A não é simétrica.\n");
    std::cout << (B->ehSimetrica() ? "A matriz B é simétrica.\n" : "A matriz B não é simétrica.\n");

    Matriz* PA = Matriz::potencia(A, 2);
    std::cout << "\nA matriz A ao quadrado:\n";
    PA->imprime();

    Matriz* PB = Matriz::potencia(B, 2);
    std::cout << "\nA matriz B ao quadrado:\n";
    PB->imprime();

    Matriz* OA = A->oposta();
    std::cout << "\nA matriz A oposta:\n";
    OA->imprime();

    Matriz* OB = B->oposta();
    std::cout << "\nA matriz B oposta:\n";
    OB->imprime();

    Matriz* PAB = Matriz::hadamard(A, B);
    std::cout << "\nProduto de Hadamard (A .* B):\n";
    PAB->imprime();

    std::cout << "\nTraço da matriz A: " << A->traco() << "\n";
    std::cout << "Traço da matriz B: " << B->traco() << "\n";

    delete A;
    delete B;
    delete Z;
    delete S;
    delete T;
    delete transpostaA;
    delete transpostaB;
    delete PA;
    delete PB;
    delete OA;
    delete OB;
    delete PAB;

    return 0;
}
