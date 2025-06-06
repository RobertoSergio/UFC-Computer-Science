import random
import numpy as np
from prettytable import PrettyTable
import matplotlib.pyplot as plt

# Função de aptidão (objetivo é criar a parábola mais plana possível)
def funcao_aptidao(parametros):
    a, b, c = parametros
    if a <= 0:
        return -float('inf')  # Penaliza parábolas voltadas para baixo
    vertice_x = -b / (2 * a)
    vertice_y = a * (vertice_x ** 2) + b * vertice_x + c
    y_esquerda = a * (vertice_x - 1) ** 2 + b * (vertice_x - 1) + c
    y_direita = a * (vertice_x + 1) ** 2 + b * (vertice_x + 1) + c
    curvatura = abs(y_esquerda - vertice_y) + abs(y_direita - vertice_y)
    return -curvatura  # Negativo para minimizar a curvatura

# Função para criar a população inicial
def criar_populacao_inicial(tamanho, limite_inferior, limite_superior):
    populacao = []
    for _ in range(tamanho):
        individuo = (
            random.uniform(limite_inferior, limite_superior),
            random.uniform(limite_inferior, limite_superior),
            random.uniform(limite_inferior, limite_superior)
        )
        populacao.append(individuo)
    return populacao

# Função de seleção por torneio
def selecao(populacao, aptidoes, tamanho_torneio=3):
    selecionados = []
    for _ in range(len(populacao)):
        torneio = random.sample(list(zip(populacao, aptidoes)), tamanho_torneio)
        vencedor = max(torneio, key=lambda x: x[1])[0]
        selecionados.append(vencedor)
    return selecionados

# Função de cruzamento
def cruzamento(pai1, pai2):
    alfa = random.random()
    filho1 = tuple(alfa * p1 + (1 - alfa) * p2 for p1, p2 in zip(pai1, pai2))
    filho2 = tuple(alfa * p2 + (1 - alfa) * p1 for p1, p2 in zip(pai1, pai2))
    return filho1, filho2

# Função de mutação
def mutacao(individuo, taxa_mutacao, limite_inferior, limite_superior):
    individuo = list(individuo)
    for i in range(len(individuo)):
        if random.random() < taxa_mutacao:
            quantidade_mutacao = random.uniform(-1, 1)
            individuo[i] += quantidade_mutacao
            # Garante que o valor permaneça dentro dos limites
            individuo[i] = max(min(individuo[i], limite_superior), limite_inferior)
    return tuple(individuo)
