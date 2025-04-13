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
