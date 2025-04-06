class Matriz
  attr_accessor :matriz, :m, :n

  def initialize(m, n)
    @m = m
    @n = n
    @matriz = Array.new(m) { Array.new(n, 0.0) }
  end

  def self.ler_de_arquivo(caminho)
    linhas = File.readlines(caminho).map(&:strip)
    tamanho = linhas.shift.to_i
    matriz = new(tamanho, tamanho)
    tamanho.times do |i|
      matriz.matriz[i] = linhas[i].split.map(&:to_f)
    end
    matriz
  end

  def multiplicacao_escalar(escalar)
    @m.times do |i|
      @n.times do |j|
        @matriz[i][j] *= escalar
      end
    end
  end

  def soma_diagonal_superior
    soma = 0.0
    @m.times do |i|
      (i+1...@n).each do |j|
        soma += @matriz[i][j]
      end
    end
    soma
  end

  def self.multiplicacao(a, b)
    raise "Dimensões incompatíveis" unless a.n == b.m
    resultado = new(a.m, b.n)
    a.m.times do |i|
      b.n.times do |j|
        soma = 0.0
        a.n.times do |k|
          soma += a.matriz[i][k] * b.matriz[k][j]
        end
        resultado.matriz[i][j] = soma
      end
    end
    resultado
  end

  def alterar_elemento
    loop do
      print "linha: "
      m = gets.to_i
      print "coluna: "
      n = gets.to_i
      print "novo número: "
      valor = gets.to_f

      @matriz[m - 1][n - 1] = valor

      puts "Deseja ver a matriz? (1), alterar mais? (2), sair? (0)"
      opcao = gets.to_i
      imprime if opcao == 1
      break if opcao == 0
    end
  end

  def imprime
    @matriz.each do |linha|
      puts linha.map { |e| format("%.1f", e) }.join(" | ")
    end
  end

  def self.soma(a, b)
    raise "Tamanhos diferentes" unless a.m == b.m && a.n == b.n
    resultado = new(a.m, a.n)
    a.m.times do |i|
      a.n.times do |j|
        resultado.matriz[i][j] = a.matriz[i][j] + b.matriz[i][j]
      end
    end
    resultado
  end

  def self.subtrai(a, b)
    raise "Tamanhos diferentes" unless a.m == b.m && a.n == b.n
    resultado = new(a.m, a.n)
    a.m.times do |i|
      a.n.times do |j|
        resultado.matriz[i][j] = a.matriz[i][j] - b.matriz[i][j]
      end
    end
    resultado
  end

  def transposta
    resultado = Matriz.new(@n, @m)
    @m.times do |i|
      @n.times do |j|
        resultado.matriz[j][i] = @matriz[i][j]
      end
    end
    resultado
  end

  def salva_em_arquivo(nome_arquivo)
    File.open(nome_arquivo, "a") do |f|
      f.puts "#{@m} #{@n}"
      @matriz.each do |linha|
        f.puts linha.map { |e| format("%.2f", e) }.join(" ")
      end
      f.puts
    end
  end

  def determinante
    raise "Matriz não quadrada" unless @m == @n
    return @matriz[0][0] if @m == 1
    return @matriz[0][0] * @matriz[1][1] - @matriz[0][1] * @matriz[1][0] if @m == 2

    det = 0.0
    @n.times do |j|
      sub = submatriz(0, j)
      det += ((j.even? ? 1 : -1) * @matriz[0][j] * sub.determinante)
    end
    det
  end

  private

  def submatriz(linha_excluida, coluna_excluida)
    nova = Matriz.new(@m - 1, @n - 1)
    nova_linha = 0
    @matriz.each_with_index do |linha, i|
      next if i == linha_excluida
      nova_coluna = 0
      linha.each_with_index do |valor, j|
        next if j == coluna_excluida
        nova.matriz[nova_linha][nova_coluna] = valor
        nova_coluna += 1
      end
      nova_linha += 1
    end
    nova
  end
end
