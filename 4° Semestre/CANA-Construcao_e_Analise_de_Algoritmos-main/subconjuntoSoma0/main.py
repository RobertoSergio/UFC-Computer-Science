def subconjuntoSomaZero(L):
  # Lista de tuplas (soma, subconjunto)
  somas = [(0, [])]
  maior_tamanho = 0
  subconjunto = []

  for elemento in L:
      novas_somas = []

      for soma, numeros in somas:
          nova_soma = soma + elemento
          novo_numeros = numeros + [elemento]

          # Verifica se a nova soma é zero
          if nova_soma == 0:
              # Atualiza o maior tamanho e subconjunto se necessário
              if len(novo_numeros) > maior_tamanho:
                  maior_tamanho = len(novo_numeros)
                  subconjunto = novo_numeros

          novas_somas.append((nova_soma, novo_numeros))

      # Adiciona as novas somas à lista
      somas.extend(novas_somas)

  return maior_tamanho, subconjunto

# Exemplo de uso:
L = [5, 46, -7, 9, 1, -51, -3, 12, 6, -11, 4, 2, -5, -13, 12, -5]
resultado_tamanho, resultado_subconjunto = subconjuntoSomaZero(L)
print("Maior tamanho de subconjunto com soma zero:", resultado_tamanho)
print("Subconjunto com soma zero:", resultado_subconjunto)
