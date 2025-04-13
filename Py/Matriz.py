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
