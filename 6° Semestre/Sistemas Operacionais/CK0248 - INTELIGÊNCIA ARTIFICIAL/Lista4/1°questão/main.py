import numpy as np
import random
from utils import inicializar_populacao, avaliar_aptidao, selecao_torneio, crossover_ponto_unico, mutar

# Parâmetros do algoritmo genético
tamanho_populacao = 300
tamanho_genoma = 10
taxa_crossover = 0.8
taxa_mutacao = 0.01
num_geracoes = 300
limites = [-5.12, 5.12]

# Algoritmo genético
def algoritmo_genetico():
    populacao = inicializar_populacao(tamanho_populacao, tamanho_genoma, limites)
    
    for geracao in range(num_geracoes):
        aptidao = avaliar_aptidao(populacao)
        
        populacao_selecionada = selecao_torneio(populacao, aptidao)
        
        proxima_populacao = []
        for i in range(0, len(populacao_selecionada), 2):
            pai1 = populacao_selecionada[i]
            pai2 = populacao_selecionada[min(i + 1, len(populacao_selecionada) - 1)]
            filho1, filho2 = crossover_ponto_unico(pai1, pai2, taxa_crossover)
            proxima_populacao.extend([filho1, filho2])
        
        populacao = [mutar(individuo, taxa_mutacao, limites) for individuo in proxima_populacao]
        
        aptidao = avaliar_aptidao(populacao)
        melhor_aptidao = min(aptidao)
        melhor_individuo = populacao[aptidao.index(melhor_aptidao)]
        
        print(f'Geração {geracao + 1}: Melhor Aptidão = {melhor_aptidao}')
    
    return melhor_individuo

if __name__ == "__main__":
    melhor_solucao = algoritmo_genetico()
    print("Melhor solução encontrada:", melhor_solucao)
