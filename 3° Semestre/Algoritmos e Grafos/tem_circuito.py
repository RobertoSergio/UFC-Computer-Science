def tem_circuito(G):
    Estado = vetor[0 , ... , n-1] de enumerações {nao_atingido, no_caminho, finalizado}
    Estado = ['não_atingido'] * (n+1)
  
    for v E V
        if Estado[v] == 'não_atingido':
            if encontrou_circuito(G, Estado, v):
                return True
    return False

def encontrou_circuito(G, Estado, u):
    Estado[u] = 'no_caminho_atual'
    for v in N+(u):
        if Estado[v] == 'no_caminho_atual':
            return True
        if Estado[v] == 'não_atingido':
            if encontrou_circuito(G, Estado, v):
                return True
    
    Estado[u] = 'finalizado'
    return False

def N(vertice):
    vizinhos = []
    for aresta in G:
        origem, destino = aresta
        if origem == vertice:
            vizinhos.append(destino)
    return vizinhos

def main():
    G = [(1, 2), (1, 3), (2, 4), (3, 6), (6, 5), (5, 1)]
    if tem_circuito(G):
        print("O grafo contém circuito")
    else:
        print("O grafo não contém circuito")

main()