import numpy as np
import random
import matplotlib.pyplot as plt

def gerar_cidades(num_cidades, limite_inferior=0, limite_superior=100):
    return np.random.uniform(limite_inferior, limite_superior, (num_cidades, 2))

def calcular_distancia(cidade1, cidade2):
    return np.linalg.norm(cidade1 - cidade2)

def matriz_distancias(cidades):
    num_cidades = len(cidades)
    matriz = np.zeros((num_cidades, num_cidades))
    for i in range(num_cidades):
        for j in range(num_cidades):
            if i != j:
                matriz[i][j] = calcular_distancia(cidades[i], cidades[j])
    return matriz

def inicializar_feromonios(num_cidades, feromonio_inicial):
    return np.full((num_cidades, num_cidades), feromonio_inicial)

def escolher_proxima_cidade(cidade_atual, visitadas, feromonios, distancias, alfa, beta):
    probabilidades = []
    for cidade in range(len(distancias)):
        if cidade not in visitadas:
            tau = feromonios[cidade_atual][cidade] ** alfa
            eta = (1 / distancias[cidade_atual][cidade]) ** beta
            probabilidades.append((cidade, tau * eta))

    soma = sum(peso for _, peso in probabilidades)
    probabilidades = [(cidade, peso / soma) for cidade, peso in probabilidades]

    escolha = random.choices([cidade for cidade, _ in probabilidades], [peso for _, peso in probabilidades])[0]
    return escolha

def construir_caminho(feromonios, distancias, alfa, beta):
    caminho = []
    visitadas = set()
    cidade_atual = random.randint(0, len(distancias) - 1)
    caminho.append(cidade_atual)
    visitadas.add(cidade_atual)

    while len(visitadas) < len(distancias):
        proxima_cidade = escolher_proxima_cidade(cidade_atual, visitadas, feromonios, distancias, alfa, beta)
        caminho.append(proxima_cidade)
        visitadas.add(proxima_cidade)
        cidade_atual = proxima_cidade

    return caminho

def calcular_custo_caminho(caminho, distancias):
    custo = sum(distancias[caminho[i]][caminho[i + 1]] for i in range(len(caminho) - 1))
    custo += distancias[caminho[-1]][caminho[0]]  # Voltar à cidade inicial
    return custo

def atualizar_feromonios(feromonios, caminhos, custos, evaporacao, q):
    feromonios *= (1 - evaporacao)  # Evaporação
    for caminho, custo in zip(caminhos, custos):
        deposito = q / custo
        for i in range(len(caminho) - 1):
            feromonios[caminho[i]][caminho[i + 1]] += deposito
            feromonios[caminho[i + 1]][caminho[i]] += deposito
        feromonios[caminho[-1]][caminho[0]] += deposito
        feromonios[caminho[0]][caminho[-1]] += deposito

def plotar_caminho(cidades, caminho):
    plt.figure(figsize=(10, 6))
    for i in range(len(caminho)):
        cidade1 = cidades[caminho[i]]
        cidade2 = cidades[caminho[(i + 1) % len(caminho)]]
        plt.plot([cidade1[0], cidade2[0]], [cidade1[1], cidade2[1]], 'b-')

    plt.scatter(cidades[:, 0], cidades[:, 1], c='red', marker='o')
    for i, (x, y) in enumerate(cidades):
        plt.text(x, y, str(i), color='black', fontsize=12)

    plt.title("Melhor Caminho Encontrado")
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.grid(True)
    plt.show()

def executar_algoritmo_colonia_formigas(num_cidades, num_formigas, num_iteracoes, alfa, beta, evaporacao, feromonio_inicial, q):
    cidades = gerar_cidades(num_cidades)
    distancias = matriz_distancias(cidades)
    feromonios = inicializar_feromonios(num_cidades, feromonio_inicial)
    melhor_caminho = None
    menor_custo = float('inf')

    for iteracao in range(num_iteracoes):
        caminhos = []
        custos = []

        for _ in range(num_formigas):
            caminho = construir_caminho(feromonios, distancias, alfa, beta)
            custo = calcular_custo_caminho(caminho, distancias)
            caminhos.append(caminho)
            custos.append(custo)

            if custo < menor_custo:
                melhor_caminho = caminho
                menor_custo = custo

        atualizar_feromonios(feromonios, caminhos, custos, evaporacao, q)
        print(f"Iteração {iteracao + 1}/{num_iteracoes}, Melhor Custo: {menor_custo:.2f}")

    print(f"Melhor Caminho: {melhor_caminho}")
    print(f"Menor Custo: {menor_custo:.2f}")
    plotar_caminho(cidades, melhor_caminho)
