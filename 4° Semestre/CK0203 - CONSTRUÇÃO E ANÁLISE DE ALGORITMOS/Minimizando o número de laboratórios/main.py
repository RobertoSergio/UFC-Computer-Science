def quicksort(atividades, key):
  if len(atividades) <= 1:
      return atividades
  pivot = atividades[len(atividades) // 2][key]
  left = [x for x in atividades if x[key] < pivot]
  middle = [x for x in atividades if x[key] == pivot]
  right = [x for x in atividades if x[key] > pivot]
  return quicksort(left, key) + middle + quicksort(right, key)

def min_lab(atividades, n):
  atividades = quicksort(atividades, 0)  # Ordena as atividades pelo início
  ati_inicio = [atividade[0] for atividade in atividades]

  atividades = quicksort(atividades, 1)  # Ordena as atividades pelo fim
  ati_fim = [atividade[1] for atividade in atividades]

  i = 0
  f = 0
  max_lab = 0
  lab = 0

  while i < n and f < n:
      if ati_inicio[i] < ati_fim[f]:
          lab += 1
          i += 1

          if lab > max_lab:
              max_lab = lab
      else:
          lab -= 1
          f += 1

  return max_lab

# main
atividades = [(1, 3), (2, 5), (4, 7), (6, 9), (8, 11)]
resultado = min_lab(atividades, len(atividades))
print("Maior número de laboratórios abertos ao mesmo tempo eh:", resultado)
