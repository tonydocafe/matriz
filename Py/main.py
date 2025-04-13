from matriz import Matriz

def ler_duas_matrizes(caminho):
    with open(caminho, 'r') as f:
        linhas = [linha.strip() for linha in f.readlines()]
    
    tam = int(linhas.pop(0))
    matriz_a = Matriz(tam, tam)
    for i in range(tam):
        matriz_a.matriz[i] = list(map(float, linhas.pop(0).split()))
    
    tam_b = int(linhas.pop(0))
    matriz_b = Matriz(tam_b, tam_b)
    for i in range(tam_b):
        matriz_b.matriz[i] = list(map(float, linhas.pop(0).split()))
    
    return matriz_a, matriz_b
