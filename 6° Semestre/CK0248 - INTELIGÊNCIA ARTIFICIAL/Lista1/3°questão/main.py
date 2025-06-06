from utils import greedy_search, a_star_search

inicio = "Arad"
destino = "Bucareste"

# Executando Greedy Search 
caminho_guloso = greedy_search(inicio, destino)
print("Caminho encontrado pela Busca Gulosa:", caminho_guloso)

# Executando A*
caminho_a_estrela = a_star_search(inicio, destino)
print("Caminho encontrado pelo A*:", caminho_a_estrela)
