def maximo_de_dados_processados(dados_processamento, dados_possiveis_processados, i, j, memo):
  n = len(dados_processamento)

  if i >= n:
      return 0

  if memo[i][j] != -1:
      return memo[i][j]

  # Calcula a quantidade de dados processados no dia
  dados = min(dados_processamento[i], dados_possiveis_processados[j])

  # Calcula a quantidade de dados processados ao não reiniciar no dia i
  nao_reiniciar = dados + maximo_de_dados_processados(dados_processamento, dados_possiveis_processados, i + 1, j + 1, memo)

  # Calcula a quantidade de dados processados ao reiniciar no dia i
  reiniciar = maximo_de_dados_processados(dados_processamento, dados_possiveis_processados, i + 1, 0, memo)

  # Retorna o máximo entre as duas opções
  memo[i][j] = max(nao_reiniciar, reiniciar)

  return memo[i][j]

# Main:
dados_processamento = [5, 1, 20, 5]
dados_possiveis_processados = [20, 15, 10, 5]

# Inicializa a tabela de memorização
memo = [[-1] * len(dados_possiveis_processados) for _ in range(len(dados_processamento))]

resultado = maximo_de_dados_processados(dados_processamento, dados_possiveis_processados, 0, 0, memo)

print("Quantidade máxima de dados processados:", resultado)
