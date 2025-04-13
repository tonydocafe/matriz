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

escalar = float(input("\nDigite um escalar para multiplicar as matrizes:\n"))

A.multiplicacao_escalar(escalar)
print(f"\nMatriz A * {escalar}:")
A.imprime()

B.multiplicacao_escalar(escalar)
print(f"\nMatriz B * {escalar}:")
B.imprime()

transpostaA = A.transposta()
transpostaB = B.transposta()


B.multiplicacao_escalar(escalar)
print(f"\nMatriz B * {escalar}:")
B.imprime()


print("\nTransposta A:")
transpostaA.imprime()
transpostaA.salva_em_arquivo("saida.txt")

print("\nTransposta B:")
transpostaB.imprime()
transpostaB.salva_em_arquivo("saida.txt")


soma = Matriz.soma(A, B)
print("\nA soma das matrizes é:")
soma.imprime()
soma.salva_em_arquivo("saida.txt")


subtracao = Matriz.subtrai(A, B)
print("\nA subtração das matrizes é:")
subtracao.imprime()
subtracao.salva_em_arquivo("saida.txt")


print("\nDeterminante A:")
A.imprime()
print(f"\nDeterminante: {A.determinante()}")

print("\nDeterminante B:")
B.imprime()
print(f"\nDeterminante: {B.determinante()}")

print(f"\nA é identidade? {'Sim' if A.eh_identidade() else 'Não'}")
print(f"B é identidade? {'Sim' if B.eh_identidade() else 'Não'}")

print(f"\nA é simétrica? {'Sim' if A.eh_simetrica() else 'Não'}")
print(f"B é simétrica? {'Sim' if B.eh_simetrica() else 'Não'}")

print(f"\nTraço de A: {round(A.traco(), 1)}")
print(f"Traço de B: {round(B.traco(), 1)}")

print("\nA ao quadrado:")
potenciaA = Matriz.multiplicacao(A, A)
potenciaA.imprime()

print("\nB ao quadrado:")
potenciaB = Matriz.multiplicacao(B, B)
potenciaB.imprime()


print(f"\nA é nilpotente até k=3? {'Sim' if A.eh_nilpotente(3) else 'Não'}")
print(f"B é nilpotente até k=3? {'Sim' if B.eh_nilpotente(3) else 'Não'}")

print("\nMatriz oposta de A:")
A.oposta().imprime()

print("\nMatriz oposta de B:")
B.oposta().imprime()

print("\nProduto de Hadamard entre A e B:")
hadamard = Matriz.produto_hadamard(A, B)
hadamard.imprime()
