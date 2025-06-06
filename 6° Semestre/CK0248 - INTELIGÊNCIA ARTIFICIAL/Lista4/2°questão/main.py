import matplotlib.pyplot as plt
import numpy as np
from prettytable import PrettyTable
from utils import (
    funcao_aptidao,
    criar_populacao_inicial,
    selecao,
    cruzamento,
    mutacao,
)

# Função principal do algoritmo genético
def algoritmo_genetico(tamanho_populacao, limite_inferior, limite_superior, geracoes, taxa_mutacao):
    populacao = criar_populacao_inicial(tamanho_populacao, limite_inferior, limite_superior)

    # Preparar para tabela de resultados
    tabela = PrettyTable()
    tabela.field_names = ["Geração", "a", "b", "c", "Aptidão"]

    melhores_resultados = []

    for geracao in range(geracoes):
        aptidoes = [funcao_aptidao(ind) for ind in populacao]

        # Armazena o melhor indivíduo da geração atual
        melhor_individuo = max(populacao, key=funcao_aptidao)
        melhor_aptidao = funcao_aptidao(melhor_individuo)
        melhores_resultados.append((melhor_individuo, melhor_aptidao))
        tabela.add_row([geracao + 1, melhor_individuo[0], melhor_individuo[1], melhor_individuo[2], melhor_aptidao])

        # Seleção dos indivíduos para a próxima geração
        populacao = selecao(populacao, aptidoes)

        # Cruzamento e mutação
        nova_populacao = []
        for i in range(0, len(populacao), 2):
            pai1 = populacao[i]
            pai2 = populacao[i + 1]
            filho1, filho2 = cruzamento(pai1, pai2)
            nova_populacao.append(mutacao(filho1, taxa_mutacao, limite_inferior, limite_superior))
            nova_populacao.append(mutacao(filho2, taxa_mutacao, limite_inferior, limite_superior))

        # Mantém o melhor indivíduo da geração atual
        nova_populacao[0] = melhor_individuo
        populacao = nova_populacao

    # Exibir a tabela com os melhores resultados por geração
    print(tabela)

    # Mostrar o melhor resultado final
    melhor_solucao = max(populacao, key=funcao_aptidao)
    print(f"\nMelhor solução encontrada: a = {melhor_solucao[0]}, b = {melhor_solucao[1]}, c = {melhor_solucao[2]}")

    # Plotar os valores dos parâmetros ao longo das gerações
    geracoes_lista = range(1, geracoes + 1)
    a_valores = [resultado[0][0] for resultado in melhores_resultados]
    b_valores = [resultado[0][1] for resultado in melhores_resultados]
    c_valores = [resultado[0][2] for resultado in melhores_resultados]

    plt.plot(geracoes_lista, a_valores, label='a', color='blue')
    plt.plot(geracoes_lista, b_valores, label='b', color='green')
    plt.plot(geracoes_lista, c_valores, label='c', color='red')
    plt.xlabel('Geração')
    plt.ylabel('Valores dos Parâmetros')
    plt.title('Evolução dos Parâmetros ao Longo das Gerações')
    plt.legend()
    plt.show()

# Parâmetros para o algoritmo genético
tamanho_populacao = 100
limite_inferior = -50
limite_superior = 50
geracoes = 25
taxa_mutacao = 0.1

# Executar o algoritmo genético
algoritmo_genetico(tamanho_populacao, limite_inferior, limite_superior, geracoes, taxa_mutacao)
