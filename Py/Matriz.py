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
