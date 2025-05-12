class Matriz:
    def __init__(self, m, n):
        self.m = m
        self.n = n
        self.matriz = [[0.0 for _ in range(n)] for _ in range(m)]


  @classmethod
    def ler_de_arquivo(cls, caminho):
        with open(caminho, 'r') as f:
            linhas = [linha.strip() for linha in f.readlines()]
        tamanho = int(linhas.pop(0))
        matriz = cls(tamanho, tamanho)
        for i in range(tamanho):
            matriz.matriz[i] = list(map(float, linhas[i].split()))
        return matriz



   def multiplicacao_escalar(self, escalar):
        for i in range(self.m):
            for j in range(self.n):
                self.matriz[i][j] *= escalar
                
   def soma_diagonal_superior(self):
        soma = 0.0
        for i in range(self.m):
            for j in range(i + 1, self.n):
                soma += self.matriz[i][j]
        return soma


    @staticmethod
    def multiplicacao(a, b):
        if a.n != b.m:
            raise ValueError("Dimensões incompatíveis")
        resultado = Matriz(a.m, b.n)
        for i in range(a.m):
            for j in range(b.n):
                soma = 0.0
                for k in range(a.n):
                    soma += a.matriz[i][k] * b.matriz[k][j]
                resultado.matriz[i][j] = soma
        return resultado


    def alterar_elemento(self):
        while True:
            m = int(input("linha: "))
            n = int(input("coluna: "))
            valor = float(input("novo número: "))
            self.matriz[m - 1][n - 1] = valor

            opcao = int(input("Deseja ver a matriz? (1), alterar mais? (2), sair? (0): "))
            if opcao == 1:
                self.imprime()
            if opcao == 0:
                break

    def imprime(self):
            for linha in self.matriz:
                print(" | ".join(f"{e:.1f}" for e in linha))


    @staticmethod
    def soma(a, b):
        if a.m != b.m or a.n != b.n:
            raise ValueError("Tamanhos diferentes")
        resultado = Matriz(a.m, a.n)
        for i in range(a.m):
            for j in range(a.n):
                resultado.matriz[i][j] = a.matriz[i][j] + b.matriz[i][j]
        return resultado

     @staticmethod
     def subtrai(a, b):
        if a.m != b.m or a.n != b.n:
            raise ValueError("Tamanhos diferentes")
        resultado = Matriz(a.m, a.n)
        for i in range(a.m):
            for j in range(a.n):
                resultado.matriz[i][j] = a.matriz[i][j] - b.matriz[i][j]
        return resultado

    def transposta(self):
            resultado = Matriz(self.n, self.m)
            for i in range(self.m):
                for j in range(self.n):
                    resultado.matriz[j][i] = self.matriz[i][j]
            return resultado


    def salva_em_arquivo(self, nome_arquivo):
        with open(nome_arquivo, 'a') as f:
            f.write(f"{self.m} {self.n}\n")
            for linha in self.matriz:
                f.write(" ".join(f"{e:.2f}" for e in linha) + "\n")
            f.write("\n")

    def determinante(self):
        if self.m != self.n:
            raise ValueError("Matriz não quadrada")
        if self.m == 1:
            return self.matriz[0][0]
        if self.m == 2:
            return self.matriz[0][0] * self.matriz[1][1] - self.matriz[0][1] * self.matriz[1][0]

        det = 0.0
        for j in range(self.n):
            sub = self.submatriz(0, j)
            det += ((-1) ** j) * self.matriz[0][j] * sub.determinante()
        return det

    def submatriz(self, linha_excluida, coluna_excluida):
        nova = Matriz(self.m - 1, self.n - 1)
        nova_linha = 0
        for i, linha in enumerate(self.matriz):
            if i == linha_excluida:
                continue
            nova_coluna = 0
            for j, valor in enumerate(linha):
                if j == coluna_excluida:
                    continue
                nova.matriz[nova_linha][nova_coluna] = valor
                nova_coluna += 1
            nova_linha += 1
        return nova

    def eh_nilpotente(self, k):
        atual = self
        for _ in range(k):
            atual = Matriz.multiplicacao(atual, self)
            if atual.nula():
                return True
        return False

    def nula(self):
        for i in range(self.m):
            for j in range(self.n):
                if self.matriz[i][j] != 0:
                    return False
        return True


     def eh_identidade(self):
            if self.m != self.n:
                return False
            for i in range(self.m):
                for j in range(self.n):
                    if i == j and self.matriz[i][j] != 1:
                        return False
                    if i != j and self.matriz[i][j] != 0:
                        return False
            return True

    def traco(self):
        if self.m != self.n:
            raise ValueError("Matriz não quadrada")
        return sum(self.matriz[i][i] for i in range(self.m))

    def eh_simetrica(self):
        if self.m != self.n:
            return False
        for i in range(self.m):
            for j in range(self.n):
                if self.matriz[i][j] != self.matriz[j][i]:
                    return False
        return True

    def oposta(self):
        resultado = Matriz(self.m, self.n)
        for i in range(self.m):
            for j in range(self.n):
                resultado.matriz[i][j] = -self.matriz[i][j]
        return resultado

    @staticmethod
    def produto_hadamard(a, b):
        if a.m != b.m or a.n != b.n:
            raise ValueError("Tamanhos diferentes")
        resultado = Matriz(a.m, a.n)
        for i in range(a.m):
            for j in range(a.n):
                resultado.matriz[i][j] = a.matriz[i][j] * b.matriz[i][j]
        return resultado


def inversa_gauss_jordan(self):
    if self.m != self.n:
        print("Erro: A inversa só pode ser calculada para matrizes quadradas.")
        return None

    n = self.m
    AI = [[0.0 for _ in range(2 * n)] for _ in range(n)]

    for i in range(n):
        for j in range(n):
            AI[i][j] = self.matriz[i][j]
            AI[i][j + n] = 1.0 if i == j else 0.0

    print("Matriz aumentada inicial [A | I]:")
    Matriz.imprime_matriz_estatica(AI)

    for i in range(n):
        if AI[i][i] == 0.0:
            trocou = False
            for k in range(i + 1, n):
                if AI[k][i] != 0.0:
                    AI[i], AI[k] = AI[k], AI[i]
                    trocou = True
                    print(f"\nTrocou linha {i + 1} com linha {k + 1}:")
                    Matriz.imprime_matriz_estatica(AI)
                    break
            if not trocou:
                print("Erro: Matriz singular, não possui inversa.")
                return None

        pivo = AI[i][i]
        AI[i] = [x / pivo for x in AI[i]]
        print(f"\nLinha {i + 1} dividida pelo pivô {pivo:.2f}:")
        Matriz.imprime_matriz_estatica(AI)

        for k in range(n):
            if k != i:
                fator = AI[k][i]
                AI[k] = [AI[k][j] - fator * AI[i][j] for j in range(2 * n)]
                print(f"\nEliminou elemento da linha {k + 1} usando linha {i + 1} (fator: {fator:.2f}):")
                Matriz.imprime_matriz_estatica(AI)

    inversa = Matriz(n, n)
    for i in range(n):
        for j in range(n):
            inversa.matriz[i][j] = AI[i][j + n]

    return inversa

