#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#include <vector>
#include <string>
#include <iostream>

class Matriz {
private:
    int m;
    int n;
    std::vector<std::vector<double>> matriz;

public:
  
    Matriz(int m, int n);
    ~Matriz() = default;

 
    void imprime() const;
    void multiplicacaoEscalar(double escalar);
    double somaDiagonalSuperior() const;
    double traco() const;
    double determinante() const;


    static Matriz* soma(const Matriz* A, const Matriz* B);
    static Matriz* subtrai(const Matriz* A, const Matriz* B);
    static Matriz* multiplicar(const Matriz* A, const Matriz* B);
    static Matriz* hadamard(const Matriz* A, const Matriz* B);
    static Matriz* potencia(const Matriz* A, int expoente);
    static bool ehNilpotente(const Matriz* A, int k);


    Matriz* transposta() const;
    Matriz* oposta() const;
    void alteraElemento();

 
    bool ehIdentidade() const;
    bool ehSimetrica() const;

  
    static Matriz* lerDoArquivo(std::ifstream& arquivo, int tam);
    void salvarEmArquivo(const std::string& nomeArquivo) const;

    int linhas() const { return m; }
    int colunas() const { return n; }
    double get(int i, int j) const { return matriz[i][j]; }
    void set(int i, int j, double valor) { matriz[i][j] = valor; }
};

#endif 
