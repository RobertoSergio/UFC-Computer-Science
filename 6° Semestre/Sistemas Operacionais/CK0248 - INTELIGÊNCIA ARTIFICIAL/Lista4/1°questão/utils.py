import numpy as np
import random

# Função Rastrigin
def rastrigin(x):
    A = 10
    return A * len(x) + sum([(xi**2 - A * np.cos(2 * np.pi * xi)) for xi in x])

# Inicialização da população
def inicializar_populacao(tamanho_populacao, tamanho_genoma, limites):
    return [np.random.uniform(limites[0], limites[1], tamanho_genoma) for _ in range(tamanho_populacao)]

# Avaliação da aptidão
def avaliar_aptidao(populacao):
    return [rastrigin(individuo) for individuo in populacao]

# Seleção por torneio
def selecao_torneio(populacao, aptidao, tamanho_torneio=3):
    selecionados = []
    for _ in range(len(populacao)):
        aspirantes = [random.randint(0, len(populacao) - 1) for _ in range(tamanho_torneio)]
        selecionados.append(min(aspirantes, key=lambda aspirante: aptidao[aspirante]))
    return [populacao[i] for i in selecionados]

# Crossover de ponto único
def crossover_ponto_unico(pai1, pai2, taxa_crossover):
    if random.random() < taxa_crossover:
        ponto = random.randint(1, len(pai1) - 1)
        filho1 = np.concatenate([pai1[:ponto], pai2[ponto:]])
        filho2 = np.concatenate([pai2[:ponto], pai1[ponto:]])
        return filho1, filho2
    return pai1, pai2

# Mutação
def mutar(individuo, taxa_mutacao, limites):
    for i in range(len(individuo)):
        if random.random() < taxa_mutacao:
            individuo[i] = np.random.uniform(limites[0], limites[1])
    return individuo
