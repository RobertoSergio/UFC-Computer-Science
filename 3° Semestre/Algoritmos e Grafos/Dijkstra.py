Dijkstra():
d <- vetor[0, ... , n-1] de reais
ANC <- vetor[0, ... , n-1] de inteiros 
para v E V
    d[v] <- infinito
    ANC[v] <- -1

H <- HEAP de mínimo vázio , para até n pares (u,p) indexados por u E[0, ..., n-1] (É necessário armazenar as posições com base em u) e tendo p como peso.
H.inserir(O , 0) // O  sendo o vertice de origem 

Enquanto não H.vazio()
    (u,p) <- H.extrair_Mínimo()
    d[u] <- p
    para v E N+(u)
        se d[v] == infinito
            peso_via_u<- p + w(u,v)
            se v ∉ H
                H.inserir(v,peso_via_u)
                ANC[v]<- u 
            senao
                se peso_via_u < H.peso_de(v)
                    H.atualizar_peso_de(v,peso_via_u)
                    ANC[v] <- u 
retorne (d,ANC)

N+(G, v)
    vizinhos <- []
    para aresta ∈ E:
        se aresta[0] == v
            vizinhos.inserir(aresta[1])
    return vizinhos

w(u, v)
    vizinhos <- []
    para aresta ∈ E:
        se aresta[0] == u e aresta[1] = v
           return aresta[2]


classe Heap:
    criar_heap(n):
        tamanho <- 0
        posicoes <- vetor [0 , ... , n-1 ] de inteiros 
        para v E V:
            posições[v] = NULL 
        heap <- vetor [] de inteiros // vetor vazio
        retorne heap

    inserir(u, peso):
        tamanho <- tamanho + 1
        i <- tamanho - 1
        posicoes[u] <- i
        heap.append((u, peso))
        subir(i)

    consultar_minimo():
        retorne heap[0]

    extrair_minimo():
        raiz <- heap[0]
        último <- heap[tamanho - 1]
        heap[0] <- último
        posicoes[último[0]] <- 0
        heap.pop()
        tamanho <- tamanho - 1
        descer(0)
        retorne raiz

    pertence(u):
        retorne posicoes[u] não é nulo

    peso_de(u):
        retorne heap[posicoes[u]][1]

    atualizar_peso_de(u, novo_peso):
        i <- posicoes[u]
        heap[i] <- (u, novo_peso)
        subir(i)

    subir(i):
        enquanto i > 0 e heap[i][1] < heap[(i - 1) // 2][1]:
            u1, p1 <- heap[i]
            u2, p2 <- heap[(i - 1) // 2]
            heap[i] <- (u2, p2)
            heap[(i - 1) // 2] <- (u1, p1)
            posicoes[u1], posicoes[u2] <- (i - 1) // 2, i
            i <- (i - 1) // 2

    descer(i):
        enquanto verdadeiro:
            esquerda <- 2 * i + 1
            direita <- 2 * i + 2
            menor <- i

            se esquerda < tamanho e heap[esquerda][1] < heap[menor][1]:
                menor <- esquerda

            se direita < tamanho e heap[direita][1] < heap[menor][1]:
                menor <- direita

            se menor != i:
                u1, p1 <- heap[i]
                u2, p2 <- heap[menor]
                heap[i] <- (u2, p2)
                heap[menor] <- (u1, p1)
                posicoes[u1], posicoes[u2] <- menor, i
                i <- menor
            senão:
                break

def dijkstra(graph, origem):
    distancias <- vetor[0, ..., n-1] de reais
    ANC <- vetor[0, ..., n-1] de inteiros
    visitados <- vetor[0, ..., n-1] de booleanos

    para v em V faça:
        distancias[v] <- infinito
        ANC[v] <- -1
        visitados[v] <- falso

    distancias[origem] = 0 

    for a E V:
        min_distancia <- infinito
        proximo <- -1

        for v E V:
            if not visitados[v] and distancias[v] < min_distancia:
                min_distancia <- distancias[v]
                proximo <- v

        if proximo == -1:
            break

        visitados[proximo] <- True

        for v E V:
            if not visitados[v] and graph[proximo][v] != 0:
                peso_via_proximo <- distancias[proximo] + graph[proximo][v]

                if peso_via_proximo < distancias[v]:
                    distancias[v] <- peso_via_proximo
                    ANC[v] <- proximo

    return distancias, ANC