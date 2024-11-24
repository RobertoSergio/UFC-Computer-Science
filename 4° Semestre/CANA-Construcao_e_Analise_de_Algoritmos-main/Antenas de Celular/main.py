def instala_antenas(vilarejos):
  # Inicializações
  ini = vilarejos[0]  # Posição inicial do primeiro vilarejo
  antenas = [ini + 4]  # A primeira antena é instalada a 4 km da posição inicial
  alcance = ini + 8  # O alcance da primeira antena é de 8 km (4 km para cada lado)
  antenas_instaladas = 1  # Contador de antenas instaladas

  # Itera sobre os vilarejos
  for vila in vilarejos:
      # Se a vila estiver dentro do alcance, continua para a próxima vila
      if vila < alcance:
          continue

      # Adiciona uma antena 4 km após a posição do vilarejo
      antenas.append(vila + 4)
      antenas_instaladas += 1
      alcance = vila + 8  # Atualiza o alcance da antena

  return antenas

# Main
vilarejos = [1, 6, 10, 14, 20, 25]
antenas_instaladas = instala_antenas(vilarejos)
# Vetor com a posição das antenas instaladas
print("Localizações das antenas:", antenas_instaladas)
