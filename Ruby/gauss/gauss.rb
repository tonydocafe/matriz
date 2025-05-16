EPS = 1e-6
MAX = 10

def print_matriz(mat)
  mat.each do |linha|
    puts linha.map { |v| format("%7.2f", v) }.join(" ")
  end
  puts
end

def troca_linhas(mat, l1, l2)
  mat[l1], mat[l2] = mat[l2], mat[l1]
  puts "L#{l1 + 1} <-> L#{l2 + 1}"
end

def multiplica_linha(mat, l, fator)
  mat[l].map! { |v| v * fator }
  puts "L#{l + 1} <- %.2f * L#{l + 1}" % fator
end

def soma_linha(mat, l1, l2, fator)
  mat[l1].each_index do |j|
    mat[l1][j] += fator * mat[l2][j]
  end
  puts "L#{l1 + 1} <- L#{l1 + 1} + %.2f.L#{l2 + 1}" % fator
end

def escalonar_reduzida(mat)
  lin = mat.size
  col = mat[0].size
  linha_pivo = 0

  col.times do |j|
    break if linha_pivo >= lin

    # Achar pivô
    i_max = (linha_pivo...lin).max_by { |i| mat[i][j].abs }

    next if mat[i_max][j].abs < EPS

    if i_max != linha_pivo
      troca_linhas(mat, linha_pivo, i_max)
      print_matriz(mat)
    end

    pivo = mat[linha_pivo][j]
    if (pivo - 1.0).abs > EPS
      multiplica_linha(mat, linha_pivo, 1.0 / pivo)
      print_matriz(mat)
    end

    lin.times do |i|
      next if i == linha_pivo || mat[i][j].abs < EPS

      fator = -mat[i][j]
      soma_linha(mat, i, linha_pivo, fator)
      print_matriz(mat)
    end

    linha_pivo += 1
  end
end


matriz = [
  [0.0, 3.0, 5.0, 2.0, -1.0],
  [2.0, -1.0, 0.0, 1.0, -2.0],
  [3.0, 2.0, 3.0, 0.0, 0.0]
]

puts "Matriz original:"
print_matriz(matriz)

escalonar_reduzida(matriz)

puts "Matriz escalonada reduzida:"
print_matriz(matriz)
