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
arquivo = "entrada.txt"

try:
    with open(arquivo): pass
except FileNotFoundError:
    print("Erro ao abrir o arquivo.")
    exit(1)

A, B = ler_duas_matrizes(arquivo)

print("Matriz A:")
A.imprime()

print("\nMatriz B:")
B.imprime()


Z = Matriz.multiplicacao(A, B)
print("\nResultado da multiplicação:")
Z.imprime()


diagoA = A.soma_diagonal_superior()
diagoB = B.soma_diagonal_superior()
print("\nSoma da diagonal superior:")
print(f"A: {round(diagoA, 1)}")
print(f"B: {round(diagoB, 1)}")

print("\nAltere um número na matriz A:")
A.alterar_elemento()

print("\nAltere um número na matriz B:")
B.alterar_elemento()


