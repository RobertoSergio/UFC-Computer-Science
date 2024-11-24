def maximiza_tempo_ocupado(atividades):
  atividades.sort(key=lambda x: x[0])  # Ordena as atividades com base no tempo de início
  memo = [-1] * len(atividades)  # Tabela para memorização

  return maximiza_tempo_ocupado_recursivo(atividades, 0, memo)

def maximiza_tempo_ocupado_recursivo(atividades, indice, memo):
  if indice >= len(atividades):
      return 0

  if memo[indice] != -1:
      return memo[indice]

  tempo_com_atividade_atual = atividades[indice][2] + maximiza_tempo_ocupado_recursivo(atividades, proxima_atividade_sem_conflito(indice, atividades), memo)

  tempo_sem_atividade_atual = maximiza_tempo_ocupado_recursivo(atividades, indice + 1, memo)

  resultado = max(tempo_com_atividade_atual, tempo_sem_atividade_atual)
  memo[indice] = resultado

  return resultado

def proxima_atividade_sem_conflito(indice, atividades):
  tempo_fim_atual = atividades[indice][1]
  proximo_indice = indice + 1

  while proximo_indice < len(atividades) and atividades[proximo_indice][0] < tempo_fim_atual:
      proximo_indice += 1

  return proximo_indice

# Exemplo de uso
atividades = [
  (1, 3, 2),  # Atividade A
  (2, 5, 3),  # Atividade B
  (4, 7, 3),  # Atividade C
  (6, 9, 3),  # Atividade D
  (8, 11, 3)  # Atividade E
]

resultado = maximiza_tempo_ocupado(atividades)
print(f"Tempo total ocupado: {resultado}")
