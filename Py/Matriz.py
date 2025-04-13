class Matriz:
    def __init__(self, m, n):
        self.m = m
        self.n = n
        self.matriz = [[0.0 for _ in range(n)] for _ in range(m)]
