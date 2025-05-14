require_relative 'matriz'

def ler_duas_matrizes(caminho)
  linhas = File.readlines(caminho).map(&:strip)
  tam = linhas.shift.to_i

  matriz_a = Matriz.new(tam, tam)
  tam.times do |i|
    matriz_a.matriz[i] = linhas.shift.split.map(&:to_f)
  end

  tam_b = linhas.shift.to_i
  matriz_b = Matriz.new(tam_b, tam_b)
  tam_b.times do |i|
    matriz_b.matriz[i] = linhas.shift.split.map(&:to_f)
  end

  [matriz_a, matriz_b]
end

# -------- INÍCIO --------
arquivo = "entrada.txt"

unless File.exist?(arquivo)
  puts "Erro ao abrir o arquivo."
  exit 1
end


def inversa_passo_a_passo
  raise "Matriz não é quadrada!" unless @linhas == @colunas

  n = @linhas
  a = Marshal.load(Marshal.dump(@matriz))  # cópia profunda da matriz original
  identidade = Array.new(n) { |i| Array.new(n, 0.0).tap { |row| row[i] = 1.0 } }

  puts "\n--- Início do cálculo da inversa (Gauss-Jordan) ---"

  n.times do |i|
    # Verifica se o pivô é zero
    if a[i][i] == 0
      trocado = false
      (i + 1).upto(n - 1) do |j|
        if a[j][i] != 0
          a[i], a[j] = a[j], a[i]
          identidade[i], identidade[j] = identidade[j], identidade[i]
          puts "\nTrocando linha #{i} com linha #{j}:"
          trocado = true
          break
        end
      end
      raise "Matriz não possui inversa (pivô zero irremovível)" unless trocado
    end

    pivô = a[i][i]
    n.times do |j|
      a[i][j] /= pivô
      identidade[i][j] /= pivô
    end
    puts "\nLinha #{i} dividida por #{pivô}:"
    imprime_matrizes_lado_a_lado(a, identidade)

    n.times do |k|
      next if k == i
      fator = a[k][i]
      n.times do |j|
        a[k][j] -= fator * a[i][j]
        identidade[k][j] -= fator * identidade[i][j]
      end
      puts "\nEliminando elemento da linha #{k}, coluna #{i}:"
      imprime_matrizes_lado_a_lado(a, identidade)
    end
  end

  puts "\n--- Fim do cálculo da inversa ---"
  m = Matriz.new(n, n)
  m.matriz = identidade
  m
end

def imprime_matrizes_lado_a_lado(a, b)
  a.each_with_index do |linha_a, i|
    linha_b = b[i]
    puts "#{linha_a.map { |e| "%7.2f" % e }.join(" ")}  |  #{linha_b.map { |e| "%7.2f" % e }.join(" ")}"
  end
end




A, B = ler_duas_matrizes(arquivo)

puts "Matriz A:"
A.imprime

puts "\nMatriz B:"
B.imprime

Z = Matriz.multiplicacao(A, B)
puts "\nResultado da multiplicação:"
Z.imprime

diagoA = A.soma_diagonal_superior
diagoB = B.soma_diagonal_superior
puts "\nSoma da diagonal superior:"
puts "A: #{diagoA.round(1)}"
puts "B: #{diagoB.round(1)}"

puts "\nAltere um número na matriz A:"
A.alterar_elemento

puts "\nAltere um número na matriz B:"
B.alterar_elemento

puts "\nDigite um escalar para multiplicar as matrizes:"
escalar = gets.to_f

A.multiplicacao_escalar(escalar)
puts "\nMatriz A * #{escalar}:"
A.imprime

B.multiplicacao_escalar(escalar)
puts "\nMatriz B * #{escalar}:"
B.imprime

transpostaA = A.transposta
transpostaB = B.transposta

puts "\nTransposta A:"
transpostaA.imprime
transpostaA.salva_em_arquivo("saida.txt")

puts "\nTransposta B:"
transpostaB.imprime
transpostaB.salva_em_arquivo("saida.txt")

soma = Matriz.soma(A, B)
puts "\nA soma das matrizes é:"
soma.imprime
soma.salva_em_arquivo("saida.txt")

subtracao = Matriz.subtrai(A, B)
puts "\nA subtração das matrizes é:"
subtracao.imprime
subtracao.salva_em_arquivo("saida.txt")

puts "\nDeterminante A:"
A.imprime
puts "\nDeterminante: #{A.determinante}"

puts "\nDeterminante B:"
B.imprime
puts "\nDeterminante: #{B.determinante}"


puts "\nA é identidade? #{A.identidade? ? 'Sim' : 'Não'}"
puts "B é identidade? #{B.identidade? ? 'Sim' : 'Não'}"

puts "\nA é simétrica? #{A.simetrica? ? 'Sim' : 'Não'}"
puts "B é simétrica? #{B.simetrica? ? 'Sim' : 'Não'}"

puts "\nTraço de A: #{A.traco.round(1)}"
puts "Traço de B: #{B.traco.round(1)}"

puts "\nA ao quadrado:"
potenciaA = A.potencia(2)
potenciaA.imprime

puts "\nB ao quadrado:"
potenciaB = B.potencia(2)
potenciaB.imprime

puts "\nA é nilpotente até k=3? #{A.nilpotente?(3) ? 'Sim' : 'Não'}"
puts "B é nilpotente até k=3? #{B.nilpotente?(3) ? 'Sim' : 'Não'}"


puts "\nMatriz oposta de A:"
A.oposta.imprime

puts "\nMatriz oposta de B:"
B.oposta.imprime



puts "\nProduto de Hadamard entre A e B:"
hadamard = A.hadamard(B)
hadamard.imprime



