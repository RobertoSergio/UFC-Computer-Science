bfs(origem, destino, pais, capacidade_residual):
    visitados = vetor [0 , ... , n-1] de booleanos
    para r E V:
        visitados[r] <- False
    visitados[origem] <- True
    F <- fila vazia  # Fila para armazenar os nós a serem visitados
    F.enfilar(origem)
  
    enquanto não F.vazio():
        u = F.desenfilar()

        para v E N+(u):
            se não visitados[v] e capacidade_residual[u][v] > 0:
                fila.enfilar(v)
                visitados[v] <- True
                pais[v] <- u

                se v == destino:
                    caminho = []
                    enquanto v != origem:
                        caminho.enfilar(v)
                        v <- pais[v]
                    caminho.enfilar(origem)
                    caminho.reverse()
                    return caminho

    return []
#--------------------------------------------------------
#--------------------------------------------------------
#--------------------------------------------------------
#--------------------------------------------------------
#--------------------------------------------------------
#--------------------------------------------------------
#--------------------------------------------------------
#--------------------------------------------------------
#--------------------------------------------------------
#--------------------------------------------------------
#--------------------------------------------------------
#--------------------------------------------------------
#--------------------------------------------------------
#--------------------------------------------------------
bfs(origem, destino, pais, capacidade_residual):
    visitados <- vetor de [0, .. ,n-1] de booleanos
    para v E V:
        visitados[v] <- [False] 
    visitados[origem] <- True
    f<-fila vazia
    f.enfilar(origem)

    enquanto not fila.vazio():
        u <-f.desenfilar()

        for w E N+(u):
            if not visitados[w] and capacidade_residual[u][w] > 0:
                fila.enfilar(w)
                visitados[w] <- True
                pais[w] <- u

                if w == destino:
                    return True

    return False

N+(G, v)
    vizinhos <- []
    para aresta ∈ E:
        se aresta[0] == v
            vizinhos.inserir(aresta[1])
    return vizinhos

Ford-Fulkerson():
    pais <- vetor [0 , ..., n-1] de reais
    para v E V:
        pais[v] <- -1
    fluxo_maximo <- 0

    capacidade_residual <- matriz [0 , ... , n-1 ][0 , ... ,n-1]  de inteiros 

    para i E n-1:
        para j E n-1:
            capacidade_residual[i][j] = cf(i,j)

    enquanto bfs(graph, origem, destino, pais, capacidade_residual):
        fluxo_caminho <- infinito
        v <- destino

        enquanto v != origem:
            u <- pais[v]
            fluxo_caminho <- mínimo(fluxo_caminho, capacidade_residual[u][v])
            capacidade_residual[u][v] <- capacidade_residual[u][v] - fluxo_caminho
            capacidade_residual[v][u] <- capacidade_residual[v][u] + fluxo_caminho
            v <- u

        fluxo_maximo <- fluxo_maximo + fluxo_caminho

    retorne fluxo_maximo