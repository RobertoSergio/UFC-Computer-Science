def distancia():
  d <- vetor[0, ..., n-1]
  para v E V:
    d[v]=-1
  d[o]=0
  f<-fila vazia
  f.enfilar(o)
  enquanto nao F.vazia():
    u<-f.desenfilar()
    para v E N(u):
      se d(v)=-1
        d(v)<-d(u)+1
        F.enfilar(v)
  retorne d

def N(G, vertice):
    vizinhos = []
    for aresta E  G:
        origem, destino = aresta
        if origem == vertice:
            vizinhos.append(destino)
        else:
            vizinhos.append(origem)
    return vizinhos

def encontrar_distancias(arestas, origem, n):    
    d = [-1] * (n+1)
    d[origem] = 0
    fila = [origem]
    indice_fila = 0

    while indice_fila < len(fila):
        u = fila[indice_fila]
        indice_fila += 1

        for v in N(arestas , u):
            if d[v] == -1:
                d[v] = d[u] + 1
                fila.append(v)

    return d[1:]

arestas = [(1, 2), (1, 3) , (2, 4), (3, 6), (5, 6),(5,1)]
origem = 1
distancias = encontrar_distancias(arestas, origem , 6)
print(distancias)